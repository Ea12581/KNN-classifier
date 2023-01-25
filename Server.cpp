//
// Created by oem on 12/29/22.
//
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <vector>
#include <string>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "VectorCalDis.h"
#include "KnnDB.h"
#include "CheckInput.h"
#include "Server.h"
#include "Settings.h"
#include "UploadC.h"
#include "Display.h"
#include "Download.h"
#include "Command.h"
#include "Classify.h"
#include "SocketIO.h"
#define NUM_OF_CMDS 5



/**
 *
 * constructor
 */
Server::Server(int port, int sock) {
    m_port = port;
    m_sockNum = sock;
    IO = SocketIO(port, sock);   
    setCmds();
}

/**
 * distructor
 */
Server::~Server() {
    int flag = closeServer();
    //if the closing or the shutdown went wrong
    if(flag < 0)
        exit(1);
}

void Server::setCmds() {
        ShareData *sd = new ShareData();
        UploadC upload = UploadC("upload an unclassified csv data file", &IO, sd);
        Settings settings = Settings("algorithm settings", &IO, sd);
        Classify classify = Classify("classify data", &IO, sd);
        Display display = Display("display results", &IO, sd);
        Download download = Download("download results", &IO, sd);
        Command* temp[NUM_OF_CMDS] = {&upload, &settings, &classify, &display, &download};
        cmd = temp;
}

/**
 * get the socket id of the server
 * @return integer that represents the id of the server socket
 */
int Server::getSockNum() const {
    return m_sockNum;
}

/**
 *
 * @param sockNum
 * set the socket of the server with identifier of a new socket
 */
void Server::setSockNum(int sockNum) {
    Server::m_sockNum = sockNum;
}

/**
 * bind the server to socket, return -1 if it's failed, 1 if successes
 * @return
 */
int Server::bindServer() {
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(m_port);
    if (bind(m_sockNum, (struct sockaddr *) &sin, sizeof(sin)) < 0)
    {
        perror("error binding socket to m_port");
        return -1;
    }
    return 1;
}

/**
 * get the port of the server
 * @return port number
 */
int Server::getPort() const {
    return m_port;
}

/**
 * set the port of the server
 * @param port number
 */
void Server::setPort(int port) {
    Server::m_port = port;
}


void* start(void* args) {
    struct socketInfo* info =  (socketInfo*)(args);
    int sock = *(info->clientSock);
    Server* server = info->sever;
    server->setMClient(sock);
        int option = 0;
        bool isEight = false;
        string input;
        while (!isEight) {
            switch (option) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    server->getCmds()[option-1]->execute();
                    break;
                case 8:
                    isEight = true;
                    break;
                default:
                    break;
            }
            if (!isEight) {
                server->getSIO().write(server->sendMenu());
                input = server->getSIO().read();
                if (isNumber(input.c_str())) {
                    option = stoi(input);
                } else {
                    option = 0;
                }
            }
        }
    close(sock);
    pthread_exit(NULL);
}

/**
 * wait and listen to new clients that want to connect the server, return -1 if don't succeed in listening
 * the client need to send the proper input that contains:
 * x1 x2 x3 ... xn (values of unclassified vector) MATRIC(definition of the metric he want to base on it the classified
 * of the vector) k (a positive number, number of the nearest neighbors the clients want to base on them the
 * classification of the new vector. If one of the inputs above is not proper, the client would received an error
 * massage
 * @return -1 if the listening has failed
 */
int Server::listenToNewConnections() {
    // Listen for incoming connections
    if (listen(m_sockNum, 5) < 0)
    {
        perror("error listening for connections");
        return -1;
    }
    while (true)
    {
        // Accept a new connection
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int clientSock = accept(m_sockNum, (struct sockaddr*)&client_addr, &client_addr_len);
        if (clientSock < 0){
            perror("error accepting connection");
            continue;
        }
        getSIO().setMClient(clientSock);
        pthread_t thread;
        struct socketInfo* args;
        args->clientSock = &clientSock;
        args->sever = this;
        if(pthread_create(&thread, NULL, start, args) != 0)
        {
            perror("Error creating thread");
            continue;
        }
    }
    return 0;
}


int Server::getMClient() const {
    return m_client;
}

void Server::setMClient(int mClient) {
    m_client = mClient;
}

/**
 * safe closing the server. return 1 if succeed, -1 if not
 * @return 1 for success, -1 else
 */
int Server :: closeServer() {
    // stop the server socket from sending or receiving
    int flag = shutdown(m_sockNum, SHUT_RDWR);
    if(flag < 0){
        perror("error shutdown socket");
        return flag;
    }

    // close the socket
    flag = close(m_sockNum);
    if(flag < 0){
        perror("error closing socket");
        return flag;
    }
    return 0;
}

string Server :: sendMenu() {
    string menu = "Welcome to the KNN Classifier Server. Please choose an option:\n";
    int cmd_size = sizeof(cmd)/sizeof(cmd[0]);
    for (int i = 0; i < cmd_size; i++) {
        menu.append(std::to_string(i+1));
        menu.append(" ");
        menu.append(cmd[i][0].getDesc());
        menu.append("\n");
    }
    menu.append("8. exit");
    return menu;
}

int main(int argc, char *argv[]){
    if (argc != 2) {
        printf("Wrong number of arguments!\n");
        exit(1);
    }
    //check if the m_port is number and legal m_port
    if(isNumber(argv[1]) && isLegalPort(argv[1])){

        //take th m_port
        int decimalBase = 10;
        const long port_no = std::strtol(argv[1], nullptr,decimalBase);
        Server server = Server(0, 0);
        server.setPort(port_no);
        // Create a socket
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0)
        {
            perror("error creating socket");
            return 1;
        }
        //set the sock number
        server.setSockNum(sock);
        
        // Bind the socket to the specified m_port
        server.getSIO().setMServer(server.getSockNum());
        int bindFlag = server.bindServer();
        //if the bind has failed
        if(bindFlag < 0)
            exit(1);
        //listen to connections
        int listenFlag = server.listenToNewConnections();
        if(listenFlag < 0) {
            exit(1);
        }

    }else{
        cout << "first input is not a legal m_port number!"<< endl;
    }
    return 0;
}

    SocketIO Server::getSIO() {
        return IO;
    }
    Command** Server::getCmds() {
        return cmd;
    }