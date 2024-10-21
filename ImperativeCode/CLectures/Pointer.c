


/*
Pointers allow us to understand variables by the
    position they're stored in memory


A C Program has access to a computer's memory as an array of bytes,
    each byte containing 8 bits.
Each byte has a unique position index, which is the address of the byte.

A pointer is a reference to an address in memory. 
Pointers are variables, which live in memory, and thus have an address.
Pointers can also be typed so that they keep information about a type 
    of the item stored at that address.
    int type pointer -> int * pointerName

*/


int i, j, k = 137;
int a[3] = {2, 4, 6};

int *p; 
// here we have created a pointer to an int, not initialised,
// so it may point to anything!

p = &k; // p now points to k, that is to the address of k's first byte

// p holds the memory that p is pointing to,
// while *p holds the value stored in the memory p is pointing to

*p = 138; // k now contains 138, since p* resolves to k here
p = &a[2]; // p now points to the last element of array a
*p = 3; // a[2] now contains 3, since p* resolves to a[2] here

// the two lines below are exactly the same.
// They both make p point to the first element of a
p = &a[0];
p = a;



// Pointer Arithemtic
// If p points to a[1], p + 1 points to a[2]



// The two declarations and initialisations below are nearly identical
char s[] = "bat"; // string as array of char variables
char *p = "bat"; // pointer to string constant
// p is a pointer to a string constant which means it cannot be updated


// two functions below take the same argument
void print1 (char s[]) {
    return 0;
}
void print2 (char *s) {
    return 0;
}


/*
the structure of the main function now becomes clear
    it takes n, the number of arguments,
    and an array of pointer to characters.
Each of these pointers point to the first element 
    of a char array representing a string.
We can pass n seperate strings into our program from the console. 
*/

// 
//


int main (int n, char *args[n]) {
    return 0;
}






// constancy and Pointer
void op(const int *x, // int value *x is read only. The value cannot change
        int *const y) { // pointer is fixed to an address, but the value can change

    

        }




