/*Calculates Intrest*/

#include <stdio.h>

double add(double amount, double intrestRate){
    int gained = amount * intrestRate * 0.01;
    return amount + gained;

}

int main(void) {
    double a, i;
    printf("Enter an amount:\n");
    scanf("%lf", &a);
    printf("Enter an interest rate (%%):\n");
    scanf("%lf", &i);
    double total = add(a, i);
    printf("Adding %.2lf%% intrest to £%.2lf gives £%.2lf\n", i, a, total);
    return 0;
}
