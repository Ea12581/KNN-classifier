#include <iostream>
#include "Display.h"

/*
* Func name: execute
* Input: none
* Output: none
* Function operation: if classification vector is of size 0,
* asks for data to be uploaded. if the first classification is empty,
* asks for the data to be classified. else, creates a string with the
* list of classifications.
*/
void Display::execute() {
    string output;
    if (!getSd()->isUnClaExists()) {
        output = "please upload data";
    } else if (!getSd()->isClassifiedExists()) {
        output = "please classify the data";
    } else {
        for (int i = 1; i <= getSd()->getClassified()->size(); i++) {
            string index = to_string(i);
            output.append(index);
            output.append(" ");
            output.append((*(getSd()->getClassified())).at(i-1).getClassification());
            output.append("\n");
        }
        output.append("Done.");
    }
    getDio()->write(output);
}

