#include <iostream>
#include <fstream>
#include "Download.h"

/*
* Func name: execute
* Input: none
* Output: none
* Function operation: if classification vector is of size 0,
* asks for data to be uploaded. if the first classification is empty,
* asks for the data to be classified. else, if the file could be
* created, prints a message. else, create a file with the list
* of classifications.
*/
void Download::execute() {
    //string path = getDio().read();
    //std::ofstream file(path);
    string output;
    if (!getSd()->isUnClaExists()) {
        output = "please upload data\n";
    } else if (!getSd()->isClassifiedExists()) {
        output = "please classify the data\n";
    /*} else if (!file) {
        output = "couldn't create the file!\n";
    } else if (file) {*/
    } else {
        int length = getSd()->getClassified()->size();
            for (int i = 0; i < length; i++) {
                string index = to_string(i + 1);
                output.append(index);
                output.append(" ");
                output.append((*(getSd()->getClassified())).at(i).getClassification());
                output.append("\n");
            }

        getDio()->write(output);
            //get finish massage
            getDio()->read();
    }
}