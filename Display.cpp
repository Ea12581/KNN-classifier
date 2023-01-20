#include <iostream>
#include "Display.h"

Display::Display(vector<string> clsifics) {
    setClsifics(clsifics);
}

vector<string> Display::getClsifics() {
    return clsifics;
}
void Display::setClsifics(vector<string> _clsifics) {
    clsifics = _clsifics;
}
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

