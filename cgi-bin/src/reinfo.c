#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <string.h>
sqlite3 * open_create_table(){
	const char * createSql ="create table if not exists users(\
                        id  integer primary key,\
                        name  char(32)  not null unique,\
                        zhiwei char(32)  not null,\
                        bumen char(32)  not null,\
                        num varchar(32)  not null,\
                        state bool not null default false\
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
    char *sql = "update users set state =false";
   
    char **result;
    int row,col;
    int ret =sqlite3_exec(db,sql,NULL,NULL,NULL);
    if(ret != SQLITE_OK){
         printf("reset err");
        return -1;
    }
    printf("ok");

    sqlite3_close(db);
    return 0;    
}