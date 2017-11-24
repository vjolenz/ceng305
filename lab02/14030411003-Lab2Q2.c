#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t child1_pid, child2_pid;
    int letterCount = 0, numberCount = 0;
    FILE* file;
    char ch;

    child1_pid = fork();

    if(child1_pid == 0) {
        file = fopen("data.txt", "r");
        while((ch = getc(file)) != EOF){
            if(ch >= '0' && ch <= '9')
                numberCount++;
        }
        fclose(file);
        printf("[CHILD1] Number count: %d\n", numberCount);
    } else {
        printf("[PARENT] Child process ID: %d\n", child1_pid);

        child2_pid = fork();

        if(child2_pid == 0) {
            file = fopen("data.txt", "r");
            while((ch = getc(file)) != EOF){
                if(ch > '9')
                    letterCount++;
            }
            fclose(file);
            printf("[CHILD2] Letter count: %d\n", letterCount);
        } else {
            printf("[PARENT] Child process ID: %d\n", child2_pid);
        }
    }

    wait(NULL); // wait until all child processes to exit

    return 0;
}
