#ifndef STDIO_H
#define STDIO_H
#include <string>
#include "DefaultIO.h"


using namespace std;
class SocketIO : public DefaultIO {
private:
    int m_client;
public:
    int getMServer() const;

    int getMClient() const;

    SocketIO(int client);

    string read();
    void write(string output);

};

#endif