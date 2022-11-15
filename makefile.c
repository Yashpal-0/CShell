#include "header.h"

char* homedir,*prev_dir;
extern int o_original,i_original;
int bgpid[100]={0},n=0;


void run_background(char** tokens)
{
    
    pid_t pid=fork();
    bgpid[n]=pid;
    n++;
    if(pid==0)
    {
        int c_pid=getpid();
        char * exitstatus=malloc(sizeof(char)*100);
        //setpgid(0,0);
        if(execvp(tokens[0],tokens)<0)
        {
            sprintf(exitstatus,"%s with pid %d exited abnormally\n",tokens[0],c_pid);
            perror(exitstatus);
            exit(1);
        }
        sprintf(exitstatus,"%s with pid %d exited normally\n",tokens[0],c_pid);
        perror(exitstatus);
        exit(0);
    }
    else
    {
        printf("%d",pid);
    }
}



void run_foreground(char** tokens)
{
    pid_t pid;
    pid=fork();
    if(pid==0)
    {
        if(execvp(tokens[0],tokens)==-1)
        {
            printf("jdfjd\n");
            perror("Error:");
            exit(0);
        }
    }
    else
    {
        int status;
        waitpid(pid,&status,0);
    }
}

void switchtosystem(char** tokens)
{
    int i=0;
    while(tokens[i]!=NULL)
    {
        i++;
    }
    // printf("%d\n",i);
    // printf("%s\n",tokens[i-1]);
    // printf("%ld\n",strlen(tokens[i-1]));
    // printf("%c",tokens[i-1][strlen(tokens[i-1])-1]);
    if(tokens[i-1][strlen(tokens[i-1])-1]=='&')
    {
        tokens[i-1][strlen(tokens[i-1])-1]='\0';
        printf("switching to background\n");
        //printf("%s\n",tokens[i-1]);
        run_background(tokens);
    }
    else
    {
        printf("Hellow\n");
        run_foreground(tokens);
    }
}


void ls(char** tokens)
{
    int i=1,no_dir=0;
    int aflag=0,lflag=0;
    char **path=(char**)malloc(100*sizeof(char*));
    path[0]=".";
    while(tokens[i]!=NULL)
    {
        if(strcmp(tokens[i],"-a")==0)
        {
            aflag=1;
        }
        else if(strcmp(tokens[i],"-l")==0)
        {
            lflag=1;
        }
        else if(strcmp(tokens[i],"-al")==0 || strcmp(tokens[i],"-la")==0)
        {
            aflag=1;
            lflag=1;
        }
        else
        {
            path[no_dir]=tokens[i];
            no_dir++;
        }
        i++;
    }
    if(no_dir==0)
    {
        no_dir=1;
    }
    for(int j=0;j<no_dir;j++)
    {
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir (path[j])) != NULL) {
            
            while ((ent = readdir (dir)) != NULL) {
                if(aflag==0)
                {
                    if(ent->d_name[0]!='.')
                    {
                        if(lflag==0)
                        {
                            printf ("%s \n", ent->d_name);
                        }
                        else
                        {
                            struct stat fileStat;
                            char date[25];
                            stat(ent->d_name,&fileStat);
                            
                            printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
		                    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
		                    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
		                    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
		                    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
		                    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
		                    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
		                    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
		                    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
		                    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
		                    printf(" %ld ",fileStat.st_nlink);
                            struct passwd *pw = getpwuid(fileStat.st_uid);
                            struct group  *gr = getgrgid(fileStat.st_gid);
                            if(pw!=NULL)
                            {
                                printf("%15s ",pw->pw_name);
                            }
                            else
                            {
                                printf("%15d ",fileStat.st_uid);
                            }
                            if(gr!=NULL)
                            {
                                printf("%15s ",gr->gr_name);
                            }
                            else
                            {
                                printf("%15d ",fileStat.st_gid);
                            }
                            printf("%12ld ",fileStat.st_size);
                            strftime(date, 20, "%b %d %H:%M ", localtime(&(fileStat.st_mtime)));
                            printf(" %s ",date);
                            printf("%s\n",ent->d_name);
                        }
                    }
                }
                else
                {
                    if(lflag==0)
                    {
                        printf ("%s \n", ent->d_name);
                    }
                    else
                    {
                        struct stat fileStat;
                        char date[25];
                        stat(ent->d_name,&fileStat) ;
                        
                            printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
		                    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
		                    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
		                    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
		                    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
		                    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
		                    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
		                    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
		                    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
		                    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
		                    printf(" %2ld ",fileStat.st_nlink);
                            struct passwd *pw = getpwuid(fileStat.st_uid);
                            struct group  *gr = getgrgid(fileStat.st_gid);
                            if(pw!=NULL)
                            {
                                printf("%15s ",pw->pw_name);
                            }
                            else
                            {
                                printf("%15d ",fileStat.st_uid);
                            }
                            if(gr!=NULL)
                            {
                                printf("%15s ",gr->gr_name);
                            }
                            else
                            {
                                printf("%15d ",fileStat.st_gid);
                            }
                            printf("%12ld ",fileStat.st_size);
                            strftime(date, 20, "%b %d %H:%M ", localtime(&(fileStat.st_mtime)));
                            printf(" %s ",date);
                            printf("%s\n",ent->d_name);
                        }
                    }
            }
            closedir (dir);
    }
        else
        {
            perror ("");
            return;
        }
    }      
}
// to break string into tokens
char** tokenize(char* str, char* delimiter)
{
    char** tokens = (char**)malloc(sizeof(char*) * 100);
    int i = 0;
    char* token = strtok(str, delimiter);
    while(token != NULL)
    {
        tokens[i] = token;
        token = strtok(NULL, delimiter);
        i++;
    }
    tokens[i] = NULL;
    return tokens;
}

//function: get home directory
char *get_home_dir()
{
    struct passwd *pwd =(struct passwd *)malloc(sizeof(struct passwd));
    pwd = getpwuid(getuid());
    return pwd->pw_dir;
}
//username

char *username()
{
    struct passwd *pw = getpwuid(getuid());
    return pw->pw_name;
}

//current directory

char *currentdir()
{
    char *cwd = malloc(sizeof(char) * 1024);
    getcwd(cwd, 1024);
    return cwd;
}
// to run each command

void run(char* command)
{
    char** tokens = tokenize(command, " \t");
    // tokens=redirect(tokens);
    if(strcmp(tokens[0], "cd") == 0)
    {
        if((tokens[1] == NULL)||strcmp(tokens[1],"~")==0)
        {
            prev_dir = currentdir();
            chdir(homedir);
        }
        else if(strcmp(tokens[1],"-")!=0)
        {
             char *temp=prev_dir;
                prev_dir=currentdir();
             if(chdir(tokens[1]))
             {
                 perror("Error:");
                 prev_dir=temp;
             }
        }
        else if(strcmp(tokens[1],"-")==0)
        {
            if(prev_dir == NULL)
            {
                printf("No previous directory found");
            }
            else
            {
            char *temp = currentdir();
            chdir(prev_dir);
            prev_dir = temp;
            }
        }
    }
    else if(strcmp(tokens[0], "pwd") == 0)
    {
        char *cwd = currentdir();
        printf("%s\n", cwd);
    }
    else if(strcmp(tokens[0], "exit") == 0)
    {
        exit(0);
    }
    else if(strcmp(tokens[0], "echo") == 0)
    {
        int j=1;
        while(tokens[j] != NULL)
        {
            printf("%s ", tokens[j]);
            j++;
        }
        printf("\n");
    }
    else if(strcmp(tokens[0],"ls")==0)
    {   
        ls(tokens);

    }
    else if(strcmp(tokens[0],"history")==0)
    {
        int i=0;
        int fd=open("history.txt",O_RDONLY);
        char *buf=(char *)malloc(sizeof(char)*100);
        lseek(fd,0,SEEK_SET);
        
        while(read(fd,buf,100))
        {
            
            printf("%s",buf);
        }
        close(fd);
    }
    else if(strcmp(tokens[0],"pinfo")==0)
    {
        pid_t pid;
        int flag=0;
        char path[100],*buffer=(char *)malloc(sizeof(char)*1000),*svptr=(char *)malloc(sizeof(char)*1000);
        if(tokens[1]==NULL)
        {
            pid=getpid();
        }
        else
        {
            sscanf(tokens[1],"%d",&pid);
            printf("%d",pid);
        }
        sprintf(path,"/proc/%d/stat",pid);
        int fd=open(path,O_RDONLY);
        if(fd==-1)
        {
            perror("Error:");
            return;
        }
        printf("pid -- %d\n",pid);
        read(fd,buffer,1000);
        char *token=strtok_r(buffer," ",&svptr);
        int i=0;
        while(token!=NULL)
        {
    
            if(i==2)
            {
                printf("Process Status: %s\n",token);
                break;
            }
            token=strtok_r(NULL," ",&svptr);
            i++;
        }
        close(fd);
        sprintf(path,"/proc/%d/statm",pid);
        fd=open(path,O_RDONLY);
        if(fd==-1)
        {
            perror("Error:");
            return;
        }
        read(fd,buffer,1000);
        token=strtok_r(buffer," \n",&svptr);
        printf("memory: %s\n",buffer);
        if(tokens[1]==NULL)
        printf("Executable Path: %s \n",currentdir());
        close(fd);

    }
    else if(strcmp(tokens[0],"discover")==0)
    {
        //discover the given file from the home directory
        
    }
    else if(strcmp(tokens[0],"jobs")==0)
    {
        jobs();
    }
    else if(strcmp(tokens[0],"sig")==0)
    {
        killp(tokens);
    }
    else 
    {
        //printf("hellow owrld");
        switchtosystem(tokens);
    }
}


void run_command(char* command)
{
    char** tokens = tokenize(command,";");
    int i = 0;
    while(tokens[i] != NULL)
    {
        run(tokens[i]);
        i++;
    }
}
int main()
{
    char *input;
    input=(char*)malloc(sizeof(char) *200 );
    size_t size=200;
    homedir = currentdir();
    char devicename[100];
    while(1)
    {
        int fd;
        gethostname(devicename,sizeof(devicename));
        fflush(stdout);
        fflush(stdin);
        dup2(i_original,STDIN_FILENO);
        dup2(o_original,STDOUT_FILENO);
        printf("%s@%s:~%s>", username(),devicename,currentdir());
        // printf("%d",bgpid[2]);
        fgets( input, size, stdin);
        fd=open("history.txt",O_CREAT | O_RDWR | O_APPEND,0666);
        write(fd,input,strlen(input));
        input[strlen(input)-1]='\0';
        run_command(input);
        close(fd);
    }
            return 0;

}
