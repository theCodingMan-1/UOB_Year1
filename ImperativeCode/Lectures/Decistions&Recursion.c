int minimum(int x, int y) {
    int min;
    if (x < y) min =  x;
    else min = y;
    return min;
}

int nextHailstone(int x) {
    int next;
    if (x % 2 == 1) {
        int base = 3 * x;
        next = base + 1;
    }
    // an if (or else) statement can be follwed by a block {}, instead of a single statement


    else next = x / 2;
    return next;
}

int nextHailstone(int x) {
    int next;
    switch (x % 2) {
        case 1: next = 3 * x + 1; break; // if (x % 2) == 1 this case is ran
        default: next = x / 2; // otherwise if none of the cases are fulfilled, the default case is run
    }
    return next;
}



int grade(int mark) {
    int grade;
    if (mark >= 70) grade = 1;
    else if (mark >= 50) grade = 2;
    else if (mark >= 40) grade = 3;
    else grade = 4;
    return grade;
}




//find the sum of the numbers from 1 to n. RECURSIVE
int sum(int n) {
    if (n = 1) return 1;
    else return n + sum(n - 1);
}





int example(int var);  // declaration of signature only
// prototyping allows us to call procedures before the program point at wich they are defined.

int main(void) {
    return 0;
}

int example(int var) {  
    // full definition with body
    int example;  // cannot call the function example in this procedure as the variable example overshadows the function
    return 0;
}