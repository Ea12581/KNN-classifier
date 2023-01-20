#include <iostream>
#include "Classify.h"
#include "KnnDB.h"


/*
* A consturctor with decription, path, pointer to a vector of special vectors, an int and a metric to for the classification
*/
Classify::Classify(string _desc, DefaultIO _dio, string _path, vector <VectorCalDis>* _vectors, int _k, string _metric) {
        setDesc(_desc);
        setDio(_dio);
        setPath(_path);
        setVectors(_vectors);
        setK(_k);
        setMetric(_metric);
}

/*
* Func name: getK
* Input: None
* Output: int k (a number)
* Function operation: A getter for number to calc the knn with
*/ 
int Classify::getK() {
    return k;
}

/*
* Func name: getMetirc
* Input: None
* Output: string (the name of the metric used for the classification)
* Function operation: a getter for the metric
*/ 
string Classify::getMetirc() {
    return metric;
}

/*
* Func name: setK
* Input: int _k (a number)
* Output: None
* Function operation: A setter for number to calc the knn with
*/ 
void Classify::setK(int _k) {
    k = _k;
}

/*
* Func name: setMetric
* Input: string _metric(the name of the metric used for the classification)
* Output: None
* Function operation: A getter for metric
*/     
void Classify::setMetric(string _metric) {
    metric = _metric;
}

/*
* Func name: getPath
* Input: None
* Output: string (the path of the file with classified vectors)
* Function operation: A getter for the path
*/ 
string Classify::getPath() {
    return path;
}

/*
* Func name: setPath
* Input: string _path (the path of the file with classified vectors)
* Output: None
* Function operation: A setter for the path
*/
void Classify::setPath(string _path) {
    path = _path;
}

/*
* Func name: getVectors
* Input: None
* Output: vector<pair <VectorCalDis, string>>* (a pointer to the vector
* of pairs holding vectors and their classifications).
* Function operation: A getter for the vector of pairs.
*/
vector<pair <VectorCalDis, string>>* Classify::getVectors() {
    return &vectors;
}

/*
* Func name: setVectors
* Input: vector _vectors <VectorCalDis>* (a pointer to a vector of vectors)
* Output: none
* Function operation: sets vectors without a classification.
*/
void Classify::setVectors(vector <VectorCalDis>* _vectors) {
    for (int i = 0; i < _vectors->size(); i++) {
        pair <VectorCalDis, string> vector;
        vector.first = _vectors->at(i);
        vector.second = "";
        vectors.push_back(vector);
    }

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
    if (path == "\0") {
        cout << "please upload data\n";
    } else {
        KnnDB data = KnnDB(path, k, metric);
        data.classifyPairs(vectors);
        cout << "classifying data complete\n";
    }
}