#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> 
#include <sys/wait.h>


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

		//printf("gg\n");    
	}
}

void print_wallets(FILE* fp, int num_wallets, struct wallets* wallet) {
	int i = 0;
	for (i; i < num_wallets; ++i)
		fprintf(fp, "wallet: %x; money: %d\n", wallet[i].key, wallet[i].key);
}

int main(void) {
	printf("Welcome to the BTC wallet tracker.\n");
	srand(time(NULL));

	char* filename = (char*)malloc(255);
	char* command = (char*)malloc(255);
	FILE* fp = NULL;
	int num_wallets;
	int is_generated = 0;
	int is_printed = 0;
	pid_t pid;
	int forkflag = 0;
	printf("Please enter the file name that contains number of wallets: ");
	scanf("%s", filename);
	fp = fopen(filename, "r");
	fscanf(fp, "%d", &num_wallets);
	fclose(fp);
	struct wallets* wallet = (struct wallets*)malloc(num_wallets * sizeof(struct wallets));

	printf("Type 'help' for list of available commands.\n");
prompt:
	printf("prompt> ");
	scanf("%s", command);
	if (strcmp(command, "help") == 0) {
		pid = -10000;        
		if ((pid = fork()) == 0) {
			forkflag=1;
			printf("tTT----\n");
			char *argv1[]={"./print_help", NULL};
			if( execvp(argv1[0],argv1) <0){
				printf("ERROR in execvp\n");
				exit(0);
			}
			printf("THIS MAYBe\n");
		}

		sleep(1);
		if(forkflag){
			printf("sssss\n");		
			int status; 
			if( waitpid(pid,&status , 0)<0 ){ 
				printf("ERROR IN WAITPID");
			}

			forkflag=0;
		}
		//execvp("./print_help", NULL);

		goto prompt;
	}
	else if (strcmp(command, "generate") == 0) {
		if (!is_generated) {
			is_generated = 1;
			generate_wallets(wallet, num_wallets);
			printf("DONE?\n");
		}
		else
			printf("Wallets are already generated.\n");
		goto prompt;
	}
	else if (strcmp(command, "print") == 0) {
		if (!is_printed) {
			is_printed = 1;
			filename = "wallets_info.dat";
			fp = fopen(filename, "w");
			print_wallets(fp, num_wallets, wallet);
			fclose(fp);        
		}
		else
			printf("Wallets are already printed.\n");
		goto prompt;
	}
	else if (strcmp(command, "quit") == 0)
		return 0;
	else {
		printf("Unknown command.\n");
		goto prompt;
	}
	return 0;
}
