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
#include <regex.h>
#include <string>
#include "SocketIO.h"

SocketIO::SocketIO(int client) {
    m_client = client;
}

SocketIO::SocketIO() {
    m_server = 0;
    m_client = 0;
}

/**

 * getter for the id number of the server socket
 * @return int id socket
 */
int SocketIO::getMServer() const {
    return m_server;
}

void SocketIO::setMServer(int server) {
    m_server = server;
}

/**

 * getter socket of the client id socket
 * @return int id socket
 */
int SocketIO::getMClient() const {
    return m_client;
}

void SocketIO::setMClient(int client) {
    m_client = client;
}

/*
* Function Name: read
* Input: None
* Output: string (the input from the user)
* Function Operation: Gets input from the user and returns it.
*/

    string SocketIO::DefaultIO::read(){

        std::string message;
        char buffer[4096];
        int expected_data_len = sizeof(buffer);

        // Read data from the socket in chunks until the entire message has been received
        while (true)
        {

            int read_bytes = recv(m_client, buffer, expected_data_len, 0);

                // Append the data to the message
                message.append(buffer, read_bytes);
                // Connection closed by the client

            if (read_bytes < 0)
            {
                // Error
                perror("error reading from socket");
                break;
            }
            //if the buffer is not full, we read everything from the client
            if(read_bytes < expected_data_len)
                break;
            //clear the buffer
            memset(buffer,0,expected_data_len);
        }

        return message;
    }

    /*
    * Function Name: write
    * Input: string output (the string to output)
    * Output: none
    * Function Operation: Prints the string to output.
    */
    void SocketIO::write(string output) {
        output += '\n';
        send(m_client, output.c_str(), output.length(), 0);
    }

