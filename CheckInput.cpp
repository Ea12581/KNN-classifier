
#include <string.h>
#include <string>
#include <ctype.h>
#include <regex>
#include "CheckInput.h"

using namespace std;

/*
* Function Name: isNumber
* Input: char input1[] (an array of characters)
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

/*
* Function Name: isLegalIp
* Input: string input1
* Output: bool (true for legal, false for illegal ip)
* Function operation: Checks if the string is in a legal ip format.
*/
bool isLegalIp(string input1) {
    regex ip_format("^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)\\.?\\b){4}$");
    return regex_match(input1, ip_format);
}