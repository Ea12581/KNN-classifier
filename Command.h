#ifndef CMD_H
#define CMD_H
#include <string>
#include "DefaultIO.h"

using namespace std;
class Command {
private:
    string desc;
    DefaultIO dio;

public:

    Command(string _desc, DefaultIO _dio);
    void setDesc(string _desc);
    void setDio(DefaultIO _dio);
    string getDesc();
    DefaultIO getDio();
    void execute(); 
};

#endif;