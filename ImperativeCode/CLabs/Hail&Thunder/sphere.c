#include <stdio.h>

int surface(double radius) {
    double area = 4 * 3.14 * radius * radius;
    return area;
}

int main(void) {
    double radius;
    printf("Enter the radius:\n");
    scanf("%lf", &radius);
    printf("The surface area of sphere of radius %lf is %lf\n", radius, surface(radius));
    return 0;
    
}
