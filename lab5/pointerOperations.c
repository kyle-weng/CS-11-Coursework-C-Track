/*
 * The program runs a 1 - dimensional cellular automata. It takes two input
 * arguments: the number of cells in the automata and the number of generations
 * to compute. For each generation, the program computes and prints it.
 */
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "memcheck.h"

/* print the current automata */
void printAutomata(int arrayIn[], int num_elements) {
    int index;
    for (index = 0; index < num_elements; index++) {
        if (arrayIn[index] == 0) {
            printf(".");
        }
        else {
            printf("*");
        }
    }
    printf("\n");
}

/* update the state of the automata according to the given rules

   if the current cell is empty and if one of the two adjacdent cells
   is full (but not both), set the current cell to be full

   in all other cases, set the cell to be empty

 */
void update(int stateOld[], int stateNew[], int num_elements) {
    int index;
    int *previous;
    int *current;
    int *next;
    int *currentNew;

    previous = &stateOld[0];
    current = &stateOld[1];
    next = &stateOld[2];
    currentNew = &stateNew[0];

    /* first cell */
    if (*next == 1 && *current == 0) {
        *currentNew = 1;
    }
    else {
        *currentNew = 0;
    }
    currentNew++;

    /* this covers all cells but the first and the last */
    for (index = 1; index < num_elements - 1; index++) {
        if (*previous != *next && *current == 0) {
            *currentNew = 1;
        }
        else {
            *currentNew = 0;
        }
        previous++;
        current++;
        next++;
        currentNew++;
    }

    /* last cell */
    if (*previous == 1 && *current == 0) {
        *currentNew = 1;
    }
    else {
        *currentNew = 0;
    }
}

int main(int argc, char *argv[]) {
    int numberOfCells = atoi(argv[1]);
    int numberOfGenerations = atoi(argv[2]);
    int i, j;
    /*
    int arr[numberOfCells];
    int arrNew[numberOfCells];
    */
    int *arr;
    int *arrNew;

    arr = (int *) calloc(numberOfCells, sizeof(int));
    arrNew = (int *) calloc(numberOfCells, sizeof(int));

    if (argc != 3) {
        fprintf(stderr, "usage: arrayOperations x y\n\
            x = number of cells in 1dCA\n\
            y = number of generations to compute\n");
        return 1;
    }
    srand(time(0));

    /* randomly seed arr with 1's and 0's */
    for (i = 0; i < numberOfCells; i++) {
        j = (rand() % 2);
        arr[i] = j;
    }

    while (numberOfGenerations > 0) {
        update(arr, arrNew, numberOfCells);
        numberOfGenerations--;
        for (i = 0; i < numberOfCells; i++) {
            arr[i] = arrNew[i];
        }
        printAutomata(arr, numberOfCells);
    }

    free(arr);
    free(arrNew);
    return 0;
}
