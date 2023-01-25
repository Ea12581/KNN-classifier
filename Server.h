//
// Created by oem on 12/31/22.
//

#ifndef SERVER_H
#define SERVER_H
#include "SocketIO.h"
#include "Command.h"
/*
 * header for the server class
 */

class Server{
private:
    long m_port;
    int m_sockNum;
    int m_client;
    int getMClient() const;
    void setMClient(int mClient);
    SocketIO IO;
    Command** cmd;
public:
    Server();
    int getPort() const;
    void setPort(int port);
    int getSockNum() const;
    SocketIO getSIO();
    Command** getCmds();
    void setCmds();
    void setSockNum(int sockNum);
    int bindServer();
    int closeServer();
    int listenToNewConnections();
    void* start(void*);
    std::string sendMenu();

};

#endif 
