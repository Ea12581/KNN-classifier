#include <iostream>
#include "Display.h"

/*
* A consturctor with a vector of classifications as strings.
* the command descreption and the IO object.
*/
Display::Display(vector<string> clsifics, string _desc, DefaultIO _dio) {
    setClsifics(clsifics);
    setDesc(_desc);
    setDio(_dio);
}

/*
* A getter for the classifications.
*/
vector<string> Display::getClsifics() {
    return clsifics;
}

/*
* A setter for the classifications.
*/
void Display::setClsifics(vector<string> _clsifics) {
    clsifics = _clsifics;
}

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
    if (clsifics.size() == 0) {
        cout << "please upload data" << endl;
    } else if (clsifics[0] == "") {
        cout << "please classify the data" << endl;
    } else {
        string list = "";
        for (int i = 1; i <= clsifics.size(); i++) {
            string index = to_string(i);
            list.append(index);
            list.append(" ");
            list.append(clsifics[i]);
            list.append("\n");
        }
        list.append("Done.\n");
    }
}

