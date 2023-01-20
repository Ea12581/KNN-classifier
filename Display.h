#ifndef DISPLAY_H
#define DISPLAY_H
#include <string>
#include "Command.h"
#include "VectorCalDis.h"


using namespace std;
class Display : protected Command {
private:
    vector<string> clsifics;

public:
    Display(vector<string>);
    vector<string> getClsifics();
    void setClsifics(vector<string>);
    virtual void execute();
};


#endif