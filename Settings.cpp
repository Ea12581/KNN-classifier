#include <iostream>
#include "Settings.h"
#include "CheckInput.h"
#define DEFAULT_K 5
#define DEFAULT_METRIC "EUC"




/*
* A getter for the k value.
*/
int Settings::getK() {
    return getSd()->getK();
}

/*
* A getter for the metric.
*/
string Settings::getMetric() {
    return getSd()->getMetric();
}

/*
* A setter for the k value.
*/
void Settings::setK(int _k) {
    getSd()->setK(_k);
}

/*
* A setter for the metric.
*/   
void Settings::setMetric(string _metric) {
    getSd()->setMetric(_metric);
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
    string input = getDio().read();
    string output;
    if (input == "\n") {
        output = "The current KNN parameters are: K = ";
        output.append(to_string(getK()));
        output.append(", distance metric = ");
        output.append(getMetric());
        output.append("\n");
    } else {
        int firstSpace = input.find(" ");
        char* k;
        char* metric;
        strncpy(k, input.c_str(), firstSpace);
        strcpy(metric, &input[firstSpace + 1]);
        bool isKLegal = false;
        if (!isNumber(k)) {
            output = "invalid value for K\n";
        } else {
            isKLegal = true;
        }
        if ((metric != "AUC") && (metric != "MAN") && (metric != "CHB") && (metric != "CAN") &&
            (metric != "MIN")) {
            output = "invalid value for metric\n";
        } else {
            if (isKLegal) {
                setK(stoi(k));
                setMetric(metric);
            }
        }
    }
    getDio().write(output);
}