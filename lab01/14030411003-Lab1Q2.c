#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int fillArrayRandomly(int* array[]);

int main() {
	int array[1000];
	srand((unsigned)time(NULL));

	FILE *f = fopen("numbers2.txt" , "w");
	for(int i = 0; i < 1000; i++) {
		fprintf(f, "%d\n", rand() % (1000 - 100) + 100);
	}
	fclose(f);

	// Shell expression to find lines that contain numbers between 200 and 299 => cat numbers2.txt | grep "^2"

	return 0;
}
