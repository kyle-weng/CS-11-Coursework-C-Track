#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "linked_list.h"
#include "memcheck.h"

node *quicksort(node *input_list, int numberNodes) {
    int i;
    node *tempList = copy_list(input_list);
    node *copyOfList = copy_list(input_list);
    node *smaller, *largerEqual, *temp, *final;
    int n_nodesSmaller = 0;
    int n_nodesLargerEqual = 0;
    smaller = NULL;
    largerEqual = NULL;

    if (numberNodes == 0 || numberNodes == 1) {
        return copyOfList;
    }

    for (i = 0; i < numberNodes; i++) {
        if (tempList->data < copyOfList->data) {
            temp = create_node(tempList->data, smaller);
            smaller = temp;
            n_nodesSmaller++;
        }
        else {
            temp = create_node(tempList->data, largerEqual);
            largerEqual = temp;
            n_nodesLargerEqual++;
        }
        tempList = tempList->data;
    }
    smaller = quicksort(smaller, n_nodesSmaller);
    largerEqual = quicksort(largerEqual, n_nodesLargerEqual);

    final = append_lists(smaller, create_node(copyOfList->data,\
        largerEqual->data));
    final = append_lists(final, largerEqual);

    return final;
}

int main(int argc, char *argv[]) {

    int i; /* iterator */
    int qCmdArg = 0; /* 1 if -q is in command line arguments, suppress output */
    int n_nodes = 0; /* number of nodes */
    node *list; /* pointer to the list */
    node *temp; /* temporary pointer */
    node *sortedList;
    list = NULL; /* empty list */

    if (argc == 1) { /* if there are no command line arguments */
        fprintf(stderr, "usage: quicksort [-q] number1 [number2 ... ]\n");
        return 1;
    }


    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-q") == 0) {
            qCmdArg = 1;
        }
        else {
            temp = create_node(atoi(argv[i]), list);
            list = temp;
            n_nodes++;
        }
    }

    /* if there are too many or no integer arguments */
    if (n_nodes == 0) {
        fprintf(stderr, "usage: quicksort [-q] number1 [number2 ... ]\n");
        return 1;
    }

    /* sort */
    sortedList = quicksort(list, n_nodes);

    /* print if -q is not present */
    if (qCmdArg == 0) {
        print_list(sortedList);
    }

    return 0;
}
