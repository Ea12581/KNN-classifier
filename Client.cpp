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

using namespace std;

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
        cout << receive();
        cin >> decision;
        input += decision;
        //send the decsition to the server
        sendToSer(input);
        //clear the buffer
        getline(std::cin, input);
        input = "";
        switch(decision){
            case '1':
                cout << receive();
                //get path to classified vectors from user
                getline(cin, input);
                upload(input);
                //next massage from server
                cout << receive();
                //get path to unclassified vectors
                getline(cin, input);
                upload(input);
                input = "";
                break;
            case '5':
                //get input from user
                download("/home/oem/Documents/bar_ilan_courses/c++/ex4/write.txt");
                input = "";
                break;
            case '8':
                break;
            default:
                sendToSer();
                break;
        }
        cout << receive();
    }
    close(m_socket);

}

/**
 * receive massage from the server
 * @return string massage from the server
 */
string Client::receive() {
    // Wait for a response from the server
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    int min_data_len = 2;
    int read_bytes = recv(m_socket, buffer, expected_data_len, 0);
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
    string massage;
    // Append the data to the message
    massage.append(buffer, read_bytes);
    // Check if the entire message has been received
    if (read_bytes < min_data_len) {
        perror("error: The entire message was not recived");
        close(m_socket);
        exit(1);
    }
    return massage;
}

/**
 * send massage to the server
 */
void Client::sendToSer() {
    string userInput;
    getline(cin, userInput);
    userInput += '@';
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
    //sign for end massage
    userInput += '@';
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
 * upload new unclassified vectors from a cvs file
 */
void Client::upload(string path) {
    //stream pointer to the file
    ifstream fin;
    //check if this is a cvs file
    regex_t csv_regex;
    //compile the expression \.csv$, every string that ends with '.cvs'
    int ret = regcomp(&csv_regex, "\\.csv$", REG_EXTENDED);
    if (ret != 0) {
        printf("error compiling the regular expression\n");
    }

    ret = regexec(&csv_regex, path.c_str(), 0, NULL, 0);
    if (ret != 0) {
        // the regular expression does not match the input string
        printf("This is not a csv file\n");
    }

    regfree(&csv_regex);
    // Open an existing file
    fin.open(path, ios::in);
    //check if the openning has succeeded
    if(fin.is_open()) {
        // Read the Data from the file
        //line by line
        string line;
        // store it in a string variable 'line' and read it line by line
        while (getline(fin, line)) {
            //add /n
            line += '\n';
            const char* pInput = line.c_str();
            int data_len = strlen(pInput);
            int sent_bytes = send(m_socket, pInput, data_len, 0);
            if (sent_bytes < 0) {
                // Error
                perror("error writing to m_socket");
                close(m_socket);
                exit(1);
            }

        }
        fin.close();
        line += '@';
        const char* pInput = line.c_str();
        int data_len = strlen(pInput);
        int sent_bytes = send(m_socket, pInput, data_len, 0);
        if (sent_bytes < 0) {
            // Error
            perror("error writing to m_socket");
            close(m_socket);
            exit(1);
        }
        //if we couldn't open the file
    } else{
        sendToSer("error");
    }

}

/**
 * download the results of classifying the vectors which we have loaded earlier
 */
void Client::download(string path) {
    //stream pointer to the file
    ofstream fin;
    //check if this is a cvs file
    regex_t csv_regex;
    //compile the expression \.txt$, every string that ends with '.txt'
    int ret = regcomp(&csv_regex, "\\.txt$", REG_EXTENDED);
    if (ret != 0) {
        printf("error compiling the regular expression\n");
    }

    ret = regexec(&csv_regex, path.c_str(), 0, NULL, 0);
    if (ret != 0) {
        // the regular expression does not match the input string
        printf("This is not a txt file\n");
    }

    regfree(&csv_regex);
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    int min_data_len = 2;
    // Open an existing file
    fin.open(path, ios::out);
    //check if the openning has succeeded
    if(fin.is_open()) {
        // Read the Data from the socket
        //line by line
        string line;
        // store it in the buffer and write it to the file
        while (true) {
            int read_bytes = recv(m_socket, buffer, expected_data_len, 0);
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
            fin << buffer;
            // Check if the entire message has been received
            if (read_bytes < expected_data_len){
                perror("error: The entire message was not received");
                break;
            }

        }
        fin.close();
        //if we couldn't open the file
    } else{
        ::perror("couldn't open the file");
    }


}


