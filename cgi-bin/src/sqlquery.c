#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <string.h>
sqlite3 * open_sql(){
	sqlite3 *db;char *err;
    int ret =sqlite3_open("/usr/lib/cgi-bin/facename.db",&db);
	if(ret != SQLITE_OK){
         return  NULL;
    }
	return db;
}
int flag=1;
int callback(void *arg,int col,char **mes,char **names){
    if(flag){
        for(int i =0;i<col;i++){
        printf("%s\t",names[i]);
        }
    printf("\n");
    flag=0;
    }
    for(int i =0;i<col;i++){
        printf("%s\t",mes[i]);
    }
    printf("\n");
    return 0;
}
int main(){
    printf("context-type:html/text\n\n");
   char *url = getenv("QUERY_STRING");
    sqlite3 *db =open_sql();
    if(db==NULL||url==NULL){
        printf("err");
        return -1;
    }
    char sql[1024];
    int len = strlen(url)+1;
    for(int i=0;i<=len;i++){
        if(url[i]=='&'){
            sql[i]=' ';
        }else{
            sql[i]=url[i];
        }
    }
    
    char *err;
   int ret =  sqlite3_exec(db,sql,callback,NULL,&err);
    if(ret != SQLITE_OK){
        printf("%s\n",err);
         return  -1;
    }
    printf("ok^-^\n");
    sqlite3_close(db);
    return 0;    
}