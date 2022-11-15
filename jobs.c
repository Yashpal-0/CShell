#include "header.h"
extern int bgpid[100];
void jobs()
{
    int i=0;
    char path[100];
    while(bgpid[i]!=0)
{
    int fd;
    char** token=malloc(sizeof(char*)*100);
    sprintf(path, "/proc/%d/stat",bgpid[i]);
    // printf("%s\n",path);
    fd=open(path,O_RDONLY);
    if(fd>=0)
    {
        char buffer[100];
    lseek(fd,0,SEEK_SET);
    read(fd,buffer,sizeof(buffer));
    token=tokenize(buffer," \n");
    printf("[%d] ",i+1);
    if(token[2][0]=='R'||token[2][0]=='S')
    printf("Running ");
    else 
    printf("Stopped ");
    printf("%s ",token[1]);
    printf("[%d]\n",bgpid[i]);
    }
    i++;
    
}

}