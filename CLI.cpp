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
#include "CLI.h"

#include <unistd.h>
#define NUM_OF_CMDS 5


/**
 * run the communication with the client
 */
    void CLI::start() {
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
                    getCmds()[option-1]->execute();
                    break;
                case 8:
                    isEight = true;
                    break;
                default:
                    break;
            }
            if (!isEight) {
                getSIO()->write(sendMenu());
                input = getSIO()->read();
                if (isNumber(input.c_str())) {
                    option = stoi(input);
                } else {
                    option = 0;
                }
            }
        }
        pthread_exit(NULL);
    }

/**
 * constructor
 * @param ID socketIO to communicate with client client
 */
CLI::CLI(SocketIO *IO) {
    this->IO = IO;
    setCmds();

}

/**
 * destructor
 */
    CLI::~CLI() {
        delete IO;
    }

/**
 * send menu to the client. create string that represent the menu
 * @return string of the menu
 */
    string CLI::sendMenu() {
        string menu = "Welcome to the KNN Classifier Server. Please choose an option:\n";
        for (int i = 0; i < NUM_OF_CMDS; i++) {
            menu.append(std::to_string(i + 1));
            menu.append(". ");
            menu.append(cmd[i][0].getDesc());
            menu.append("\n");
        }
        menu.append("8. exit");
        return menu;
    }

    void CLI::setCmds() {
        ShareData *sd = new ShareData();
        cmd = new Command *[NUM_OF_CMDS];
        cmd[0] = new UploadC("upload an unclassified csv data file", IO, sd);
        cmd[1] = new Settings("algorithm settings", IO, sd);
        cmd[2] = new Classify("classify data", IO, sd);
        cmd[3] = new Display("display results", IO, sd);
        cmd[4] = new Download("download results", IO, sd);
    }
/**
 * helper to run in a separate thread
 * @param arg the object himself
 * @return *void
 */
void *CLI::start_helper(void *arg) {
    CLI* self = static_cast<CLI*>(arg);
    self->start();
    delete self;
    return NULL;
}

/**
 * getter to the ScketIO
 * @return IO
 */
SocketIO *CLI::getSIO() {
    return this->IO;
}

/**
 * get the set of the commands
 * @return cmd, array of the commands
 */
Command **CLI::getCmds() {
    return cmd;
}

