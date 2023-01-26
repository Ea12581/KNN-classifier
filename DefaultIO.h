#ifndef DIO_H
#define DIO_H
#include <string>

using namespace std;
class DefaultIO {
public:

    virtual string read();

    virtual void write(string);

};

#endif
