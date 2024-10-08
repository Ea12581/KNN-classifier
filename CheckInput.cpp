
#include <string.h>
#include <string>
#include <ctype.h>
#include <regex.h>
#include "CheckInput.h"

using namespace std;

/*
* Function Name: isNumber
* Input: char input1[] (an array of characters)
* Output: bool (true for a number, false otherwise)
* Function operation: Checks if a string is a positive number.
*/
bool isNumber(char input2[]) {
    int size = strlen(input2);
    for (int i = 0; i < size; i++) {
        if(!isdigit(input2[i])) {
            return 0;
        }
    }
    return 1;
}

/*
* Function Name: isNumber
* Input: const char input1[] (an array of characters)
* Output: bool (true for a number, false otherwise)
* Function operation: Checks if a string is a positive number.
*/
bool isNumber(const char input2[]) {
    int size = strlen(input2);
    for (int i = 0; i < size; i++) {
        if(!isdigit(input2[i])) {
            return 0;
        }
    }
    return 1;
}

/*
* Function Name: isLegalPort
* Input: int number
* Output: bool (true for legal, false for illegal port)
* Function operation: Checks if the number can be used as a port, that he is in range of 1024-65535.
*/
bool isLegalPort(int input2) {
    return input2 >= 1024 && input2 <= 65535;

}
