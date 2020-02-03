#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include<sys/wait.h>   
#include<string.h>

void join_pipe(int* lpipe, int* rpipe, char** arr) {
    if(fork()==0) {
        if(lpipe) {
		    close(lpipe[1]);
	        dup2(lpipe[0],STDIN_FILENO);
	        close(lpipe[0]);  
        }

	    if(rpipe) {
            close(rpipe[0]);
		    dup2(rpipe[1],STDOUT_FILENO);
		    close(rpipe[1]);
	    }

     	execvp(arr[0],arr);
    }
}    

int main(int argc, char *argv[]) {
    int i,j,count=1,x=0;
    int status;
    int n=argc-1;
    char* str=NULL;
    char** arr = (char**) malloc(n*sizeof(char*));
    for ( i = 0; i < n; i++) {   
       str = argv[i];
       arr[i] = str;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
	   if(str[0]!='-'&& str[0]!='+' )
		x++;	   
   	}

	int* len=(int*) malloc(x* sizeof(int));
   	char*** cmdlist =(char***) malloc((x)*sizeof(char**));
   	int k=0;
	for(i=0;i<n;i=i+count) {

        printf("Command: ");	  
        char * name= arr[i];
        count=1;
        for(j=i+1;j<n;j++) {
            if(arr[j][0]=='-'||arr[j][0]=='+')
                count++;
            else
                break;
        }

        char  **myargv = (char **)malloc((count+1) * sizeof(char *));
        myargv[0]=arr[i];
        for(j=0;j<count;j++){
            myargv[j]=arr[i+j];
            printf("%s ",myargv[j]);
        }
        myargv[count]=NULL;
	    len[k] =count;
	    cmdlist[k++]=myargv;
	    printf("\n");
  	}
    //	printf("%d\n",x);

	k=0;
    int lpipe[2], rpipe[2];
	i=0;
	pipe(rpipe);
	join_pipe(NULL, rpipe,cmdlist[i]);
	lpipe[0] = rpipe[0]; // output pipe becomes input pipe 
	lpipe[1] = rpipe[1];
	
	for(i=1;i<x-1;i++) {

	 	pipe(rpipe);
        join_pipe(lpipe, rpipe,cmdlist[i]);
        close(lpipe[0]);
        close(lpipe[1]);
        lpipe[0] = rpipe[0];
     	lpipe[1] = rpipe[1];
	}

	join_pipe(lpipe,NULL,cmdlist[x-1]);
	close(lpipe[0]);
	close(lpipe[1]);
}
