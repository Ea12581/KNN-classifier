//
// Created by oem on 1/22/23.
//
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include "CheckInput.h"
#include "VectorCalDis.h"
#include "Client.h"
#include <regex.h>
#include <cstring>
#include <thread>
#define BUFFER 4096
using namespace std;

/**
 * getter for the m_socket number of the client
 * @return int number
 */
int Client::getSock() const {
    return m_socket;
}

/**
 * setter for the number of the m_socket of the client
 * @param sock ,number of the m_socket of the client
 */
void Client::setSock(int sock) {
    Client::m_socket = sock;
}

/**
 * constructor to establish m_socket and binding it to the server by given ip and port
 * @param ip of the server
 * @param port of the server
 */
Client::Client(char* ip, string port) {
    const int port_no = stoi(port);
    const char* ip_address = ip;

    // Create a m_socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("error creating m_socket");
        ::exit(1);
    }

    // Connect to the server
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);
    if (connect(sock, (struct sockaddr*)&sin, sizeof(sin)) < 0)
    {
        perror("error connecting to server");
        ::exit(1);
    }
    //set the m_socket number
    setSock(sock);
    keepAlive = true;

}

/**
 * start conversation with the server and receive messages
 */
void Client::start() {
    char decision;
    string input;
    // Send a message to the server by the choose of the user
    while (keepAlive) {
        //get the menu
        cout << receive();
        cin >> decision;
        input = "";
        input += decision;
        //send the decsition to the server
        sendToSer(input);
        //clear the buffer
        getline(std::cin, input);
        input = "";
        switch(decision){
            case '1':
                uploadDB();
                break;
            case '2':
                chooseMetricK();
                break;
            case '3':
                //get confirm
                cout << receive();
                //send finish message
                sendToSer("finish");
                break;
            case '4':
                //get data
                cout << receive();
                //send finish message
                sendToSer("finish");
                break;
            case '5':
                download();
                //get input from user
                input = "";
                break;
            case '8':
                keepAlive = false;
                break;
            default:
                break;
        }
    }
    close(m_socket);

}

/**
 * receive massage from the server
 * @return string massage from the server
 */
string Client::receive() {
    // Wait for a response from the server
    char buffer[BUFFER];
    int expected_data_len = BUFFER;
    int min_data_len = 2;
    int read_bytes;
    string massage;
    //read while we can read from the socket
    while((read_bytes = recv(m_socket, buffer, expected_data_len, 0)) > 0){
    if (read_bytes == 0) {
        // Connection closed by the server
        perror("Connection closed by the server");
        close(m_socket);
        exit(1);
    } else if (read_bytes < 0) {
        // Error
        perror("error reading from m_socket");
        close(m_socket);
        exit(1);
    }
    // Append the data to the message
    massage.append(buffer, read_bytes);
        memset(buffer,0,BUFFER);
    // Check if the buffer is not full, if so, go out
    if (read_bytes < expected_data_len) {
        break;
    }
}
    return massage;
}

/**
 * send massage to the server
 */
void Client::sendToSer() {
    string userInput;
    getline(cin, userInput);
    //if the user pressed enter, send new line
    if(userInput.length() == 0){
        userInput += "\n";
    }
    const char* pInput = userInput.c_str();
    // Removes leading spaces
    userInput.erase(0, userInput.find_first_not_of(' '));
      int data_len = strlen(pInput);
    int sent_bytes = send(m_socket, pInput, data_len, 0);
    if (sent_bytes < 0) {
        // Error
        perror("error writing to m_socket");
        close(m_socket);
        exit(1);
    }
    //check if the user inserted 8
    if (!strcmp(pInput, "8")) {
        keepAlive = false;
    }

}

/**
 * send massage to the server
 * @param userInput string input from the user
 */
void Client::sendToSer(string userInput){
    const char* pInput = userInput.c_str();
    // Removes leading spaces
    userInput.erase(0, userInput.find_first_not_of(' '));
    int data_len = strlen(pInput);
    int sent_bytes = send(m_socket, pInput, data_len, 0);
    if (sent_bytes < 0) {
        // Error
        perror("error writing to m_socket");
        close(m_socket);
        exit(1);
    }


}

/**
 * upload new unclassified vectors from a cvs file otherwise
 * @return: true if the upload succeeded, false
 */
bool Client::upload(string path) {
    //stream pointer to the file
    ifstream fin;
    // Open an existing file
    fin.open(path, ios::in);
    //check if the openning has succeeded
    if(fin.is_open()) {
        // Read the Data from the file
        //line by line
        string line;
        string vectors;
        // store it in a string variable 'line' and read it line by line
        while (getline(fin, line)) {
            //add /n
            line += '\n';
            vectors += line;
        }
            const char* pInput = vectors.c_str();
            int data_len = strlen(pInput);
            int sent_bytes = send(m_socket, pInput, data_len, 0);
            if (sent_bytes < 0) {
                // Error
                perror("error writing to m_socket");
                close(m_socket);
                exit(1);
            }
        fin.close();
        }

        //if we couldn't open the file
     else{
        sendToSer("error");
        return false;
    }
    return true;

}

/**
 * download the results of classifying the vectors which we have loaded earlier
 */
void Client::download() {
    string path;
    getline(std::cin, path);
    string vectors = receive();
    //thread t(&Client::separetedDownload, this,path,vectors);
    separetedDownload(path,vectors);
    //t.detach();
    sendToSer("finish");
}

/**
 * up load classified and unclassified vectors from given files directories
 */
void Client::uploadDB(){
    string input;
    //get instructions from server
    cout << receive();
    //get path to classified vectors from user
    getline(cin, input);
    if(upload(input)){
        //get confirm
        cout << receive();
        //get path to unclassified vectors
        getline(cin, input);
        upload(input);
        //get confirm
        cout << receive();
        sendToSer("finish");
    }
    //return to main
}

/**
 * manage the choise of the user about the current k and metric
 */
void Client::chooseMetricK() {
    //get the current metric and k
    cout << receive();
    string input;
    //choose to change or not
    getline(cin, input);
    //decide not
    if(input == ""){
        sendToSer("\n");
        return;
    }
    sendToSer(input);
    //get the current metric and k
    cout << receive();
    //send finish
    sendToSer("finish");

}


/**
 * download the file in another thread
 * @param path to the file we want to write in
 */
void Client::separetedDownload(string path,string vectors){
    //stream pointer to the file
    ofstream fin;
    // Open an existing file
    fin.open(path, ios::out);
    //check if the openning has succeeded
    if(fin.is_open()) {
        string line;
        stringstream s(vectors);
        //line by line
        // store it in a string variable 'line' and read it line by line
        while (getline(s,line,'\n')) {
            //add /n
            line += '\n';
            fin << line;
        }

        fin.close();
    }
        //if we couldn't open the file
    else{
        cout << "invalid path" << endl;
        //throw the output from server
        receive();
    }

}

/*
* Func name: main
* Input: int argc (num of terminal inputs), char *argv[] (the file name and inputs)
* Output: int
* Function operation: Expects an IP and a port to connect to, creates a m_socket
* for the connection, sends as a string vectors, a function to use and an int
* so the server could classify the vector by it's knn. gets the classification
* from the server and prints it, stops when it gets -1, of if the inputs are illegal
* (or if an error occured).
*/

int main(int argc, char *argv[]) {
    // should have 3 inputs, the out file, the ip and the port.
    if (argc != 3) {
        printf("Wrong number of arguments!\n");
        exit(1);
    }
    // check if the port is number and legal port
    if (!(isNumber(argv[2]) && isLegalPort(stoi(argv[2])))) {
        cout << "2rd input is not a legal port number!"<< endl;
        exit(1);
    }
    // checks if the ip is legal
    if (!isLegalIp(argv[1])) {
        cout << "first input is not a legal ip!!"<< endl;
        exit(1);
    }
    Client c = Client(argv[1], argv[2]);
    c.start();
    return 0;
}
