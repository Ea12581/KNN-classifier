#ifndef STDIO_H
#define STDIO_H
#include <string>
#include "DefaultIO.h"


using namespace std;
class SocketIO : public DefaultIO {
private:
    int m_client;
public:
    int getMClient() const;
    void setMClient(int);
    SocketIO();
    SocketIO(int client);
};

#endif