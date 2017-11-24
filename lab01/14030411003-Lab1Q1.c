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
void writeMatrixToFile(struct Matrix *matrix, char fileName[]);


int main(int argc, char *args[]) {
   	struct Matrix matrix;
   	matrix.rowCount = atoi(args[1]);
   	matrix.columnCount = atoi(args[2]);
	
	makeMatrix(&matrix);

   	fillMatrixRandomly(&matrix);
   	writeMatrixToFile(&matrix, "numbers.txt");

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
			matrix->data[i][j] = rand() % 100;
		}
	}
}

void writeMatrixToFile(struct Matrix *matrix, char fileName[]) {
	FILE *f = fopen(fileName, "w");
	for(int i = 0; i < matrix->rowCount; i++) {
		for(int j = 0; j < matrix->columnCount; j++){
			fprintf(f, "%d ", matrix->data[i][j]);
		}
		fprintf(f, "\n");
	}

	fclose(f);
}
