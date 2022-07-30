#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    printf("context-type:html/text\n\n");
     char *value = getenv("CONTENT_TYPE");
     char *data = getenv("CONTENT_LENGTH");
    if (data == NULL||value==NULL)
    {
        printf("err");
        return -1;
    }
    


    unsigned int recvsize = 0, sendsize = atoi(data);
    char savepath[128];
    sprintf(savepath,"/usr/lib/cgi-bin/facePic/%s",value);
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
    
    printf("%d", recvsize);
    return 0;
}