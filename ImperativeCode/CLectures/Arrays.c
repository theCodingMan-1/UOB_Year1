

int array(void){
    int seq[3]; // declare an erray of 3 int variables
    seq[0] = 10; // initialises first variable
    seq[1] = 5; // initialises second variable
    seq[2] = 4; // initialises third (final) variable

    // seq[3] means it takes up 3 spaces in memory. 
    // Trying to find seq[800] won't work because it is outside the memory assigned to the array

    return 0;
}

int array2(void) {
    int seq[] = {10, 5, 4}; // legal alternative for seq[3]
    return 0;
}

// arrays can't be returned from functions directly. 