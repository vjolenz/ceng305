#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
	pid_t child1_pid, child2_pid;
	int evenNumberCount = 0, oddNumberCount = 0;
	FILE* file;
    char ch;

    srand((unsigned)time(NULL));

    child1_pid = fork();

    if(child1_pid == 0) {
    	file = fopen("numbers.txt", "w");
    	for(int i = 0; i < 1000000; i++) {
			fprintf(file, "%d ", rand() % 10);
    	}
    	printf("[CHILD1] Wrote 1000000 integers to numbers.txt, terminating.\n");
    	fclose(file);
    } else {
    	printf("[PARENT] Child process ID: %d\n", child1_pid);
    	wait(NULL);

    	child2_pid = fork();

    	if(child2_pid == 0) {
    		file = fopen("numbers.txt", "r");
	    	while((ch = getc(file)) != EOF){
	            if(ch >= '0' && ch <= '9')
	                if(atoi(&ch) % 2 == 0)
	                	evenNumberCount++;
	                else
	                	oddNumberCount++;
	        }
	        fclose(file);
	        printf("[CHILD2] Even numbers: %d, odd numbers: %d, terminating.\n", evenNumberCount, oddNumberCount);
    	} else {
    		printf("[PARENT] Child process ID: %d\n", child2_pid);
    		wait(NULL);
    		printf("[PARENT] Terminating.\n");
    	}
    }
}

