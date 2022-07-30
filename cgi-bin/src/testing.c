#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){
    // char * str = "a123,b3,c2,d1,12,f1,1g";

    // char a[10][10];

    // sscanf(str,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s",a[0],a[1],a[2],a[3],a[4],a[5],a[6]);
    // for(int i =0;i<7;i++){
    //     printf("%s\t",a[i]);
    // }
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    timeinfo->tm_hour-=9;
    printf ( "\007The current date/time is: %s", asctime (timeinfo) );
    return 0;
}