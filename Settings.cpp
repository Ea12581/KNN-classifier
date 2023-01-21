#include <iostream>
#include "Settings.h"
#include "CheckInput.h"
#define DEFAULT_K 5
#define DEFAULT_METRIC "EUC"


/*
* A consturctor command descreption and the IO object.
*/
Settings::Settings(string _desc, DefaultIO _dio, string _input) {
    setDesc(_desc);
    setDio(_dio);
    setInput(_input);
    setK(DEFAULT_K);
    setMetric(DEFAULT_METRIC);

}

/*
* A getter for the k value.
*/
int Settings::getK() {
    return k;
}

/*
* A getter for the metric.
*/
string Settings::getMetric() {
    return metric;
}

/*
* A setter for the k value.
*/
void Settings::setK(int _k) {
    k = _k;
}

/*
* A setter for the metric.
*/   
void Settings::setMetric(string _metric) {
    metric = _metric;
}

/*
* A setter for the input.
*/   
void Settings::setInput(string _input) {
    userInput = _input;
}

/*
* A getter for the input.
*/
string Settings::getInput() {
    return userInput;
}

/*
* Func name: execute
* Input: none
* Output: none
* Function operation: if the user input is just enter, prints the k and metric values.
* else, if the input is a number and a legal metric, updates the values of k and the
* metric, if not - prints messages describing what part of the string was illegal.
*/
void Settings::execute() {
    if (userInput == "\n") {
        string kMet = to_string(getK());
        kMet.append(getMetric());
    } else {
        int firstSpace = userInput.find(" ");
        char* k;
        char* metric;
        strncpy(k, userInput.c_str(), firstSpace);
        strcpy(metric, &userInput[firstSpace + 1]);
        bool isKLegal = false;
        if (!isNumber(k)) {
            cout << "invalid value for K\n";
        } else {
            isKLegal = true;
        }
        if ((metric != "AUC") && (metric != "MAN") && (metric != "CHB") && (metric != "CAN") &&
            (metric != "MIN")) {
            cout << "invalid value for metric\n";
        } else {
            if (isKLegal) {
                setK(stoi(k));
                setMetric(metric);
            }
        }
    }
}