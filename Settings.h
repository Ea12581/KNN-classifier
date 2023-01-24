#ifndef SETINGS_H
#define SETINGS_H
#include <string>
#include "Command.h"
#define DEFAULT_K 5
#define DEFAULT_METRIC "AUC"


using namespace std;
class Settings : public Command {
private:
    int k;
    string metric;
public:
    Settings(string _desc, DefaultIO _dio, ShareData* _sd) : Command(std::move(_desc), _dio, _sd){
        setK(DEFAULT_K);
        setMetric(DEFAULT_METRIC);
    };
    int getK();
    string getMetric();
    string getInput();
    void setK(int);
    void setMetric(string);
    void setInput(string);
    virtual void execute();
};

#endif