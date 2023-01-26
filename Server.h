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
public:
    Server(int,int);
    ~Server();
    int getPort() const;
    void setPort(int port);
    int getSockNum() const;
    void setSockNum(int sockNum);
    int bindServer();
    int closeServer();
    int listenToNewConnections();
};

struct SocketInfo {
    int* clientSock;
    Server* &server;
    SocketInfo(int* client, Server* s) : clientSock(client), server(s) {}
};

#endif 
