//
// Created by oem on 1/22/23.
//

#ifndef EX4_CLIENT_H
#define EX4_CLIENT_H
#include <string>
/**
 * class for handling the client side
 */
using namespace std;
class Client{
private:
    int m_socket;
    bool keepAlive;
public:
    Client(char* ip, string port);

    int getSock() const;

    void setSock(int sock);

    void start();

    string receive();

    void sendToSer();

    void sendToSer(string userInput);

    void download(string path);

    bool upload(string path);

    void uploadDB();

    void chooseMetricK();
};
#endif //EX4_CLIENT_H
