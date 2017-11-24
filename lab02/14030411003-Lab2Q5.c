#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void sigintHandler();

// 1 for random number, -1 for random letter
static int operation = 1;

int main() {
    signal(SIGINT, sigintHandler);
    srand((unsigned)time(NULL));
    char *letters = "abcdefghijklmnopqrstuvwxyz";
    int randomNumber;
    int printCount = 0;

    while(1) {
        if(printCount == 15)
            exit(0);

        randomNumber = rand() % 26;

        if(operation == 1)
            printf("%d\n", randomNumber);
        else
            printf("%c\n", letters[randomNumber]);

        sleep(1);
        printCount++;
    }
    return 0;
}

void sigintHandler() {
    operation *= -1;
    printf("\n");
}
