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
    SocketIO* IO;
    Command** cmd;
public:
    Server(int,int);
    ~Server();
    int getMClient() const;
    void setMClient(int mClient);
    int getPort() const;
    void setPort(int port);
    int getSockNum() const;
    SocketIO* getSIO();
    Command** getCmds();
    void setCmds();
    void setSockNum(int sockNum);
    int bindServer();
    int closeServer();
    int listenToNewConnections();
    std::string sendMenu();
    void* start();
    static void* start_helper(void* arg);
};

struct SocketInfo {
    int* clientSock;
    Server* &server;
    SocketInfo(int* client, Server* s) : clientSock(client), server(s) {}
};

#endif 
