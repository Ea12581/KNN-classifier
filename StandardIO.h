#ifndef STDIO_H
#define STDIO_H
#include <string>
#include "DefaultIO.h"


using namespace std;
class StandardIO : public DefaultIO {
    string read() override;
    void write(string output) override;

};

#endif
