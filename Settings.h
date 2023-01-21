#ifndef SETINGS_H
#define SETINGS_H
#include <string>
#include "Command.h"


using namespace std;
class Settings : protected Command {
private:
    int k;
    string metric;
    string userInput;

public:
    Settings(string _desc, DefaultIO _dio, string userInput);
    int getK();
    string getMetric();
    string getInput();
    void setK(int);
    void setMetric(string);
    void setInput(string);
    virtual void execute();
};

#endif