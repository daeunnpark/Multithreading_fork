#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <string.h>

int main (int argc, char** argv){


	if(argc<2){

		printf("PLEASE ENTER A INPUT FILE\n");
		exit(0);

	} else {


		printf("APP STARTS-------\n");
		char* app = malloc(sizeof(char)*10);		
		int flag=0;
		int status;	

		char* inputfilename = *(argv+1);
		//char* outputfilename = "";
		FILE *fp,*fp2;

		char* N;

		fp = fopen(inputfilename, "r");

		while(fp){	

			printf("ENTER THE NAME OF APP TO RUN\n");
			scanf("%s",app);
			pid_t pid = -10000;
			char *env1[] = { "PATH=/bin:/sbin", NULL };

			printf("app: %s\n",app);

			if( strcmp(app,"solver")==0 ){
				char *argv1[] = { "solver", inputfilename , NULL };


				if((pid=fork()==0)){
					if(execve(argv1[0], argv1, env1 )<0){
						printf("ERROR IN EXECVE\n");
						exit(0);
					}

				}

			}


			if( strcmp(app,"trace")==0 ){  
				char *argv1[] = { "trace", inputfilename , NULL }; 

				if((pid=fork()==0)){
					if(execve(argv1[0], argv1, env1 )<0){
						printf("ERROR IN EXECVE\n");
						exit(0);
					}
				}
			}


			if( strcmp(app,"fib")==0 ){
				N = malloc(sizeof(char)*100000);
				fscanf(fp,"%s", N); 

				char *argv1[] = { "fib", N , NULL }; 


				if((pid=fork()==0)){   
					if(execve(argv1[0], argv1, env1 )<0){
						printf("ERROR IN EXECVE\n");
						exit(0);
					}
				}

			}

			if( strcmp(app,"quit")==0 ){ 		

				fclose(fp); 
				free(app);		
				exit(0);
			}

			
if( strcmp(app,"change")==0 ){ 
				fclose(fp); 
				printf("PLEASE ENTER A NEW INPUT FILE NAME\n"); 
				scanf("%s",inputfilename); 

				//printf("NEW INTPUT FILE NAME : %s\n", inputfilename);
				fp = fopen(inputfilename, "r"); 

			}



			if( (strcmp(app,"solver")==0 ) ||  strcmp(app,"trace")==0 || ( strcmp(app,"fib")==0  )){
				if( waitpid(pid,&status , 0)<0 ){
					printf("ERRROR in waitpid\n");

				} else {
					printf("DONE\n");
				}

			}



			if( strcmp(app,"fib")==0 ){ 			
				free(N);

			}


		}// while

	}

	printf("FILE DOES NOT EXIST\n");
	printf("ENDDD\n");
	return 0;
}

