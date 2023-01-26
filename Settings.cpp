#include <iostream>
#include "Settings.h"
#include "CheckInput.h"



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
    if (getSd()->isKnnDBExists()) {
        getSd()->setK(_k);
        k = _k;
    } else {
       k = _k;
    }
}

/*
* A setter for the metric.
*/   
void Settings::setMetric(string _metric) {
    if (getSd()->isKnnDBExists()) {
        getSd()->setMetric(_metric);
        metric = _metric;
    } else {
        metric = _metric;
    }
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
    string output;
    output = "The current KNN parameters are: K = ";
    output.append(to_string(getK()));
    output.append(", distance metric = ");
    output.append(getMetric());
    getDio()->write(output);
    string input = getDio()->read();
    if (input == "\n") {
        return;
    } else {
        int firstSpace = input.find(" ");
        if (firstSpace == -1) {
            output = "invalid value for K\n";
            output.append("invalid value for metric");
            getDio()->write(output);
            //get finish massage from client
            getDio()->read();
            return;
        } else {
           char* k;
            char* metric;
            metric = &input[firstSpace + 1];
            input[firstSpace] = '\0';
            k = &input[0];
            bool isKLegal = false;
            if (!isNumber(k)) {
                output = "invalid value for K";
                getDio()->write(output);
                //get finish massage from client
                getDio()->read();
                return;
            } else {
                isKLegal = true;
            }
            if ((strcmp(metric, "AUC")) && (strcmp(metric, "MAN")) && (strcmp(metric, "CHB")) && (strcmp(metric, "CAN")) &&
                (strcmp(metric, "MIN"))) {
                output = "invalid value for metric";
                getDio()->write(output);
                //get finish massage from client
                getDio()->read();
                return;
            } else {
                if (isKLegal) {
                    setK(stoi(k));
                    setMetric(metric);
                    output = "The current KNN parameters are: K = ";
                    output.append(to_string(getK()));
                    output.append(", distance metric = ");
                    output.append(getMetric());
                    getDio()->write(output);
                    //get finish massage from client
                    getDio()->read();
                }
            }
        }
    }
}
