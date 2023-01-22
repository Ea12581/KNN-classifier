#ifndef SETINGS_H
#define SETINGS_H
#include <string>
#include "Command.h"


using namespace std;
class Settings : protected Command {
public:
    Settings(string _desc, DefaultIO _dio, ShareData* _sd) : Command(std::move(_desc), _dio, _sd){};
    int getK();
    string getMetric();
    string getInput();
    void setK(int);
    void setMetric(string);
    void setInput(string);
    virtual void execute();
};

#endif