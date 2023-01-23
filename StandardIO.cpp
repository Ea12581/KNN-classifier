#include <iostream>
#include <string>
#include "StandardIO.h"
    
    /*
    * Function Name: read
    * Input: None
    * Output: string (the input from the user)
    * Function Operation: Gets input from the user and returns it.
    */
    string StandardIO::read()  {
        string input;
        getline(std::cin, input);
        return input;
    }

    /*
    * Function Name: write
    * Input: string output (the string to output)
    * Output: none
    * Function Operation: Prints the string to output.
    */
    void StandardIO::write(string output) {
        cout << output << endl;
    }