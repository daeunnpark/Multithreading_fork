#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <inttypes.h> 
#include <time.h>

struct wallets {
	uint32_t key;
	int money;
};

void print_help() {}

uint32_t key_gen() {
	uint32_t key = rand() & 0xff;
	key |= (rand() & 0xff) << 8;
	key |= (rand() & 0xff) << 16;
	key |= (rand() & 0xff) << 24;
	//	printf("key");
	//	printf("%" PRIu32 "\n", key);	
	return key;
}

uint32_t money_gen() {
	uint32_t money = rand() % 100;
	return money;
}

void generate_wallets(struct wallets* wallet, int num_wallets) {
	int i = 0;
	// int num_wallets = 5000000;
	for (i; i < num_wallets; ++i) {
		wallet[i].key = key_gen();
		wallet[i].money = money_gen();
	}
}

void print_wallets(FILE* fp, int num_wallets, struct wallets* wallet) {
	int i = 0;
	for (i; i < num_wallets; ++i){
		fprintf(fp, "wallet: ");		
		fprintf(fp, "%" PRIu32 "; money: ",wallet[i].key);
		fprintf(fp, "%" PRIu32 "\n", wallet[i].money);
		//	fprintf(fp, "wallet: %x; money: %d\n", wallet[i].key, wallet[i].key);
	}
}

int main(void) {
	printf("Welcome to the BTC wallet tracker.\n");
	srand(time(NULL));

	char* filename = (char*)malloc(255);
	char* command = (char*)malloc(255);
	FILE* fp = NULL;
	FILE* fp2 = NULL;
	int num_wallets;
	int is_generated = 0;
	int is_printed = 0;
	pid_t pid;
	int forkflag = 0;

	while(1){
		printf("Please enter the file name that contains number of wallets: ");
		scanf("%s", filename);
		fp = fopen(filename, "r");


		if(fp){

			fscanf(fp, "%d", &num_wallets);
			fclose(fp);
			struct wallets* wallet = (struct wallets*)malloc(num_wallets * sizeof(struct wallets));

			printf("Type 'help' for list of available commands.\n");
prompt:
			printf("prompt> ");
			int n = scanf("%s", command);

			if (strcmp(command, "help") == 0) {
				pid = getpid();        

				//printf("Current Process ID is : %d\n",pid);
				//printf("[ Forking Child Process ... ] \n");

				pid =fork();


				if (pid == 0) { // child
					char *argv1[]={"./print_help", NULL};
					execvp(argv1[0],argv1);

					// iff it fails, returns here
					printf("execvp failed");
					exit(0);	
				} else { // parent
					//	printf("%d: going to sleep for a while - child %d might die while I snooze\n",(int)getpid(), (int)pid);
					sleep(1);
					int status; 
					//zombie here  
					//system("ps -eo pid,ppid,stat,cmd"); 
					if( waitpid(pid,&status , 0)<0 ){ 
						printf("ERROR IN WAITPID\n");
						exit(0);
					}
					//no zoombie 
					//system("ps -eo pid,ppid,stat,cmd"); 
					//	printf("%d: awake\n", (int)getpid());
				}

				goto prompt;
			}
			else if (strcmp(command, "generate") == 0) {
				if (!is_generated) {
					is_generated = 1;
					generate_wallets(wallet, num_wallets);
				}
				else
					printf("Wallets are already generated.\n");
				goto prompt;
			}
			else if (strcmp(command, "print") == 0) {
				if (!is_printed) {
					if(is_generated)	{		
						is_printed = 1;

						fp2 = fopen("wallets_info.dat", "w");
						print_wallets(fp2, num_wallets, wallet);
						fclose(fp2);        
					}	
					else{

						printf("No wallet is generated.\n");
					}
				} else {
					printf("Wallets are already printed.\n");
				}	
				goto prompt;
			}
			else if (strcmp(command, "quit") == 0){
				free(wallet);
				break;				
				//return 0;
			} else {
				printf("Unknown command.\n");
				goto prompt;
			}

		}
		else{
			printf("FILE DOES NOT EXIST\n"); 

		}
	}

	free(filename);
	free(command);
	return 0;
}
