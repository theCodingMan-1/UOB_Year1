#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>


int square(int x) {
    return x * x;
}

int (*f) (int);
f = square;
printf("7 x 7 = %d", f(7));