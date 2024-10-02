#include <stdio.h>

const int FIRSTBOUNDRY = 70;
const int UPPERSECONDBOUNDRY = 60;
const int LOWERSECONDBOUNDRY = 50;
const int THIRDBOUNDRY = 40;


char finalGrade(int percentage) {
    char grade[12];
    if (FIRSTBOUNDRY <= percentage <= 100) {
        grade = "First";
    }

    else if (percentage >= UPPERSECONDBOUNDRY) {
        grade = "Upper Second";
    }

    else if (percentage >= LOWERSECONDBOUNDRY) {
        grade = "Lower Second";
    }

    else if (percentage >= THIRDBOUNDRY) {
        grade = "Third";
    }

    else if (percentage >= 0) {
        grade = "Fail";
    }

    else {
        grade = "INVALID MARK";
    }

    return grade;
}

int main(void) {
    int percentage;
    printf("Enter the mark (0 - 100)%%:\n");
    scanf("%d", &percentage);
    printf("Your grade is: %s\n", finalGrade(percentage));
    return 0;

}

