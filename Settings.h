#ifndef SETINGS_H
#define SETINGS_H
#include <string>
#include "Command.h"


using namespace std;
class Settings : protected Command {
private:
    int k;
    string metric;

public:
    Settings(string _desc, DefaultIO _dio);
    int getK();
    string getMetirc();
    void setK(int);
    void setMetric(string);
    virtual void execute();
};


#endif