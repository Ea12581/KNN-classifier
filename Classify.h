#ifndef CLASSI_H
#define CLASSI_H
#include <string>
#include "Command.h"
#include "VectorCalDis.h"


using namespace std;
class Classify : protected Command {
public:
    Classify(string _desc, DefaultIO _dio, ShareData* _sd) : Command(std::move(_desc), _dio, _sd){};    
    int getK();
    string getMetirc();
    void setK(int);
    void setMetric(string);
    virtual void execute();
};


#endif