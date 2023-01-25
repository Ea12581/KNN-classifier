#include <iostream>
#include <limits>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Command.h"
#include "SocketIO.h"
#include "UploadC.h"
#include "Settings.h"
#include "Classify.h"
#include "Display.h"
#include "Download.h"
#include "CheckInput.h"
#include <unistd.h>
#define NUM_OF_CMDS 5


string printMenu(Command** cmd) {
    string menu = "Welcome to the KNN Classifier Server. Please choose an option:\n";
    for (int i = 0; i < NUM_OF_CMDS; i++) {
        menu.append(std::to_string(i+1));
        menu.append(". ");
        menu.append(cmd[i][0].getDesc());
        menu.append("\n");
    }
    menu.append("8. exit\n");
    return menu;
}

class CLI {

public:
    void start() {
        // Create a socket
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("error creating socket");
            exit(1);
        }
        struct sockaddr_in sin;
        memset(&sin, 0, sizeof(sin));
        sin.sin_family = AF_INET;
        sin.sin_addr.s_addr = INADDR_ANY;
        sin.sin_port = htons(12345);
        if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
            perror("error binding socket to m_port");
            exit(1);
        }

        while (true) {
            // Listen for incoming connections
            if (listen(sock, 5) < 0) {
                perror("error listening for connections");
                exit(1);
            }
            // Accept a new connection
            struct sockaddr_in client_addr;
            socklen_t client_addr_len = sizeof(client_addr);
            int clientSock = accept(sock, (struct sockaddr *) &client_addr, &client_addr_len);
            if (clientSock < 0) {
                perror("error accepting connection");
                continue;
            }

            ShareData *sd = new ShareData();
            SocketIO tempIO = SocketIO(clientSock);
            DefaultIO* IO = &tempIO;
            UploadC upload = UploadC("upload an unclassified csv data file", IO, sd);
            Settings settings = Settings("algorithm settings", IO, sd);
            Classify classify = Classify("classify data", IO, sd);
            Display display = Display("display results", IO, sd);
            Download download = Download("download results", IO, sd);
            Command *commands[NUM_OF_CMDS] = {&upload, &settings, &classify, &display, &download};
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
                        commands[option - 1]->execute();
                        break;
                    case 8:
                        isEight = true;
                        break;
                    default:
                        break;
                }
                if (!isEight) {
                    tempIO.write(printMenu(commands));
                    input = tempIO.read();
                    if (isNumber(&input[0])) {
                        option = stoi(input);
                    } else {
                        option = 0;
                    }
                }
            }
           // close(clientSock);
        }
    }
};



int main(int argc, char *argv[]) {
    CLI cli;
    cli.start();
    return 0;
}


