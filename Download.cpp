#include <iostream>
#include <fstream>
#include "Download.h"

Download::Download(vector<string> clsifics, string path) {
    setClsifics(clsifics);
    setPath(path);
}

vector<string> Download::getClsifics() {
    return clsifics;
}
void Download::setClsifics(vector<string> _clsifics) {
    clsifics = _clsifics;
}

string Download::getPath() {
    return path;
}

void Download::setPath(string _path) {
    path = _path;
}

void Download::execute() {
    string list = "";
    std::ofstream file(path);
    if (clsifics.size() == 0) {
        cout << "please upload data" << endl;
    } else if (clsifics[0] == "") {
        cout << "please classify the data" << endl;
    } else {
        for (int i = 1; i <= clsifics.size(); i++) {
            string index = to_string(i);
            list.append(index);
            list.append(" ");
            list.append(clsifics[i]);
            list.append("\n");
        }
        list.append("Done.\n");
    }
    if (!file) {
        cout << "couldn't create the file!" << endl;
    } else {
        file << list;
    }
}