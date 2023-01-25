#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <cctype>
#include <string>
#include "VectorCalDis.h"
#include "KnnDB.h"
#include <string.h>
#include "CheckInput.h"

using namespace std;


/*
    * Func name: main
    * Input: int argc (num of terminal inputs), char *argv[] (the path to the database and port number)
    * Output: int
    * Function operation: Expects path to database file (csv file) and port number for the server side
    * to create database of Knn vectors and to build socket for listening for clients who want to connect
    */
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
        int bindFlag = server.bindServer();
        //if the bind has failed
        if(bindFlag < 0)
            ::exit(1);
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