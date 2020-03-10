#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include<sys/wait.h>   
#include<string.h>

void join_pipe(int* left, int* right, char** arr) {
    if(fork()==0) {
        if(left) {
		    close(left[1]);
	        dup2(left[0],STDIN_FILENO);
	        close(left[0]);  
        }

	    if(right) {
            close(right[0]);
		    dup2(right[1],STDOUT_FILENO);
		    close(right[1]);
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
    int left[2], right[2];
	i=0;
	pipe(right);
	join_pipe(NULL, right,cmdlist[i]);
	left[0] = right[0]; // output pipe becomes input pipe 
	left[1] = right[1];
	
	for(i=1;i<x-1;i++) {

	 	pipe(right);
        join_pipe(left, right,cmdlist[i]);
        close(left[0]);
        close(left[1]);
        left[0] = right[0];
     	left[1] = right[1];
	}

	join_pipe(left,NULL,cmdlist[x-1]);
	close(left[0]);
	close(left[1]);
}
