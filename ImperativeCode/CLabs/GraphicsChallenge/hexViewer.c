#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    FILE *file = fopen("textfile.txt", "rb");
    unsigned char c = fgetc(file);
    while (! feof(file)) {
        printf("%x", c);
        printf(" ");
        c = fgetc(file);
    }
    printf("\n");
    fclose(file);


}