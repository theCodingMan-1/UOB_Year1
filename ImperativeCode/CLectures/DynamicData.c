
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// malloc allows data to persist until you free it explicitly
void example(){
    const int N = 6;
    int *ip = malloc(N * sizeof(int)); // allocates N integers worth of memory
}


// the heap is used for dynamically allocated memory,
// which needs to persist outside scope boundries. 


int main () {
    char *s = malloc(4); // creates 'char s[4]' but persistent.
    // The variable declared (s) is a pointer to the first element
    // of the allocated memory

    strcpy(s, "cat");
    // though "cat" is only three bytes, we need to assign
    // 4 in malloc since the null character takes up a byte

    printf("%s\n", s);
    free(s); // releasing memory, string disappears here
    return 0;


}


// a heap never shrinks. Gaps just appear after 'free'




// when assigning integers you need to create more memory
int integerExample() {
    int *numbers1 = malloc (10 * sizeof(int));
    // this creates enough memory for 10 numbers

    // An alternative function is the calloc function.
    // This clears memory for the memory.
    int *numbers2 = calloc(10, sizeof(int));

    return 0;

}

int reallocation (){
    int capacity = 4;
    char *s = malloc(capacity);
    capacity = capacity * 3/2;
    s = realloc(s, capacity);
    // reallocates a larger amount of memory to s

    free(s);
    return 0;
}