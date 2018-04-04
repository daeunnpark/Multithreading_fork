#include <stdlib.h>				
#include <stdio.h>
#include <stdint.h>  
#include <inttypes.h> 
#define trace main  

int trace2(int row1, int col1, int row2, int col2, int **data1, int **data2);

int trace (int argc, char** argv){ 

	char *inputfilename = *(argv+1);
	char *outputfilename= "part2_trace.dat";
	int row1 =0, col1=0, row2=0, col2 = 0;

	FILE *fp,*fp2;
	fp = fopen(inputfilename, "r");  

	// 1st Matrix
	fscanf(fp,"%d %d", &row1, &col1);

	int **data1, i, c, d;
	data1=(int **) malloc(row1*sizeof(int *));

	for(i=0;i<row1;++i){
		data1[i]=(int *) malloc(col1*sizeof(int));
	}

	//printf("ROW: %d\n", row1);
	//printf("COL: %d\n", col1);  

	for (c = 0; c < row1; c++){
		for (d = 0; d < col1; d++){
			fscanf(fp, "%d", &data1[c][d]);    
		}
	}

/*
	printf("FIRST MAT:\n");

	for (c = 0; c < row1; c++) {
		for (d = 0; d < col1; d++){
			printf("%d\t", data1[c][d]);
		}
		printf("\n");
	}
*/
	// 2nd Matrix
	fscanf(fp,"%d %d", &row2, &col2); 
	int **data2;

	data2=(int **) malloc(row2*sizeof(int *));

	for(i=0;i<row2;++i){
		data2[i]=(int *) malloc(col2*sizeof(int));
	}


	for (c = 0; c < row2; c++){
		for (d = 0; d < col2; d++){
			fscanf(fp, "%d", &data2[c][d]);
		}
	}


/*
	printf("second MAT:\n");

	for (c = 0; c < row2; c++) {
		for (d = 0; d < col2; d++){
			printf("%d\t", data2[c][d]);
		}
		printf("\n");
	}
*/
	fp2 = fopen(outputfilename,"w+"); 
	fprintf(fp2, "%d\n",trace2(row1, col1, row2, col2, data1, data2));

	for(i=0;i<row1;++i){
		free(data1[i]);
	}


	for(i=0;i<row2;++i){
		free(data2[i]);
	}

	free(data1);
	free(data2);

	fclose(fp2);
	fclose(fp);

}




// ALLOC FOR MULT?
int trace2(int row1, int col1, int row2, int col2, int **data1, int **data2) {
	int c, d, k, sum=0, trace = 0;
	int multiply[row1][col2];

	for (c = 0; c < row1; c++) {
		for (d = 0; d < col2; d++) {
			for (k = 0; k < row2; k++) {
				sum = sum + (data1[c][k] * data2[k][d]);
			}

			multiply[c][d] = sum;
			sum = 0;
		}
	}

	/*
	   for (c = 0; c < row1; c++) {
	   for (d = 0; d < col2; d++){
	   printf("%d\t", multiply[c][d]);
	   }
	   printf("\n");
	   }
	 */

	for (c = 0; c < row1; c++) {
		for (d = 0; d < col2; d++){
			if(c==d){
			trace+=multiply[c][d];	
			}	
}
	}

	return trace;
}



