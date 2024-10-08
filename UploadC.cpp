//
// Created by oem on 1/18/23.
//
#include "UploadC.h"
#include "KnnDB.h"
#include <iostream>
#include <utility>
#include <sstream>
#include <cstring>
#define DEFAULT_K 5
#define DEFAULT_METRIC "AUC"



/**
 * upload cvs unclassified VectorCalDis vectors file.
 * @param path  to the csv file
 * @return true if the upload was succeeded, false other wise
 */
bool UploadC::uploadTest() {
    //create DB of vectors
    vector <VectorCalDis>* test;
    // Read the Data from the file
    string vectors = getDio()->read();
    if(::strcmp(vectors.c_str(),"error") != 0) {
        test = new vector <VectorCalDis>;
        // ss is an object of stringstream that references the S string.
        stringstream ss(vectors);
        //line by line
        string line;
        int i = 0;
        // store it in a string variable 'line'
        while (getline(ss, line, '\n')) {
            i++;
            VectorCalDis v;
            string val;
            string newVec;
            VectorCalDis temp;
            // used for breaking to seperates values
            stringstream s(line);
            // read every value of date and
            // store it in a string with spaces, run untill he gets the last val (the classification), ignore - or . chars
            while (getline(s, val, ',')) {
                newVec += val;
                //insert space between every value
                newVec += " ";
            }
            //cut the \r ending
            newVec.replace(newVec.length() - 2, 1, "");
            //check if we can create vector from the values
            try{v = VectorCalDis::vectorFromString(newVec);} catch (exception e){cout << newVec;}
            //if we couldn't create vector from this record
            if (v.empty()) {
                continue;
            }
            test->push_back(v);
        }
    } else{
//if the path was not correct
        return false;
    }
//set the test file
    setMTest(test);
    //send the client
    getDio()->write("Upload complete");
    //get finish massage from client
    getDio()->read();
return true;
};

/**
 * upload cvs classified knn vectors file.
 * @param path  to the csv file
 * @return true if the upload was succeeded, false other wise
 */
bool UploadC::uploadTrain(){
    //create DB of vectors
    vector <KnnVec>* train;
    string vectors = getDio()->read();
    if(std::strcmp(vectors.c_str(),"error") != 0){
        train = new vector <KnnVec>;
        // ss is an object of stringstream that references the S string.
        stringstream ss(vectors);
        //take them lie by line
        string line;
        KnnVec v;
        while(getline(ss,line,'\n')){
            v = KnnVec :: createFromStr(line);
            //if we couldn't create vector from this record
            if(v.empty()) {
                continue;
            }
            train->push_back(v);
        }}else{
        return false;
    }
//set the test file
        setMTrain(train);
        return true;
    }



/**
 * override the method in command
 */
void UploadC::execute() {
//send the client
getDio()->write("Please upload your local train CSV file.");
//get the path through the dio
if(uploadTrain()){
    //if the upload had successes
    //send the client
    getDio()->write("Upload complete\nPlease upload your local test CSV file.");
    //check if succeeded
    if(uploadTest()){
        getSd()->setK(DEFAULT_K);
        getSd()->setMetric(DEFAULT_METRIC);
        return;
    }
    //if the upload of the test file hasn't succeeded, set the other file as nullPtr to wipe it from the shared data
    this->getSd()->freeTestSafely();
}
    getDio()->write("invalid input");
//get "finish" massage from client
    getDio()->read();
}

/**
 * create new Knn DB in the shared data
 * @param mTrain train knn vectors to build the Knn database
 */
void UploadC::setMTrain(vector<KnnVec> *mTrain) {
    this->getSd()->setKnnDb(new KnnDB(*mTrain));
}

/**
 * pass new unClassified vectors to the shared data
 * @param mTest pointer to the unClassified vectos
 */
void UploadC::setMTest(vector<VectorCalDis> *mTest) {
    this->getSd()->setUnClassified(mTest);
}


