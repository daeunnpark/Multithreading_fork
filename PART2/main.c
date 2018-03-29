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


		printf("dddddd-------\n");
		// APP1
		int flag=0;
		int status;	

		char* inputfilename = *(argv+1);
		char* outputfilename = "";
		FILE *fp,*fp2;

		char* N;


		fp = fopen(inputfilename, "r");

		if(fp) {// exists
			fclose(fp);

			printf("ENTER THE APP NUM TO RUN\n");
			scanf("%d",&flag);

			pid_t pid = -10000;

			char *env1[] = { "PATH=/bin:/sbin", NULL };

			if(flag == 1){ 

				char *argv1[] = { "solver", inputfilename , NULL };

				if((pid=fork()==0)){

					if(execve(argv1[0], argv1, env1 )<0){
						printf("ERROR IN EXECVE\n");
						exit(0);
					}

				}

			}



			if(flag == 2){ 

				char *argv1[] = { "trace", inputfilename , NULL }; 

				if((pid=fork()==0)){

					if(execve(argv1[0], argv1, env1 )<0){
						printf("ERROR IN EXECVE\n");
						exit(0);
					}
				}
			}


			if(flag == 3){

				fp = fopen(inputfilename, "r"); 
				N = malloc(sizeof(char)*100000);
				fscanf(fp,"%s", N); 

				char *argv1[] = { "fib", N , NULL }; 

				fclose(fp);


				if(execve(argv1[0], argv1, env1 )<0){
					printf("ERROR IN EXECVE\n");
					exit(0);
				}



			}



			if(flag == 4){ // quit
				exit(0);
			}

			if(flag == 5){ 

				printf("PLEASE ENTER A NEW INPUT FILE NAME\n"); 
				scanf("%s",inputfilename); 


			}
			/*
			   if((pid=fork()==0)){

			   if(execve(argv1[0], argv1, env1 )<0){
			   printf("ERROR IN EXECVE\n");
			   exit(0);
			   }


			   printf("GGGGRRR\n");
			//exit(0);
			}

			 */

			if( waitpid(pid,&status , 0)<0 ){
				printf("ERRROR in waitpid\n");

			} else {
				printf("DONE\n");
			}


			if(flag==3){
				free(N);

			}


			//fclose(fp2);
			//	fclose(fp);





		} else {

			printf("FILE DOES NOT EXIST\n");

		}


	}


	printf("ENDDD\n");
	return 0;
}

