#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

long long convertToNum(char number[]) {
    if (number[0] == '0' && number[1] != '\0') return -1; // no leading 0 -> "03" rejected

    char *endptr;
    long long num = strtol(number, &endptr, 10);


    if (endptr == number) return -1;
    // this means no digits were found within the string (i.e "hello")

    else if (*endptr != '\0') return -1;
    // invalid character within the set (i.e "4y")
    // this is because the characters do not have null characters after them

    else return num;
}




char* convertToBin(long long num, int power) {
    const int constantPower = power;
    int adder = 0;
    int q = 0;
    if (num / 2 == -4611686018427387904){
        return "1000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000";

    } 
    else{
        long long r = labs(num);
        int memory = constantPower + (constantPower / 4) + 2;
        char output[memory];
        char *p = output;
        while (power > 0) {
            if (power == 63) {
                q = 0;

            }
            else {
                long long divider = pow(2, power);
                q = r / divider;
                r = r % divider;

            }

            

            char qStr[2];
                
            sprintf(qStr, "%d", q);
            output[constantPower - power + adder] = qStr[0];
                    
            if (power % 4 == 0) {
                adder++;
                output[constantPower - power + adder] = ' ';

            }
            power--;
        }
        char rStr[2];
        sprintf(rStr, "%lli", r);
        output[memory - 2] = rStr[0];

        if (num < 0) {
            int counter = memory - 2;
            int zero = 0;
            while (counter >= 0) {
                if ((output[counter] != ' ') && (zero == 1)) {

                    if (output[counter] == '1') output[counter] = '0';
                    else output[counter] = '1';
                }
                if (output[counter] == '1') zero = 1;
                counter--;
            }    
        }
        output[memory - 1] = '\0';
        return p;

    }

}



char* makeChar(char number[]) {
    long long num;
    if ((number[0] == '-') && (number[1] == '1') && (number[2] == '\0')) {
        num = -1;
    }
    else {
        num = convertToNum(number);
        if (num == -1) return "Input error.";

        else if ((num < -128) || (num > 127)) return "Input error.";
    }

    int power = 7;

    return convertToBin(num, power);
}


char* makeInt(char number[]) {
    long long num;
    if ((number[0] == '-') && (number[1] == '1') && (number[2] == '\0')) {
        num = -1;
    }
    else {
        num = convertToNum(number);
        if (num == -1) return "Input error.";

        else if ((num < -2147483648) || (num > 2147483647)) return "Input error.";
    }

    int power = 31;  
    
    return convertToBin(num, power);
}

char* makeLong(char number[]) {
    long long num;
    if ((number[0] == '-') && (number[1] == '1') && (number[2] == '\0')) {
        num = -1;
    }
    else {
        num = convertToNum(number);
        if (num == -1) return "Input error.";

        char backToString[strlen(number) + 1];
        sprintf(backToString, "%lli", num);
        if (strcmp(backToString, number) != 0) return "Input error.";

        
    }

    int power = 63;  
    
    return convertToBin(num, power);

}




char* makeUnChar(char number[]) {


    long long num = convertToNum(number);
    if (num == -1) return "Input error.";

    else if ((num < 0) || (num > 255)) return "Input error.";

    
    int power = 7;

    return convertToBin(num, power);
}



char* makeUnInt(char number[]) {


    long long num = convertToNum(number);
    if (num == -1) return "Input error.";

    else if ((num < 0) || (num > 4294967295)) return "Input error.";

    
    int power = 31;

    return convertToBin(num, power);

}



//---------------------TESTS----------------------------------------------------------------------



void assert(int line, bool b) {
    if (b) return;
    printf("The test on line %d fails.\n", line);
    exit(1);
}



void testChar(void) {
    assert(__LINE__, strcmp(makeChar("-128"), "1000 0000") == 0);
    assert(__LINE__, strcmp(makeChar("-104"), "1001 1000") == 0);
    assert(__LINE__, strcmp(makeChar("43"), "0010 1011") == 0);
    assert(__LINE__, strcmp(makeChar("127"), "0111 1111") == 0);
    assert(__LINE__, strcmp(makeChar("-1"), "1111 1111") == 0);
    assert(__LINE__, strcmp(makeChar("-129"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeChar("128"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeChar("4.5"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeChar("-0.65"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeChar("05"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeChar("4z"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeChar("4T3"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeChar("hello"), "Input error.") == 0);
}


void testInt(void) {
    assert(__LINE__, strcmp(makeInt("-2147483648"), "1000 0000 0000 0000 0000 0000 0000 0000") == 0);
    assert(__LINE__, strcmp(makeInt("-987654321"), "1100 0101 0010 0001 1001 0111 0100 1111") == 0);
    assert(__LINE__, strcmp(makeInt("1234567890"), "0100 1001 1001 0110 0000 0010 1101 0010") == 0);
    assert(__LINE__, strcmp(makeInt("2147483647"), "0111 1111 1111 1111 1111 1111 1111 1111") == 0);
    assert(__LINE__, strcmp(makeInt("-1"), "1111 1111 1111 1111 1111 1111 1111 1111") == 0);
    assert(__LINE__, strcmp(makeInt("-2147483649"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeInt("2147483648"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeInt("4.5"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeInt("-0.65"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeInt("05"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeInt("4z"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeInt("4T3"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeInt("hello"), "Input error.") == 0);
}


void testLong(void) {
    assert(__LINE__, strcmp(makeLong("-9223372036854775808"), "1000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000") == 0);
    assert(__LINE__, strcmp(makeLong("-98765432123456789"), "1111 1110 1010 0001 0001 1101 0101 1100 1101 1110 0011 0001 1000 0010 1110 1011") == 0);
    assert(__LINE__, strcmp(makeLong("1234567890987654321"), "0001 0001 0010 0010 0001 0000 1111 0100 1011 0001 0110 1100 0001 1100 1011 0001") == 0);
    assert(__LINE__, strcmp(makeLong("9223372036854775807"), "0111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111") == 0);
    assert(__LINE__, strcmp(makeLong("-1"), "1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111") == 0);
    assert(__LINE__, strcmp(makeLong("-9223372036854775809"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeLong("9223372036854775808"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeLong("4.5"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeLong("-0.65"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeLong("05"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeLong("4z"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeLong("4T3"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeLong("hello"), "Input error.") == 0);

}



void testUnChar(void){
    assert(__LINE__, strcmp(makeUnChar("0"), "0000 0000") == 0);
    assert(__LINE__, strcmp(makeUnChar("43"), "0010 1011") == 0);
    assert(__LINE__, strcmp(makeUnChar("255"), "1111 1111") == 0);
    assert(__LINE__, strcmp(makeUnChar("-1"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeUnChar("256"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeUnChar("4.5"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeUnChar("-0.65"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeUnChar("05"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeUnChar("4z"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeUnChar("4T3"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeUnChar("hello"), "Input error.") == 0);


}



void testUnInt(void) {
    assert(__LINE__, strcmp(makeUnInt("0"), "0000 0000 0000 0000 0000 0000 0000 0000") == 0);
    assert(__LINE__, strcmp(makeUnInt("1234567890"), "0100 1001 1001 0110 0000 0010 1101 0010") == 0);
    assert(__LINE__, strcmp(makeUnInt("4294967295"), "1111 1111 1111 1111 1111 1111 1111 1111") == 0);
    assert(__LINE__, strcmp(makeUnInt("-1"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeUnInt("4294967296"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeUnInt("4.5"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeUnInt("-0.65"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeUnInt("05"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeUnInt("4z"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeUnInt("4T3"), "Input error.") == 0);
    assert(__LINE__, strcmp(makeUnInt("hello"), "Input error.") == 0);

}



void test(void) {
    testChar();
    testInt();
    testLong();
    testUnChar();
    testUnInt();
    printf("All Tests Pass!\n");
}



int main(int n, char *args[n]) {
    setbuf(stdout, NULL);
    if (n == 1) {
        test();
    }
    else if (n == 3) {
        if (strcmp(args[1], "char") == 0) printf("%s\n", makeChar(args[2]));
        else if (strcmp(args[1], "int") == 0) printf("%s\n", makeInt(args[2]));
        else if (strcmp(args[1], "long") == 0) printf("%s\n", makeLong(args[2]));
        else {
            printf("Use e.g.: ./visualise char 7\n");
        }
    }
    else if (n == 4) {
        if ((strcmp(args[1], "unsigned") == 0) && (strcmp(args[2], "char") == 0)){
            printf("%s\n", makeUnChar(args[3]));
        }
        else if ((strcmp(args[1], "unsigned") == 0) && (strcmp(args[2], "int") == 0)){
            printf("%s\n", makeUnInt(args[3]));
        }

        else {
            printf("Use e.g.: ./visualise unsigned char 7\n");
        }
        

    }
    else {
        printf("Use e.g.: ./visualise char 7\n");
    }
    return 0;
}
