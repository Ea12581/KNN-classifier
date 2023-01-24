#include <iostream>
#include "Classify.h"
#include "KnnDB.h"
#define DEFAULT_K 5
#define DEFAULT_METRIC "EUC"


/*
* Func name: getK
* Input: None
* Output: int k (a number)
* Function operation: A getter for number to calc the knn with
*/ 
int Classify::getK() {
    return getSd()->getK();
}

/*
* Func name: getMetirc
* Input: None
* Output: string (the name of the metric used for the classification)
* Function operation: a getter for the metric
*/ 
string Classify::getMetirc() {
    return getSd()->getMetric();
}

/*
* Func name: setK
* Input: int _k (a number)
* Output: None
* Function operation: A setter for number to calc the knn with
*/ 
void Classify::setK(int _k) {
    getSd()->setK(_k);
}

/*
* Func name: setMetric
* Input: string _metric(the name of the metric used for the classification)
* Output: None
* Function operation: A getter for metric
*/     
void Classify::setMetric(string _metric) {
    getSd()->setMetric(_metric);
}

/*
* Func name: execute
* Input: none
* Output: none
* Function operation: if the path is "\0", meaning no path was provided,
* prints a message to upload data. else, classifies the pairs according
* to the k, the metric and the data in the file provided.
*/
void Classify::execute() {
    string output;
    if (getSd()->getUnClassified() == nullptr) {
        output = "please upload data";
    } else {
        KnnDB temp;
        vector<KnnVec> *tempVec = new vector<KnnVec>;
        *tempVec = temp.createDBFromValCalDis(*(getSd()->getUnClassified())); 
        getSd()->setClassified(tempVec);
        output = "classifying data complete";
    }
    getDio()->write(output);
}