#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>


int convert(const char length[]) {

    if (length[0] == '0') return -1; // no leading 0 -> "03" rejected

    char *endptr;
    int num = strtol(length, &endptr, 10);
    // length is the string to be converted
    // endptr used to store the pointer to the first character after the numeric value
    // 10 represents the base of the number system.

    if (endptr == length) return -1;
    // this means no digits were found within the string (i.e "hello")

    else if (*endptr != '\0') return -1;
    // invalid character within the set (i.e "4y")
    // this is because the characters do not have null characters after them

    else if (num <= 0) return -1;
    // if it is a negative number it returns -1
    // also if it is a number bigger than 214748367 it doesn't fit within the integers
    //      so it rolls over to the negatives which will return -1
    //      (i.e 214748367 + 1 = -214748368)

    else return num;


}




int main(int n, char *args[n]) {
    setbuf(stdout, NULL);
    // if (n == 1) {
    //     test();
    // }
    if (n == 3) {
        if (strcmp(args[1], "char") == 0){
            printf("this is a char");
        }
        int num = convert(args[2]);
        printf("Type of num is %d\n", num);
        // if (a == char) printf("hey\n");
        // else printf("no\n");
        

    }
    else {
        printf("Use e.g.: ./visualise char 7\n");
    }
    return 0;
}
