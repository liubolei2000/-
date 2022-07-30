#include <cstdio>
#include <cstdlib>
#include <sys/types.h> //open
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>	  //close、read
#include <seeta/FaceDetector.h>
#include <seeta/FaceEngine.h>
#include <opencv.hpp>
extern "C"{
#include "sqlite3.h"

}
using namespace seeta;
using namespace seeta::v2;
using namespace cv;
sqlite3 * open_create_table(){
	const char * createSql ="create table if not exists users(\
                        id  integer primary key,\
                        name  char(32)  not null unique,\
                        zhiwei char(32)  not null,\
                        bumen char(32)  not null,\
                        num varchar(32)  not null,\
                        state bool not null default false,\
                        picpath text\
                        )";
	sqlite3 *db;char *err;
    int ret =sqlite3_open("/usr/lib/cgi-bin/facename.db",&db);
	if(ret != SQLITE_OK){
         return  NULL;
    }
    ret =sqlite3_exec(db,createSql,NULL,NULL,&err);
    if(ret != SQLITE_OK){
		sqlite3_free(err);
         return  NULL;
    }
	return db;
}
int main()
{
   
     printf("Content-Type:text/html\n\n");
    sqlite3 *db = open_create_table();
    char *data = getenv("CONTENT_LENGTH");
    char *value = getenv("CONTENT_TYPE");
    if (data == NULL||value==NULL||db==NULL)
    {
        printf("err");
        return -1;
    }

    
    char picname[128],facename[32],zhiwei[32],bumen[32],num[32];
    sscanf(value,"%[^,],%[^,],%[^,],%[^,],%s",picname,facename,zhiwei,bumen,num);
    unsigned int recvsize = 0, sendsize = atoi(data);
    char savepath[128];
    sprintf(savepath,"/usr/lib/cgi-bin/facePic/%s",picname);
    FILE *file = fopen(savepath, "w");
    while (recvsize < sendsize)
    {
        char buf[10240] = {0};
        //从标准输入中读取数据（上传的文件数据）
        int size = fread(buf, 1, sizeof(buf), stdin);
        recvsize += size;
        fwrite(buf, size, 1, file); //把读取到的数据写入到文件中
    }
    fclose(file);


    seeta::ModelSetting::Device device = seeta::ModelSetting::CPU;
    int id = 0;
    seeta::ModelSetting FD_model( "/opt/SeetaFace/bin/model/fd_2_00.dat", device, id );
    seeta::ModelSetting PD_model( "/opt/SeetaFace/bin/model/pd_2_00_pts5.dat", device, id );
    seeta::ModelSetting FR_model( "/opt/SeetaFace/bin/model/fr_2_10.dat", device, id );

     
    //初始化人脸引擎
    FaceEngine * fEngine = new FaceEngine(FD_model, PD_model,FR_model);

    fEngine->Load("/usr/lib/cgi-bin/face");

    Mat cvimage = imread(savepath, cv::IMREAD_COLOR);
    if(cvimage.empty()){
        printf("open err");return 0;
    }
    SeetaImageData simage;
    simage.width = cvimage.cols;
    simage.height = cvimage.rows;
    simage.channels = cvimage.channels();
    simage.data = cvimage.data;

  
  
    int fid = fEngine->Register(simage);
    printf("id:%d\n",fid);
    if(fid<0){printf("err");return 0;}

    char sql[128];
    sprintf(sql,"insert into users values(%d,'%s','%s','%s','%s',0,'%s')",fid,facename,zhiwei,bumen,num,picname);
    int ret = sqlite3_exec(db,sql,NULL,NULL,NULL);
	if(ret != SQLITE_OK){
        printf("insert err");
         return  0;
    }
    sqlite3_close(db);
    
    fEngine->Save("/usr/lib/cgi-bin/face");

    printf("ok");
    
    return 0;
}
