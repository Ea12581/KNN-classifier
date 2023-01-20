#include <iostream>
#include "Classify.h"
#include "KnnDB.h"

Classify::Classify(string _desc, DefaultIO _dio, string _path, vector <VectorCalDis>* _vectors, int _k, string _metric) {
        setDesc(_desc);
        setDio(_dio);
        setPath(_path);
        setVectors(_vectors);
        setK(_k);
        setMetric(_metric);
}

int Classify::getK() {
    return k;
}

string Classify::getMetirc() {
    return metric;
}

void Classify::setK(int _k) {
    k = _k;
}
    
void Classify::setMetric(string _metric) {
    metric = _metric;
}

string Classify::getPath() {
    return path;
}

void Classify::setPath(string _path) {
    path = _path;
}

vector<pair <VectorCalDis, string>>* Classify::getVectors() {
    return &vectors;
}

void Classify::setVectors(vector <VectorCalDis>* _vectors) {
    for (int i = 0; i < _vectors->size(); i++) {
        pair <VectorCalDis, string> vector;
        vector.first = _vectors->at(i);
        vector.second = "";
        vectors.push_back(vector);
    }
}

void Classify::execute() {
    if (path == "\0") {
        cout << "data upload please.\n";
    } else {
        KnnDB data = KnnDB(path, k, metric);
        data.classifyPairs(vectors);
    }
}