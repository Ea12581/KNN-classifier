#ifndef CMD_H
#define CMD_H
#include <string>
#include "DefaultIO.h"
#include "KnnDB.h"

using namespace std;
/*
 * class to share date between the commands of the server
 */
class ShareData{
private:
//database of classified vectors
    KnnDB* m_knnDB = nullptr;
    //database of unclassified vectors
    vector<VectorCalDis>* unClassified = nullptr;
    //database of the unclassified vectors after being classified
    vector<KnnVec>* classified = nullptr;
    //counter for how many objects has access to the shared data
    int counter = 0;
public:
    KnnDB *getKnnDb() const;

    void setKnnDb(KnnDB *knnDb);

    vector<VectorCalDis> *getUnClassified() const;

    void setUnClassified(vector<VectorCalDis> *unClassified);

    vector<KnnVec> *getClassified() const;

    int getK();

    string getMetric();

    void setClassified(vector<KnnVec> *classified);

    bool setK(int k);

    bool setMetric(string metric);

    void incCounter();

    void decCounter();

    bool isDataShared();

    bool isKnnDBExists();

    bool isUnClaExists();

    bool isClassifiedExists();

    bool isKExists();

    bool isMatricExists();

    virtual ~ShareData();

    void freeSafly();

    void freeTestSafely();
};

/**
 * Abstract class for the design pattern of Commend
 */
class Command {
private:
    //description represented by string
    string desc;
    //dio, a DefaultIO type
    DefaultIO* dio;
    //pointer to shared date between all the commands
    ShareData* sd;
public:
    ShareData *getSd() const;

    void setSd(ShareData *sd);

public:

    Command(string _desc, DefaultIO* _dio, ShareData* sd);
    void setDesc(string _desc);
    void setDio(DefaultIO* _dio);
    string getDesc();
    DefaultIO* getDio();
    virtual void execute() = 0;

    virtual ~Command();
};

#endif