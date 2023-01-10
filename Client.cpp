#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "CheckInput.h"
#include "VectorCalDis.h"


using namespace std;

    /*
    * Func name: main
    * Input: int argc (num of terminal inputs), char *argv[] (the file name and inputs)
    * Output: int
    * Function operation: Expects an IP and a port to connect to, creates a socket
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
    if (!(isNumber(argv[2]) && isLegalPort(argv[2]))) {
        cout << "3rd input is not a legal port number!"<< endl;
        exit(1);
    }
    // checks if the ip is legal
    if (!isLegalIp(argv[1])) {
      cout << "first input is not a legal ip!!"<< endl;
      exit(1);
    }
    const int port_no = stoi(argv[2]);
    const char* ip_address = argv[1];

  // Create a socket
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
  {
    perror("error creating socket");
    return 1;
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
    return 1;
  }

  // Send a message to the server
  while (1) {
      string userInput;
      getline(cin, userInput);
      const char* pInput = userInput.c_str();
      // Removes leading spaces
      userInput.erase(0, userInput.find_first_not_of(' '));\
      int data_len = strlen(pInput);
      int sent_bytes = send(sock, pInput, data_len, 0);
      if (sent_bytes < 0) {
          // Error
          perror("error writing to socket");
          close(sock);
          exit(1);
      }
      if (!strcmp(pInput, "-1")) {
          close(sock);
          exit(0);
      }
      // Wait for a response from the server
      char buffer[4096];
      int expected_data_len = sizeof(buffer);
      int min_data_len = 2;
      int read_bytes = recv(sock, buffer, expected_data_len, 0);
      if (read_bytes == 0) {
          // Connection closed by the server
          perror("Connection closed by the server");
          close(sock);
          exit(1);
      } else if (read_bytes < 0) {
          // Error
          perror("error reading from socket");
          close(sock);
          exit(1);
       }
       string classification;
       // Append the data to the message
       classification.append(buffer, read_bytes);
       // Check if the entire message has been received
       if (read_bytes < min_data_len) {
           perror("error: The entire message was not recived");
           close(sock);
           exit(1);
       }
       cout << classification << endl;
  }
}

