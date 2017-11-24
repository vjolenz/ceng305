#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

int main() {
	pid_t child1_pid, child2_pid;
	FILE* file1 = fopen("data1.txt", "w+");
	FILE* file2 = fopen("data2.txt", "w+");
	char buffer[10];

    srand((unsigned)time(NULL));

    child1_pid = fork();

    if(child1_pid == 0) {
    	char randNumbersStr[21] = "";
    	int randNumber;
    	for(int i = 0; i < 10; i++) {
    		randNumber = rand() % 10;
			fprintf(file1, "%d", randNumber);
			sprintf(buffer, "%d ", randNumber);
			strcat(randNumbersStr, buffer);
    	}
    	printf("[CHILD1] Wrote %s to file\n", randNumbersStr);
    } else {
    	printf("[PARENT] Child process ID: %d\n", child1_pid);

    	child2_pid = fork();

    	if(child2_pid == 0) {
    		char *letters = "abcdefghijklmnopqrstuvwxyz";
    		char randLetter;
    		char randLettersStr[21] = "";
	    	for(int i = 0; i < 10; i++) {
	    		randLetter = letters[rand() % 26];
				fprintf(file2, "%c", randLetter);
				sprintf(buffer, "%c ", randLetter);
				strcat(randLettersStr, buffer);
	    	}
	    	printf("[CHILD2] Wrote %s to file\n", randLettersStr);
    	} else {
    		printf("[PARENT] Child process ID: %d\n", child2_pid);
    		wait(NULL);
            wait(NULL);
    		
    		fseek(file1, 0, SEEK_SET);
    		fseek(file2, 0, SEEK_SET);
    		char readContent[41] = "";
    		for(int i = 0; i < 10; i++) {
    			sprintf(buffer, "%c %c ", getc(file1), getc(file2));
    			strcat(readContent, buffer);
    		}
    		printf("[PARENT] %s\n", readContent);
    		fclose(file1);
    		fclose(file2);
    	}
    }
}

