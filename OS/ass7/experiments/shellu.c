#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
#define LSH_TOK_PIPE "|"
#define LSH_TOK_BOOL "&&||;"


void execArgsPiped(char** parsed, char** parsedpipe) 
{ 
    // 0 is read end, 1 is write end 
  int pid=fork();
  int pfd[2];
  pipe(pfd);

  if(pid!=0)
  {
    wait(NULL);
  }
  else
  {
    
    int pid_1=fork();
    if(pid_1!=0)
    {
      close(pfd[0]);
      dup2(pfd[1],1);
      close(pfd[1]);
      //char *S[]={"./write"};
      execv(parsedpipe[0],parsedpipe);
      
      
    }
    else
    {
      wait(NULL);
      close(pfd[1]);
      dup2(pfd[0],0);
      close(pfd[0]);
      //char *T[]={"./wc"};
       execv(parsed[0],parsed);
    }
  }
} 


char **parseSpace(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}


char **parsePipe(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  token = strtok(line, LSH_TOK_PIPE);
  while (token != NULL) {
    tokens[position] = token;
    //printf("%s\n",token);
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
    }

    token = strtok(NULL, LSH_TOK_PIPE);
  }
  tokens[position] = NULL;
  return tokens;
}

char **parseBool(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  token = strtok(line, LSH_TOK_BOOL);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

int check_pipe(char *s){
  int i=0;
  int count=0;
  while(s[i+1]!='\0'){
    if(s[i]=='|' && s[i+1]=='|')
      return 0;
    else if(s[i]=='|')
      count++;
    i++;
  }
  return count;
}

int check_b(char *s){
  int i=0;
  int count=0;
  while(s[i+1]!='\0'){
    if(s[i]=='&' && s[i+1]=='&')
      return 1;
    else if(s[i]=='|' && s[i+1]=='|')
      return 2;
    else if(s[i]==';')
      return 3;
    i++;
  }
  return count;
}

int main()
{
	while(1){
    printf("\n");
		printf(">  ");
		int flag=0;
		char cwd[1024]; 
		char s[100];
		size_t size=100;
		fgets(s, 100, stdin);
    char *internal[]={"cd","clear","pwd","exit"};
		int len=strlen(s);
    int p_c;
    if((p_c=check_pipe(s))>0){
  		char **par=parsePipe(s);
      // printf("p1 %s",par[0]);
      // printf("p2 %s",par[1]);
  		char **d[0];
      d[0]=parseSpace((char*)par[0]);
      d[1]=parseSpace((char*)par[1]);
  		execArgsPiped(d[0],d[1]);
    }

    else if(check_b(s)){
      char **par=parseBool(s);
      char **d[2];
      d[0]=parseSpace((char*)par[0]);
      d[1]=parseSpace((char*)par[1]);
      if(fork()==0){
          for(int i=0;i<4;i++){
          d[0][0][strlen(d[0][0])]='\0';
          //printf("%d",i);
          if(strcmp(d[0][0],internal[i])==0){
            if(i==0){
              chdir(d[0][1]);
            }

            if(i==1){
              system("clear");
              main();
            }

            if(i==2){
               getcwd(cwd, sizeof(cwd)); 
            }
            if(i==3)
              exit(1);
          }

          execvp(d[0][0],d[0]);
        }

      }
      else{
        wait(0);
      }

      if(fork()==0){
        char df[100];
        int ind=0;
        for(int h=1;d[1][0][h]!='\0';h++){
          df[ind++]=d[1][0][h];
        }
        df[ind]='\0';
        strcpy(d[1][0],df);
          for(int i=0;i<4;i++){
          d[1][0][strlen(d[1][0])]='\0';
          //printf("%d",i);
          if(strcmp(d[1][0],internal[i])==0){
            if(i==0){
              chdir(d[1][1]);
            }

            if(i==1){
              system("clear");
              main();
            }

            if(i==2){
               getcwd(cwd, sizeof(cwd)); 
            }
            if(i==3)
              exit(0);
          }

          execvp(d[1][0],d[1]);
        }
      }
      else
        wait(0);


    }

    else{
  		char **st;
  		st=parseSpace(s);
  		
  		

  		for(int i=0;i<4;i++){
  			st[0][strlen(st[0])]='\0';
  			//printf("%d",i);
  			if(strcmp(st[0],internal[i])==0){
  				if(i==0){
  					chdir(st[1]);
  				}

  				if(i==1){
  					system("clear");
  					main();
  				}

  				if(i==2){
  					 getcwd(cwd, sizeof(cwd)); 
  				}
  				if(i==3)
  					exit(0);
  			}
  		}

  		if(fork()==0){
  			execvp(st[0],st);
  		}
  		else{
  			wait(NULL);
  		}
    }
	}
	return 0;
}