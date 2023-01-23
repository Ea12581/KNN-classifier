#ifndef DL_H
#define DL_H
#include <string>
#include <vector>
#include "Command.h"


using namespace std;
class Download : public Command {
public:
    Download(string _desc, DefaultIO _dio, ShareData* _sd) : Command(std::move(_desc), _dio, _sd){};  
    virtual void execute();
};


#endif