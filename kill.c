#include "header.h"

extern int n,bgpid[100];

void killp(char** tokens)
{
    int num;
    int signal;
    sscanf(tokens[1],"%d",&num);
    sscanf(tokens[2],"%d",&signal);
    if(num>n)
    printf("No process available");
    else{
        kill(bgpid[num-1],signal);
    }

}