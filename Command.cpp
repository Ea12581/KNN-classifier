#include "Command.h"

#include <utility>
#include <iostream>

/**
 * get pointer to the shared KnnDB
 * @return KnnDB* pointer to the shared KnnDB
 */
KnnDB* ShareData::getKnnDb() const {
    return m_knnDB;
}

/**
 * set pointer to new shared KnnDB
 * @param knnDb pointer to new Knn db
 */
void ShareData::setKnnDb(KnnDB *knnDb) {
    delete this->m_knnDB;
    this->m_knnDB = knnDb;
}

/**
 * get pointer to the unclassified vectors
 * @return pointer to the unclassified vectors
 */
vector<VectorCalDis>* ShareData::getUnClassified() const {
    return unClassified;
}

/**
 * set pointer to the unclassified vectors
 * @param unClassified pointer to the unclassified vectors
 */
void ShareData::setUnClassified(vector<VectorCalDis> *unClassified) {
    delete this->unClassified;
    this->unClassified = unClassified;
}

/**
 * get pointer to the classified Knn vectors
 * @return pointer to the classified vectors
 */
vector<KnnVec>* ShareData::getClassified() const {
    return classified;
}

/**
 * set pointer to the classified Knn vectors
 * @param classified pointer to the classified Knn vectors
 */
void ShareData::setClassified(vector<KnnVec> *classified) {
    delete this-> classified;
    this->classified = classified;
}

/**
 * increase in 1 the counter
 */
void ShareData::incCounter() {
    counter++;
}

/**
 * decrease the counter by 1
 */
void ShareData::decCounter() {
    //avoid negative count
    if(counter == 0)
        return;
    counter--;

}

/**
 * function to check if there are still objects that shared the data
 * @return
 */
bool ShareData::isDataShared() {
    return counter > 0;
}

/**
 * destroy all the pointers
 */
ShareData::~ShareData() {
    delete this->m_knnDB;
    delete this->unClassified;
    delete this->classified;

}

/**
 * check if there is a KnnDB to classify with
 * @return true if exists, false if not
 */
bool ShareData::isKnnDBExists() {
    return this->m_knnDB != nullptr;
}

/**
 * check if there are unClassified vectors
 * @return true if exists, false if not
 */
bool ShareData::isUnClaExists() {
    return this->unClassified != nullptr;
}

/**
 * check if there are classified vectors
 * @return true if exists, false if not
 */
bool ShareData::isClassifiedExists() {
    return this->classified != nullptr;
}

/**
 * check if k has beinn chosen
 * @return true if above 0, false if not
 */
bool ShareData::isKExists() {
    return m_knnDB->getK() != 0;
}

/**
 * check if the metric type has being
 * @return true if exists, false if not
 */
bool ShareData::isMatricExists() {
    return m_knnDB->getMetric() != "none";
}

/**
 * set the number of neighbors for the knn classification
 * @param k neighbors
 * return: true if succeed, false if not
 */
bool ShareData::setK(int k) {
    //return false if there is no KnnDB
    if(m_knnDB == nullptr)
        return false;
    this->m_knnDB->setK(k);
    return true;
}

/**
 * set metric for the Knn classification calculation distance
 * @param metric string
 * @return true if succeed false if not
 */
bool ShareData::setMetric(string metric) {
    //return false if there is no KnnDB
    if(m_knnDB == nullptr)
        return false;
    this->m_knnDB->setMetric(metric);
    return true;
}

/**
 * get the k number neighbors which Knn classify
 * @return k int type
 */
int ShareData::getK() {
    return this->m_knnDB->getK();
}

/**
 * get the metric which by it the Knn calculate the distances
 * @return string that represent the metric
 */
string ShareData::getMetric() {
    return this->m_knnDB->getMetric();
}

/**
 * free safely the KnnDB
 */
void ShareData::freeTestSafely() {
    delete this->m_knnDB;
    this->m_knnDB = nullptr;
}

/*
 * constructor with description and dio arguments
 */
Command::Command(string _desc, DefaultIO *_dio, ShareData* _sd) {
    desc = std::move(_desc);
    dio = _dio;
    sd = _sd;
    //increase the number of the objects that have access to the shared data
    sd->incCounter();
}

/**
 * set the description
 * @param _desc
 */
void Command::setDesc(string _desc) {
    desc = std::move(_desc);
}
/**
 * set the dio
 * @param _dio
 */
void Command::setDio(DefaultIO* _dio) {
    dio = _dio;
}

/**
 * get the description
 * @return
 */
string Command::getDesc() {
    return desc;
}
/**
 * get the dio
 * @return
 */
DefaultIO* Command::getDio() {
    return dio;
}

/**
 * get pointer to shared data
 * @return pointer to shred data
 */
ShareData *Command::getSd() const {
    return sd;
}

/**
 * set pointer to shared data
 * @param sd new pointer to new shared data
 */
void Command::setSd(ShareData *_sd) {
    //decrease the counter of the shared data
    this->sd->decCounter();
    //check if nobody has access to this shared data
    if(!this->sd->isDataShared()){
        delete this->sd;
    }
    Command::sd = _sd;
}

/**
 * destructor to free the shared data
 */
Command::~Command() {
    //decrease the counter of the shared data
    this->sd->decCounter();
    //check if nobody has access to this shared data
    if(!this->sd->isDataShared()){
        delete this->sd;
    }

}