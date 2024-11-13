#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


int main(void) {
    const int max = 100;
    FILE *extra = fopen("textfile.txt", "a");
    fprintf(extra, "\n");
    fclose(extra);
    FILE *file = fopen("textfile.txt", "r");
    FILE *newFile = fopen("newTextFile.txt", "w");
    char line[max];
    char newLine[max];
    fgets(line, max, file);
    while (! feof(file)) {
        int i = 0;
        while (i < strlen(line)) {
            newLine[i] = toupper(line[i]);
            i++;
        }
        newLine[i] = '\0';
        fprintf(newFile, ("%s\n", newLine));
        printf("%s\n", newLine);
        fgets(line, max, file);
    }
    fclose(file);
    fclose(newFile);

}
