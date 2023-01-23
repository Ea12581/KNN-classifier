//
// Created by oem on 1/18/23.
//
#include "UploadC.h"
#include "KnnDB.h"
#include <iostream>
#include <utility>

/**
 * upload cvs unclassified VectorCalDis vectors file.
 * @param path  to the csv file
 * @return true if the upload was succeeded, false other wise
 */
bool UploadC::uploadTest(string path) {
    vector <VectorCalDis>* test;
    test = VectorCalDis::createUnClisDB(path);
//if the path was not correct
    if(test == NULL){
        getDio().write("invalid input");
        return false;
    }
//set the test file
    setMTest(test);
    //send the client
    getDio().write("Upload complete");
return true;
};

/**
 * upload cvs classified knn vectors file.
 * @param path  to the csv file
 * @return true if the upload was succeeded, false other wise
 */
bool UploadC::uploadTrain(string path){
    vector <KnnVec>* train = KnnDB::createDB(path);
//if the path was not correct
    if(train == NULL){
        getDio().write("invalid input");
        return false;
    }
//set the test file
    setMTrain(train);
    getDio().write("Upload complete");
    return true;
};


/**
 * override the method in command
 */
void UploadC::execute() {
//send the client
getDio().write("Please upload your local train CSV file.");
//get the path through the dio
string path = getDio().read();
if(uploadTrain(path)){
    //if the upload had successes
    //send the client
    getDio().write("Please upload your local test CSV file.");
    path = getDio().read();
    //check if succeeded
    if(uploadTest(path)){
        return;
    }
    //if the upload of the test file hasn't succeeded, set the other file as nullPtr to wipe it from the shared data
    this->getSd()->freeTestSafely();
}
}

/**
 * create new Knn DB in the shared data
 * @param mTrain train knn vectors to build the Knn database
 */
void UploadC::setMTrain(vector<KnnVec> *mTrain) {
    delete this->getSd()->getKnnDb();
    this->getSd()->setKnnDb(new KnnDB(*mTrain));
}

/**
 * pass new unClassified vectors to the shared data
 * @param mTest pointer to the unClassified vectos
 */
void UploadC::setMTest(vector<VectorCalDis> *mTest) {
    delete this->getSd()->getUnClassified();
    this->getSd()->setUnClassified(mTest);
}


