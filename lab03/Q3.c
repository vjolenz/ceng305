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

	if(argc < 5) {
		printf("All the required arguments weren't provided! Terminating..\n");
		exit(-1);
	}

	printf("[PARENT] Creating first process...!\n");

	pid = fork();

	if(pid == 0) {
		fileName = args[1];
		numOfNumbers = atoi(args[3]);
		file = fopen(fileName, "w");

		printf("[CHILD1] Writing %d random integers to %s\n", numOfNumbers, fileName);

		for(int i = 0; i < numOfNumbers; i++) {
			fprintf(file, "%d\n", rand() % 1001);
		}

		fclose(file);
	} else {
		// seed again to prevent producing same numbers since child2 doesnt wait for child1
		// which means they normally use same timestamp to produce random number
		srand(time(NULL) % 50); 
		printf("[PARENT] Creating second process...!\n");

		pid = fork();

		if(pid == 0) {
			fileName = args[2];
			numOfNumbers = atoi(args[4]);
			file = fopen(fileName, "w");

			printf("[CHILD2] Writing %d random integers to %s\n", numOfNumbers, fileName);

			for(int i = 0; i < numOfNumbers; i++) {
				fprintf(file, "%d\n", rand() % 1001);
			}

			fclose(file);
		} else {
			wait(NULL); // wait first child
			wait(NULL); // wait second child

			printf("[PARENT] Creating third process...!\n");

			pid = fork();

			if(pid == 0) {
				char command[100];
				printf("[CHILD3] Sorting both files:\n");

				sprintf(command, "cat %s %s | sort -n", args[1], args[2]);

				system(command);
			} else {
				wait(NULL); // wait third child
				printf("[PARENT] Done.\n");
			}
		}
	}
}