#include <iostream>
#include "Settings.h"
#include "CheckInput.h"
#define DEFAULT_K 5
#define DEFAULT_METRIC "EUC"

Settings::Settings(string _desc, DefaultIO _dio) {
    setDesc(_desc);
    setDio(_dio);
    setK(DEFAULT_K);
    setMetric(DEFAULT_METRIC);

}

int Settings::getK() {
    return k;
}

string Settings::getmetirc() {
    return metric;
}

void Settings::setK(int _k) {
    k = _k;
}
    
void Settings::setMetric(string _metric) {
    metric = _metric;
}

void Settings::execute() {
    string input;
    cin >> input;
    if (input == "\n") {
        string kMet = to_string(getK());
        kMet.append(getmetirc());
    } else {
        int firstSpace = input.find(" ");
        char* k;
        char* metric;
        strncpy(k, input.c_str(), firstSpace);
        strcpy(metric, &input[firstSpace + 1]);
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