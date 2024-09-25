/*Find the area of paint I need*/

#include <stdio.h>

// area must be defined before main. main is always defined last
//always use camelCase for concise variable and function names

/*
int area(int length, int width, int height) {
    return 2 * (width  + length) * height + length * width;
}

int main(void){
    printf("The paint area is %d\n", area(5, 3, 2));
    // %d is a conversion specification that "prints the integer in a decimal form"
    return 0;
}
*/

int area(int length, int width, int height) {
    int sides = 2 * length * height; 
    // Good practise to intialise variables at decleration, so they have a well defined value at all points of the program
    int ends = 2 * width * height;
    int ceiling = length * width;
    return sides + ends + ceiling;
}

int main(void){
    int total = area(5, 3, 2);
    printf("The paint area is %d\n", total);
    // %d is a conversion specification that "prints the integer in a decimal form"
    return 0;
}

