#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    char s[100];
    int i;
    int x;

    srand(time(0));
    i = (rand() % 10) + 1;
    printf("Enter your name: ");
    scanf("%99s", s);
    for (x = 0; x < i; x++)
    {
        if (i % 2 == 0) {
            printf("%d: hello, %s!\n", i, s);
        }
        else {
            printf("%d: hi there, %s!\n", i, s);
        }
    }
    return 0;
}
