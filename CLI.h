//
// Created by oem on 1/26/23.
//

#ifndef SER_CLI_H
#define SER_CLI_H

#include "SocketIO.h"
#include "Command.h"

/**
 * class to handle one client
 */

class CLI{
private:
    SocketIO* IO;
    Command** cmd;
public:
    CLI(SocketIO* IO);
    ~CLI();
    SocketIO* getSIO();
    Command** getCmds();
    void setCmds();
    std::string sendMenu();
    static void* start_helper(void* arg);
    void start();
};
#endif //SER_CLI_H
