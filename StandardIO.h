#ifndef STDIO_H
#define STDIO_H
#include <string>
#include "DefaultIO.h"


using namespace std;
class StandardIO : public DefaultIO {
public:
    string read();
    void write(string);

};

#endif