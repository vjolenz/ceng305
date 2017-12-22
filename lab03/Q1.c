#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>


int main(int argc, char * args[])
{
	srand(time(NULL));

	pid_t pid;
	FILE* file;
	char *fileName;
	int numOfNumbers;

	if(argc < 3) {
		printf("All the required arguments weren't provided! Terminating..\n");
		exit(-1);
	}

	fileName = args[1];
	numOfNumbers = atoi(args[2]);

	printf("[PARENT] Creating first process...!\n");

	pid = fork();

	if(pid == 0) {
		printf("[CHILD1] Creating %s with %d integers..\n", fileName, numOfNumbers);
		file = fopen(fileName, "w");

		for(int i = 0; i < numOfNumbers; i++) {
			fprintf(file, "%d\n", rand() % 1001);
		}

		fclose(file);
	} else {
		wait(NULL); // Wait first child

		printf("[PARENT] Creating second process...!\n");

		pid = fork();

		if(pid == 0) {
			printf("[CHILD2] Executing sort command...\n");
			char command[100];

			sprintf(command, "sort -n %s", fileName);

			system(command);
		} else {
			wait(NULL); // Wait second child

			printf("[PARENT] Creating third process...!\n");

			pid = fork();

			if(pid == 0) {
				file = fopen(fileName, "r");
				char line [1000];
				int min = 9999;
				int max = 0;
				int number;

			    while(fgets(line, sizeof line, file) != NULL) {
			    	number = atoi(line);

			    	if(number < min)
			    		min = number;
			    	
			    	if(number > max)
			    		max = number;
			    }

			    fclose(file);

			    printf("[CHILD3] Min: %d Max: %d\n", min, max);
			} else {
				wait(NULL); // wait third child
				printf("[PARENT] Done.\n");
			}
		}

	}



	return 0;
} 