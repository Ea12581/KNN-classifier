//
// Created by oem on 12/31/22.
//

#ifndef B11_KNNSERVER_H
#define B11_KNNSERVER_H
#include "KnnDB.h"
/*
 * header for the server class
 */

class KnnServer{
private:
    KnnDB* m_KnnDBP;
    long m_port;
    int m_sockNum;
    int m_client;
    vector<string> splitMessage(string massage);
    std::string readMessage();
    int getMClient() const;
    void setMClient(int mClient);
public:
    explicit KnnServer(KnnDB *mKnnDbp);
    virtual ~KnnServer();
    int getPort() const;
    void setPort(int port);
    int getSockNum() const;
    void setSockNum(int sockNum);
    KnnDB *getMKnnDbp() const;
    void setMKnnDbp(KnnDB *mKnnDbp);
    int bindServer();
    int closeServer();
    int listenToNewConnections();

};

#endif //KNNSERVER_H
