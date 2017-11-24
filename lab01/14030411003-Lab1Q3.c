#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct Matrix{
	int ** data;
	int rowCount;
	int columnCount;
};

void makeMatrix(struct Matrix *matrix);
void fillMatrixRandomly(struct Matrix *matrix);
void printMatrix(struct Matrix *matrix);


int main() {
   	struct Matrix matrix;
   	matrix.rowCount = 10;
   	matrix.columnCount = 10;
	
	makeMatrix(&matrix);
   	fillMatrixRandomly(&matrix);
   	printMatrix(&matrix);


   	/*
	* Shell expressions to sort the output by 3. column and save it
	* gcc 14030411003-Lab1Q3.c -o q3
	* ./q3 | sort -k 3 -n >> sorted.txt
	*/


   	for(int i = 0; i < matrix.rowCount; i++) {
		free(matrix.data[i]);
	}

	free(matrix.data);

   return 0;
}

void makeMatrix(struct Matrix *matrix) {
	matrix->data = (int**)calloc(matrix->rowCount, sizeof(int*));
	for (int i = 0; i < matrix->rowCount; i++) {
	 	matrix->data[i] = (int *) calloc(matrix->columnCount, sizeof(int));
	}
}

void fillMatrixRandomly(struct Matrix *matrix) {
	srand((unsigned)time(NULL));
	for(int i = 0; i < matrix->rowCount; i++) {
		for(int j = 0; j < matrix->columnCount; j++) {
			matrix->data[i][j] = rand() % 10000;
		}
	}
}
   
void printMatrix(struct Matrix *matrix) {
	for(int i = 0; i < matrix->rowCount; i++) {
		for(int j = 0; j < matrix->columnCount; j++) {
			printf("%d ", matrix->data[i][j]);
		}
		printf("\n");
	}
}

