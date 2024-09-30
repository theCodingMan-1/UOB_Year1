// #include <stdio.h>
//     setbuf(stdout, NULL);  --> apparently makes sure everything you printf is outputted. 



// literals -> int num = 70. we don't know what that 70 is! How do we know it changes. 

// constants -> allows you to define something that doesn't change: const int EXAMPLE = 100. 
// Its possible to define them outside the program

const int FIRSTBOUNDRY = 70;
const int SECONDBOUNDRY = 50;
const int THIRDBOUNDRY = 40;

int grade(int mark) {
    int grade;
    if (mark >= FIRSTBOUNDRY) grade = 1;
    else if (mark >= SECONDBOUNDRY) grade = 2;
    else if (mark >= THIRDBOUNDRY) grade = 3;
    else grade = 4;
    return grade;
}


//enumeration -> another way of assigning identifiers to non-changing items (indexed as integer values)

int enumeration(void) {
    enum {MON, TUE, WED, THU, FRI, SAT, SUN};
    // where this is almost the same as:
    // const int MON = 0, TUE = 1, ..., SUN = 6;

    // constants defined by enum are fixed as integers. They cannot be another type

    enum WeekDays {MON, TUE, WED, THU, FRI, SAT, SUN};
    enum WeekDays current = WED;
    // 'enum WeekDays' is a type that is used to define a variable
}
