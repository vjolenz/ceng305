#include <stdio.h>
#include <stdlib.h>

void sigintHandler();

static int total = 0, inputCount = 0;

int main() {
	int input;
    signal(SIGINT, sigintHandler);
    while (1) {
        scanf("%d", &input);

        if (input == -1)
            exit(0);

        total += input;
        inputCount++;
    }

    return 0;
}

void sigintHandler() {
    printf("\nInputs: %d, Average: %.2f\n", inputCount, (float) total / inputCount);
    total = 0;
    inputCount = 0;
}