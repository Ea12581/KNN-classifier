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
#include "VectorCalDis.h"
#include "KnnDB.h"
#include "KnnServer.h"



/**
 *
 * @param mKnnDbp
 * constructor with pointer to DB
 */
KnnServer::KnnServer(KnnDB *mKnnDbp) {
    m_KnnDBP = mKnnDbp;
    m_port = 0;
    m_sockNum = 0;
}

/**
 * distructor that clean the data base
 */
KnnServer::~KnnServer() {
    delete m_KnnDBP;
    int flag = closeServer();
    //if the closing or the shutdown went wrong
    if(flag < 0)
        exit(1);
}

/**
 * get the data base vector
 * @return m_KnnDBP, the data base of the classified vectors
 */
KnnDB *KnnServer::getMKnnDbp() const {
    return m_KnnDBP;
}

/**
 *
 * @param mKnnDbp
 * set the vector with the DB of the Knn vectors
 */
void KnnServer::setMKnnDbp(KnnDB *mKnnDbp) {
    delete m_KnnDBP;
    m_KnnDBP = mKnnDbp;
}

/**
 * get the socket id of the server
 * @return integer that represents the id of the server socket
 */
int KnnServer::getSockNum() const {
    return m_sockNum;
}

/**
 *
 * @param sockNum
 * set the socket of the server with identifier of a new socket
 */
void KnnServer::setSockNum(int sockNum) {
    KnnServer::m_sockNum = sockNum;
}

/**
 * bind the server to socket, return -1 if it's failed, 1 if successes
 * @return
 */
int KnnServer::bindServer() {
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
int KnnServer::getPort() const {
    return m_port;
}

/**
 * set the port of the servet
 * @param port number
 */
void KnnServer::setPort(int port) {
    KnnServer::m_port = port;
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
int KnnServer::listenToNewConnections() {
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
        m_client = clientSock;
        std::string message = "0";
        while (message != "-1"){
            string sendBack;
            // Read data from the client
            message = readMessage();
            //check if the client want to close
            if(message == "-1"){
                //close the client socket
                close(m_client);
                //initialized the client socket
                setMClient(0);
                //get out to keep listening for new connection
                break;
            }
            vector<string> argsForVec = splitMessage(message);

            if(argsForVec.size() != 3){
                sendBack = "Wrong number of arguments from client!\n";
                send(clientSock, sendBack.c_str(), sendBack.length(), 0);
                continue;

            }
            int k;
            //check if the last argument is a number
            try
            {
                k = std::stoi(argsForVec.at(2));
            }
            catch (const std::invalid_argument &e)
            {
                sendBack =  "The last argument does not represent a number.\n";
                send(clientSock, sendBack.c_str(), sendBack.length(), 0);
                continue;
            }

            //check if the last argument is a positive number
            if(k < 0){
                sendBack =  "The last argument does not represent a positive number!.\n";
                send(clientSock, sendBack.c_str(), sendBack.length(), 0);
                continue;
            }

            string metric = argsForVec.at(1);
            //check if the middle string is represented metric
            if ((metric != "AUC") && (metric != "MAN") && (metric != "CHB") && (metric != "CAN") &&
                (metric != "MIN")) {
                sendBack = "2rd input is an unknown distance metric!\n";
                send(clientSock, sendBack.c_str(), sendBack.length(), 0);
                continue;
            }

            // K should not be larger than the amount of vectors in the DB
            if (m_KnnDBP->getDB().size() < k) {
                k = m_KnnDBP->getDB().size();
            }

            //create the vector from the coordinates
            VectorCalDis inputVec;
            string strVec = argsForVec.at(0);
            string classification;
            inputVec = inputVec.vectorFromString(strVec);
            if (inputVec.size() == 0) {
                sendBack =  "illegal vector input\n";
                send(clientSock, sendBack.c_str(), sendBack.length(), 0);
                continue;
            }
            //set the metric and the k
            m_KnnDBP->setK(k);
            m_KnnDBP->setMetric(metric);
            vector<pair<string, double>> knnPairs = m_KnnDBP->findKnn(inputVec);
            classification = m_KnnDBP->mostPrevalentCls(knnPairs);
            //send the classification to the client
            send(clientSock, classification.c_str(), classification.length(), 0);
        }
        continue;
    }
}

/*
* Function Name: splitMessage
* Input: massage, which was received by the client
* Output: massage, str with the whole massage
* Function operation: get massage from client and return it as a vector with 3 arguments, coordinates for the vector
 * the metric type and number of k neighbors to classify it.
*/
vector<string> KnnServer::splitMessage(string massage) {
    int massageSize = massage.length();
    vector<string> argsForVec;
    /* go in loop through the string and find and separate the free args
     * */
    string numbers = "-.0123456789 ";
    int i = 0;
    for (; i < massageSize; i++) {
        //if we found the first char that is not part of the coordinates
        if (numbers.find(massage[i]) == std::string::npos) {
            //get the coordinates without the space which separate them from the metric
            argsForVec.push_back(massage.substr(0, i - 1));
            break;
        }
    }
    int middle = i;
    for (; i < massageSize; i++){
        //search the first char that isn't part of the metric type
        if(numbers.find(massage[i]) != std::string::npos){
            //get the metric
            argsForVec.push_back(massage.substr(middle,i - middle));
            //condition in case there is an invalid k without k
            if(i+1 <= massageSize){
                //get the k
                argsForVec.push_back(massage.substr(i+1,massageSize - (i+1)));
            }
            break;
        }
    }


    return argsForVec;
}

/*
* Function Name: readMessage
* Input: int m_client, id of the client socket
* Output: massage, str with the whole massage
* Function operation: get massage from client and return it as a string.
*/
std::string KnnServer::readMessage() {
    std::string message;
    char buffer[4096];
    int expected_data_len = sizeof(buffer);

    // Read data from the socket in chunks until the entire message has been received
    while (true)
    {
        int read_bytes = recv(m_client, buffer, expected_data_len, 0);
        if (read_bytes == 0)
        {
            // Connection closed by the client
            break;
        }
        else if (read_bytes < 0)
        {
            // Error
            perror("error reading from socket");
            break;
        }

        // Append the data to the message
        message.append(buffer, read_bytes);

        // Check if the entire message has been received
        if (read_bytes < expected_data_len)
        {
            break;
        }
    }

    return message;
}

int KnnServer::getMClient() const {
    return m_client;
}

void KnnServer::setMClient(int mClient) {
    m_client = mClient;
}

/**
 * safe closing the server. return 1 if succeed, -1 if not
 * @return 1 for success, -1 else
 */
int KnnServer :: closeServer(){
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