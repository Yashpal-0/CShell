#include "header.h"

int o_original,i_original;

char** redirect(char** tokens)
{
    int flag=0,f_d,loc,f_id;
    int j=1;
    char** t_tokens=(char **)malloc(sizeof(char*)*100);
    o_original=dup(STDOUT_FILENO);
    i_original=dup(STDIN_FILENO);
    t_tokens[0]=tokens[0];
    // printf("orignal %d\n",o_original);
    for(int i=1;tokens[i]!=NULL;i++)
    {
        if((strcmp(tokens[i],">"))&&(strcmp(tokens[i],">>"))&&(strcmp(tokens[i],"<"))&&(strcmp(tokens[i-1],">"))&&(strcmp(tokens[i-1],">>"))&&(strcmp(tokens[i-1],"<")))
         {
             t_tokens[j]=tokens[i];
             printf("%s\n",t_tokens[j]);
             j++;
         }
        //printf("%s\n",t_tokens[j]);
        if(strcmp(tokens[i],">")==0)
        {
            // printf("helllo\n");
            f_d=open(tokens[i+1],O_WRONLY| O_CREAT | O_TRUNC,0644);
            // printf("fd %d",f_d);
            dup2(f_d,STDOUT_FILENO);
            // printf("/n fd%d",STDOUT_FILENO);
            //loc=i;
            //close(fd);
        }
        else if(strcmp(tokens[i],">>")==0)
        {
            //printf("Hello");
            f_d=open(tokens[i+1],O_WRONLY | O_CREAT | O_APPEND, 0644);
            dup2(f_d,STDOUT_FILENO);
            // loc=i;
            //close(fd);
        }
        else if(strcmp(tokens[i],"<")==0)
        {
            if(f_id=open(tokens[i+1],O_RDONLY)<0)
            {
                //printf("HEllo");
                perror("Error");
                exit(1);
                //return NULL;
            }
            printf("hello");
            lseek(f_id,0,SEEK_SET);
            dup2(f_id,STDIN_FILENO);
            
        }
    }
    // return t_tokens;
    // for(int i=1;tokens[i]!=NULL;i++)
    // {
    //     if(i!=loc&&i!=loc+1)
        
    //     printf("%s",tokens[i]);
    // }
    // //fflush(stdout);
    //dup2(o_original,STDOUT_FILENO);
    // close(o_original);
    //close(STDOUT_FILENO);
    //dup2(original,STDOUT_FILENO);
    //close(original);//close(fd);
    
}