/*
 * The program sorts all integer arguments (lowest to highest) and then
 * prints them (one element per line). If -q is specificed anywhere in the
 * arguments, output will be suppressed when printing. If -b is specified
 * anywhere in the arguments, bubble sorting will be used instead of minimum
 * element sorting.
 */
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_SIZE 32

/*
 * Sorts elements in the given integer array from lowest to highest using
 * minimum element sort.
 */
void minimumElementSort(int arrayIn[], int num_elements) {
    int start = 0;
    int smallest;
    int index;
    int tempStorage = 0;
    while (start < num_elements) { /* iterate through the input array */
        smallest = start;
        for (index = smallest; index < num_elements; index++) {
            if (arrayIn[index] < arrayIn[smallest]) {
                /* if the element at index is smaller than the element at
                smallest, set smallest equal to index */
                smallest = index;
            }
        }
        /* swap the elements at indices smallest and start */
        tempStorage = arrayIn[smallest];
        arrayIn[smallest] = arrayIn[start];
        arrayIn[start] = tempStorage;
        start++;
    }
}

/*
 * Sorts elements in the given integer array from lowest to highest using
 * bubble sort.
 */
void bubbleSort(int arrayIn[], int num_elements) {
    int index, start, temp;
    for (index = 0; index < num_elements - 1; index++) {
        /* iterate through increasingly smaller portions of the array */
        for (start = 0; start < num_elements - index - 1; start++) {
            if (arrayIn[start] > arrayIn[start + 1]) {
                /* if the element at start is greater than the element after,
                swap the two elements */
                temp = arrayIn[start];
                arrayIn[start] = arrayIn[start + 1];
                arrayIn[start + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {

    int i; /* iterator */
    int start = 0; /* tracks the number of integer arguments */
    int qCmdArg = 0; /* 1 if -q is in command line arguments, suppress output */
    int bCmdArg = 0; /* 1 if -b is in command line arguments, use bubblesort */
    int arr[MAX_SIZE]; /* array of integer values from argv */

    if (argc == 1) { /* if there are no command line arguments */
        fprintf(stderr, "usage: sorter [-b] [-q] number1 [number2 ... ]\
         (maximum 32 numbers)\n");
        return 1;
    }


    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-q") == 0) {
            qCmdArg = 1;
        }
        else if (strcmp(argv[i], "-b") == 0) {
            bCmdArg = 1;
        }
        else {
            arr[start] = atoi(argv[i]); /* fill arr[] with another element */
            start++;
        }
    }
    /* if there are too many or no integer arguments */
    if (start > 32 || start == 0) {
        fprintf(stderr, "usage: sorter [-b] [-q] number1 [number2 ... ]\
         (maximum 32 numbers)\n");
        return 1;
    }

    if (bCmdArg == 1) {
        bubbleSort(arr, start);
    }
    else {
        minimumElementSort(arr, start);
    }

    /* print contents of array */
    for (i = 0; i < start; i++) {
        if (qCmdArg == 0) {
            printf("%d\n", arr[i]);
        }
    }
    return 0;
}
