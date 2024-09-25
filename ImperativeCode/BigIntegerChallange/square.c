/*Calculates squares of numbers*/ 

#include <stdio.h>


int square(int num) {
    return num * num;
}

int main(void) {
    int n;
    printf("Enter an integer:\n");
    scanf("%d", &n);
    printf("The square of %d is %d\n", n, square(n));
    return 0;
}
