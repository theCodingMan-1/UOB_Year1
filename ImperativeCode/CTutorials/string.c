#include <string.h>
#include <stdbool.h>

char myLast(const char str[]) {
    char c = '\0';

    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return str[i - 1];

    // returns the last character in the string.
    // basically goes through the string until it gets to the null character at the end
    // and then returns the character before that
}

void myReverse(const char str[],  char rev[]) {
    int len = strlen(str);
    for (int i = len - 1; i >= 0; i--) {
        rev[len - i - 1] = str[i];
    } 
    rev[len] = '\0'; // must remember to add the null character at the end

    // reverses a string
    // does this by adding each character in the string in front of the once before.
}


bool isPalindrome(const char str[]) {
    char* rev = malloc(strlen(str) + 1);
    myReverse(str, rev);

    int r = strcmp(str, rev);

    free(rev);

    return !r;
    
}






int main(void){
    return 0;
}