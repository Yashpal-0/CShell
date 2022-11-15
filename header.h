#ifndef header_h
#define header_h
#include<stdio.h>
#include<pwd.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/utsname.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>
#include<grp.h>
#include<time.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<signal.h>

char** redirect(char** tokens);
void jobs();
char **tokenize(char *command,char* delimiter);
void killp(char** tokens);
// void run(char* command);
// void run_background(char** tokens);

#endif