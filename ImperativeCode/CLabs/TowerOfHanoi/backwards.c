/*
Returns the reverse of a string. If Hello is entered:
o
l
l
e
H
is returned.
*/

#include <stdio.h>

int backwards(char word[], int num) {
    if (num == strlen(word) - 1) {
        printf("%c\n", *(word + num));
    }

    else {
        backwards(word, num + 1);
        printf("%c\n", *(word + num));
    }
}

int main(void) {
    char word[50];
    printf("Enter a word:\n");
    scanf("%s", &word);
    backwards(word, 0);
    return 0;
}
