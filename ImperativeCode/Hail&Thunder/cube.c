#include <stdio.h>

int cube(int num) {
    int cubed = num * num * num;
    return cubed;
}

int main(void) {
    int num;
    printf("Enter a number:\n");
    scanf("%d", &num);
    printf("The cube of %d is %d\n", num, cube(num));
    return 0;
    
}
