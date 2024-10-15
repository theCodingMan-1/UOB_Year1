// Pointers essentially holds reference to an address in memory


int main(void){
    int i, j, k = 137;
    int a[3] = {2, 4, 6}; 
    int *p; // pointer to an int, not initialised
    p = &k; // p now points to the int k
    printf("k is stored at %p\n", p); // print the pointer …

    printf("value in k is %d\n", *p); // print variable pointed to
    *p = 138; // k now contains 138, since *p resolves to k here
    p = &a[2]; // p now points to the last element of the array a
    *p = 3; // a[2] now contains 3, since *p resolves to a[2] here
    p = &a[0]; // p now points to the first element of the array a
    p = a; // p still points to the first element of a
    // since referencing array a IS pointing to the 1st item

    // p holds the memory location of the variable 
    // while *p holds the value of that variable
    return 0;
}

