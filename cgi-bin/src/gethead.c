#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    printf("context-type:html/text\n\n");
   char *url = getenv("QUERY_STRING");
   if(url==NULL){
        printf("err");
        return -1;
   }
    char key[36],picname[128];
    sscanf(url,"%[^&]&%s",key,picname);
    if(strcmp(key,"123456")){
        printf("err");
        return -1;
    }
   char path[256];
    sprintf(path,"/usr/lib/cgi-bin/facePic/%s",picname);
    FILE * fs = fopen(path,"r");
    if(fs==NULL){
        printf("open err");
        return -1;
    }
   
    while (1)
    {
         char buf[4096]={0};
        int size = fread(buf,1,4096,fs);
        if(size<=0)break;
        fwrite(buf,size,1,stdout);
        
        
    }
    
    
    return 0;    
}