#ifndef DISPLAY_H
#define DISPLAY_H
#include <string>
#include "Command.h"
#include "VectorCalDis.h"


using namespace std;
class Display : public Command {
public:
    Display(string _desc, DefaultIO* _dio, ShareData* _sd) : Command(std::move(_desc), _dio, _sd){};
    virtual void execute();
};


#endif