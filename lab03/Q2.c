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
		printf("[CHILD1] Writing %d random chards to %s\n", numOfNumbers, fileName);
		char *letters = "abcdefghijklmnopqrstuvwxyz";
		file = fopen(fileName, "w");

		for(int i = 0; i < numOfNumbers; i++) {
			fprintf(file, "%c", letters[rand() % 26]);
		}

		fclose(file);
	} else {
		wait(NULL); // wait first child

		printf("[PARENT] Creating second process...!\n");

		pid = fork();

		if(pid == 0) {
			char command[100];

			sprintf(command, "zip %s.zip %s", fileName, fileName);

			printf("[CHILD2] Executing zip command...\n");
			system(command);
		} else {
			wait(NULL); // wait second child

			printf("[PARENT] Creating third process...!\n");

			pid = fork();

			if(pid == 0) {
				char command[100];

				sprintf(command, "ls -la | awk '{print $5, $9}' | grep %s", fileName);

				printf("[CHILD3] Executing ls command...\n");
				system(command);
			} else {
				wait(NULL); // wait third child
				printf("[PARENT] Done.\n");
			}
		}

		
	}
}