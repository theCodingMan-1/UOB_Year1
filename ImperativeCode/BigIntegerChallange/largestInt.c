/*Find the limits of the int type*/

#include <stdio.h>

int largestInt(int lower, long upper) {
    long mid = lower + ((upper - lower) / 2);
    int test = mid;
    
    if (test == mid) {
        lower = mid;
    }
    else {
        upper = mid;
        
    }
    if (upper - lower < 2) {
        return test;
    }

    return largestInt(lower, upper);

}

int main(void) {
    int n = largestInt(0, 2500000000);
    printf("The largest int is %d\n", n);
    return 0;
}
