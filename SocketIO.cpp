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

SocketIO::SocketIO(int server, int client) {
    m_server = server;
    m_client = client;
}

/**
 * getter for the id number of the server socket
 * @return int id socket
 */
int SocketIO::getMServer() const {
    return m_server;
}

/**
 * getter socket of the client id socket
 * @return int id socket
 */
int SocketIO::getMClient() const {
    return m_client;
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

    /*
    * Function Name: write
    * Input: string output (the string to output)
    * Output: none
    * Function Operation: Prints the string to output.
    */
    void SocketIO::DefaultIO::write(string output) {
        send(m_client, output.c_str(), output.length(), 0);
    }

