
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> //open
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>	  //close、read
#include "sqlite3.h"

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
    const char * createtime ="create table if not exists times(\
                        name char(32)  not null,\
                        time text not null default (datetime('now','localtime'))\
						)";                   
	sqlite3 *db;
    int ret =sqlite3_open("/usr/lib/cgi-bin/facename.db",&db);
	if(ret != SQLITE_OK){
         return  NULL;
    }
    ret =sqlite3_exec(db,createSql,NULL,NULL,NULL);
    if(ret != SQLITE_OK){
         return  NULL;
    }
    ret =sqlite3_exec(db,createtime,NULL,NULL,NULL);
    if(ret != SQLITE_OK){
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
    if (value==NULL||db==NULL||data==NULL)
    {
        printf("err");
        return -1;
    }

    char sql[1024],picname[128];
    if(atoi(data)>0){

        sscanf(value,"%[^&]&%[^;]",picname,sql);
        unsigned int recvsize = 0, sendsize = atoi(data);
        char savepath[128];
        sprintf(savepath,"/usr/lib/cgi-bin/facePic/%s",picname);
        FILE *file = fopen(savepath, "w+");
        while (recvsize < sendsize)
        {
            char buf[10240] = {0};
            //从标准输入中读取数据（上传的文件数据）
            int size = fread(buf, 1, sizeof(buf), stdin);
            recvsize += size;
            fwrite(buf, size, 1, file); //把读取到的数据写入到文件中
        }
        fclose(file);
    }
    int ret=-1;
    if(atoi(data)>0){
        ret = sqlite3_exec(db,sql,NULL,NULL,NULL);
    }else{
        ret = sqlite3_exec(db,value,NULL,NULL,NULL);
    }
    if(ret!=SQLITE_OK){
        printf("sql err");
        return -1;
    }
    printf("ok");
  
    sqlite3_close(db);
    
    return 0;
}
