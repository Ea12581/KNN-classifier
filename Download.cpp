#include <iostream>
#include <fstream>
#include "Download.h"

/*
* A consturctor with a vector of classifications as strings,
* and a path. the command descreption and the IO object.
*/
Download::Download(vector<string> clsifics, string path, string _desc, DefaultIO _dio) {
    setClsifics(clsifics);
    setPath(path);
    setDesc(_desc);
    setDio(_dio);
}

/*
* A getter for the classifications.
*/
vector<string> Download::getClsifics() {
    return clsifics;
}

/*
* A setter for the classifications.
*/
void Download::setClsifics(vector<string> _clsifics) {
    clsifics = _clsifics;
}

/*
* A getter for the path.
*/
string Download::getPath() {
    return path;
}

/*
* A setter for the path.
*/
void Download::setPath(string _path) {
    path = _path;
}

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
    string list = "";
    std::ofstream file(path);
    if (clsifics.size() == 0) {
        cout << "please upload data" << endl;
    } else if (clsifics[0] == "") {
        cout << "please classify the data" << endl;
    } else if (!file) {
        cout << "couldn't create the file!" << endl;
    } else if (file) {
        for (int i = 1; i <= clsifics.size(); i++) {
            string index = to_string(i);
            list.append(index);
            list.append(" ");
            list.append(clsifics[i]);
            list.append("\n");
        }
        list.append("Done.\n");
        file << list;
    }
    if (!file) {
        cout << "couldn't create the file!" << endl;
    } else {
        file << list;
    }
}