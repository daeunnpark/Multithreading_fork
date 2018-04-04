#include <stdlib.h>
#include <stdio.h> 

#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#define solver main



double solver2(double A, double B, double e, int n, double *coefs);
double f(int n, double *coefs, double x);  


double solver (int argc, char** argv){
	//printf("-------IN SOLVER----------------\n");
	int n=0;  
	double A=0, B=0, e=0, *coefs; 

	char *inputfilename = *(argv+1); 
	char *outputfilename = "part2_solver.dat";


	FILE *fp,*fp2; 
	fp = fopen(inputfilename, "r");    

	// read and set variables	
	fscanf(fp, "%d %lf %lf %lf",&n, &e, &A, &B);
	//printf("n: %d e: %f A: %f B: %f\n",n, e, A, B);
	coefs = malloc((n+1)*sizeof(double));


	int i;
	for (i=0; i<n+1;i++){
		fscanf(fp, "%lf", &coefs[i]);
		//	printf("coef : %f\n", coefs[i] );
	}

	// write output
	fp2 = fopen(outputfilename,"w+");
	fprintf(fp2, "%f\n",solver2(A, B, e, n, coefs));
	free(coefs);


	fclose(fp2);
	fclose(fp);

	return 0;

}




double solver2(double A, double B, double e, int n, double *coefs){
	double a = A;
	double b = B;
	double x = 0;

	while(1){
		x = (a+b)/2;
		if( fabs(f(n,coefs,a)) < e){//f(n,coefs,a) 
			return a;

		} else if( fabs(f(n,coefs,b)) < e){
			return b;

		} else if( fabs(f(n,coefs,x)) < e){	
			return x;

		} else {
			if( f(n,coefs,x) * f(n,coefs,b)<0){
				a=x;

			} else {
				b=x;
			}
		}
	}
	return x;

}





double f(int n, double *coefs, double x){
	int index = 0;
	double sum = 0;

	while(0<=n){

		sum+=coefs[index]*pow(x,n);
		//printf("POLY : %f.4\n",coefs[index]*pow(x,n));

		n--;
		index++;
	}
	//printf("sum: %lf  ",sum);
	return sum;

}


