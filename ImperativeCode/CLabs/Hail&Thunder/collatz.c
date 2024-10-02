#include <stdio.h>

int collatz(int num) {
    
    if (num == 1) {
        return 1;
    }
    else {
        int next;
        printf("%d\n", num);
        if (num % 2 == 0) {
            next = collatz(num / 2);
        }
        else {
            next = collatz((3 * num) + 1);
        }
        return next;
    }
}

int main(void) {
    int num;
    printf("Enter a number to collatz:\n");
    scanf("%d", &num);
    int coll = collatz(num);
    printf("%d\n", coll);
}
