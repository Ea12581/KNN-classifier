
#include <string.h>
#include <string>
#include <ctype.h>
#include <regex.h>
#include "CheckInput.h"

using namespace std;


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

/*
* Function Name: isLegalIp
* Input: string input1
* Output: bool (true for legal, false for illegal ip)
* Function operation: Checks if the string is in a legal ip format.
*/
bool isLegalIp(string input1) {
    regex_t ip_format;
    int reti;
    char msgbuf[100];

    /* Compile regular expression of ip address*/
    reti = regcomp(&ip_format, "^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)\\.?\\b){4}$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    /* Execute regular expression */
    reti = regexec(&ip_format, input1, 0, NULL, 0);
    if (!reti) {
        return true;
    } else if (reti == REG_NOMATCH) {
        return false;
    } else {
        regerror(reti, &ip_format, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }
}
