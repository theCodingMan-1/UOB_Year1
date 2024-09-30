/*WHILE LOOPS*/

#define _POSIX_C_SOURCE 200809L 
#include <unistd.h>
// POSIX cross-platform libraries.
// creates a portable interface to the operating system for tasks like timing control etc...
// Generally to go beyond the standard libraries you need to find libraries, which are abailable across platforms

#include <stdio.h>

int main(void) {
    int t = 10;

    // as long as the expression is true, the block is executed again and again
    while (t > 0) { 
        sleep(1);
        printf("%d\n", t);
        t--;
    }
    return 0;
}






#include <math.h>
#include <stdio.h>

double root(double x) {
    double r = x / 2.0; // first guess
    double epsilon = 1E-14;
    while (fabs(r - x/r) > epsilon) {
        // if r = sqrt(x) then |r - x/r| = 0. This means we must get the difference between r and x/r to be as small as possible. 

        r = (r + x / r) / 2.0;
        // if r is incorrect we redefine it as the mid point between r and x/r
    }
    return r;
}


/*
The more your code jumps about, the harder it is to debug.
Code that jumps excessively is spaghetti code. 
Whenever possible control jumps by using function calls and while loops.
*/





