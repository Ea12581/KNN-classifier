#ifndef CLASSI_H
#define CLASSI_H
#include <string>
#include "Command.h"
#include "VectorCalDis.h"


using namespace std;
class Classify : protected Command {
private:
    string path;
    vector<pair <VectorCalDis, string>> vectors;
    int k;
    string metric;

public:
    Classify(string _desc, DefaultIO _dio, string path, vector <VectorCalDis>* _vectors, int k, string metric);
    int getK();
    string getMetirc();
    void setK(int);
    void setMetric(string);
    string getPath();
    void setPath(string);
    vector<pair <VectorCalDis, string>>* getVectors();
    void setVectors(vector <VectorCalDis>*);
    virtual void execute();
};


#endif