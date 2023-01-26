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
        output = "please upload data\n";
    } else if (!getSd()->isClassifiedExists()) {
        output = "please classify the data\n";
    } else {
        for (int i = 0; i < getSd()->getClassified()->size(); i++) {
            string index = to_string(i + 1);
            output.append(index);
            output.append(" ");
            output.append((*(getSd()->getClassified())).at(i).getClassification());
            output.append("\n");
        }
        output.append("Done.");
    }
    getDio()->write(output);
    //get finish massage from client
    getDio()->read();
}

