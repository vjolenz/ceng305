#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void sigintHandler();

// 1 for increasing, -1 for decreasing
static int operation = 1;

int main() {
    signal(SIGINT, sigintHandler);
    srand((unsigned)time(NULL));
    
    int randomNumber = rand() % 100 + 100;

    printf("[Increasing]\n");
    while(1) {
        randomNumber += 10 * operation;
        printf("Variable: %d\n", randomNumber);
        if(randomNumber > 200 || randomNumber < 100)
            exit(0);
        sleep(1);
    }
    return 0;
}

void sigintHandler() {
    operation *= -1;
    printf("\n[%s]\n", (operation == 1) ? "Increasing" : "Decreasing");
}
