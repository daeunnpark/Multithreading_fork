#include <stdlib.h>
#include <stdio.h> 
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#define fib main

uint64_t fib2(uint64_t n);

int fib (int argc, char** argv){ 
	char * n = *(argv+1);
	uint64_t N;
	sscanf (n, "%" PRId64 "\n", &N);

	char *outputfilename="part2_fib.dat";
	FILE *fp2;


	fp2 = fopen(outputfilename,"w+");

	fprintf(fp2,"%" PRId64 "\n",fib2(N));
	fclose(fp2);
	return 0;
}

uint64_t fib2(uint64_t n){
	uint64_t a = 0, b = 1, c, i;
	if( n == 0){
		return a;
	}


	for (i = 2; i <= n; i++) {
		c = a + b;
		a = b;
		b = c;
	}

	return b;
}



