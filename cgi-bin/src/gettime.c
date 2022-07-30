#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <string.h>
sqlite3 * open_create_table(){               
	sqlite3 *db;
    int ret =sqlite3_open("/usr/lib/cgi-bin/facename.db",&db);
	if(ret != SQLITE_OK){
         return  NULL;
    }
	return db;
}
int main(){
    printf("context-type:html/text\n\n");
   char *url = getenv("QUERY_STRING");
    sqlite3 *db =open_create_table();
    if(db==NULL||url==NULL){
        printf("err");
        return -1;
    }
    if(strcmp(url,"123456")){
        printf("key err");
        return -1;
    }
    char *sql="select *from times";

    char **result;
    int row,col;
    int ret = sqlite3_get_table(db,sql,&result,&row,&col,NULL); 
    if(ret != SQLITE_OK){
        printf("&sqlno");
         return  -1;
    }
    for(int i=1;i<=row;i++ )
    for(int j =0;j<col;j++)
    printf("&%s",result[2*i+j]);

    sqlite3_close(db);
    return 0;    
}