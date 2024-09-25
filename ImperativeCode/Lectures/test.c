#include <stdio.h>

int main(void){
    int myVarName = 42; 
    /*myVarName is the variable's name or identifier. 
    We only need to specify the type (int) once.
    The first point of use is called the decleration of the variable*/ 

    myVarName = 43;
    // This reassigns the value

    int length;
    scanf("%d", &length); // allows inputs. saves the value inputed into the variable 'length'

    printf("%d\n", length);
}

/*Local veriables can only be usd within the curly brackets {} of the procedure. 
The curly brackets are the scope of the variable*/

//NO GLOBAL VARIABLES


/* 
Addition -> x + y
Subtraction -> x - y
Multiplication -> x * y
Division -> x / y
Remainder -> x % y
*/


