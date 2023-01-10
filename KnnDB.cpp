#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "KnnDB.h"
#include "KnnVec.h"
using namespace std;



/**
 * constructor to create DB from file, k number and type of metric
 * (fails if dbFile could not be loaded and sets m_k to -1 as a flag)
*/
KnnDB::KnnDB(string dbFile, int k, string metric){
    vector <KnnVec>* dbPointer = createDB(dbFile);
    if (dbPointer == NULL) {
        this->m_k = -1;
        return;
    }
    this->m_DB = *dbPointer;
    delete(dbPointer);
    this->m_metricType = string(metric);
    this->m_k = k;
    createMap();
};

/*
* Func name: createDB
* Input: string dirToFile, string with path to a cvs file which contains the vectors
* Output: vector <KnnVec>, vector of KnnVec vectors
* Function operation: create a DB of KnnVec vectors from csv file which contains the information on the vectors
*/
vector <KnnVec>* KnnDB :: createDB(string dirToFile){
    vector <KnnVec> *DB = new vector <KnnVec>;
    //stream pointer to the file
    ifstream fin;
    // Open an existing file
    fin.open(dirToFile, ios::in);
    //check if the openning has succeeded
    if(fin.is_open()) {
        // Read the Data from the file
        //line by line
        string line;
        // store it in a string variable 'line'
        while (getline(fin, line)) {
            KnnVec v;
            v = KnnVec :: createFromStr(line);
            //if we couldn't create vector from this record
            if(v.size() == 0) {
                continue;
            }
            DB->push_back(v);
        }
    fin.close();
    //if we couldn't open the file
  } else{
    return NULL;
  }
  return DB;
};

/**
 * constructor just with file name/path
 * (fails if dbFile could not be loaded and sets m_k to -1 as a flag)
*/
KnnDB::KnnDB(std :: string dbFile){
    vector <KnnVec>* dbPointer = createDB(dbFile);
    if (dbPointer == NULL) {
        this->m_k = -1;
        return;
    }
    this->m_DB = *dbPointer;
    delete(dbPointer);
    this->m_metricType = string("null");
    this->m_k = 0;
    createMap();
};

/**
 * constructor without arguments
*/
KnnDB::KnnDB(){
    this->m_metricType = string("null");
    this->m_k = 0;
    createMap();
};

/*
* Func name: createMap
* Input: None
* Output: void
* Function operation: Creates a map from the metrica as string
* to an int indifier to be used in a switch later.
*/
void KnnDB::createMap() {
    m_metricaMap.insert({"AUC", 0});
    m_metricaMap.insert({"MAN", 1});
    m_metricaMap.insert({"CHB", 2});
    m_metricaMap.insert({"CAN", 3});
    m_metricaMap.insert({"MIN", 4});
}

/*
* Func name: setDB
* Input: vector<KnnVec> newDB
* Output: void
* Function operation: initialize the db
*/
void KnnDB::setDB(vector<KnnVec> newDB){
    this->m_DB = newDB;
};

/*
* Func name: getDB
* Input: void
* Output: vector<KnnVec>
* Function operation: returning the vector of the db
*/
vector<KnnVec> KnnDB::getDB(){
    return this->m_DB;
};

/*
* Func name: setK
* Input: int k
* Output: void
* Function operation: set the number k (closest k vector to the unclissified one)
*/
void KnnDB::setK(int k){
    this-> m_k = k;
};

/*
* Func name: getK
* Input: int k
* Output: int k
* Function operation: get the number k (closes k vectors to the unclissified one)
*/
int KnnDB::getK(){
    return this-> m_k;
};

/*
* Func name: setMetric
* Input: string metric
* Output: void
* Function operation: set the matric distance which we shall calculate the closes k vectors to the unclissified one)
*/
void KnnDB::setMetric(string metric){
    this->m_metricType = string(metric);
};

/*
* Func name: getMetric
* Input: void
* Output: string metric
* Function operation: get the matric distance which we shall calculate the closes k vectors to the unclissified one)
*/
string KnnDB::getMetric(){
    return string(this->m_metricType);
};

/*
* Func name: getDistance
* Input: VectorCalDis inputVec (The input vector), KnnVec dbVec (a vector from the DB)
* Output: double (the distance between them)
* Function operation: Calculates and returns the distance between the input vector and a vector from
* the database. The distance is caluculated with the distance metrica stored at m_metricaType and
* translated through the map to implement switch case. 
*/
double KnnDB::getDistance(VectorCalDis inputVec, KnnVec dbVec) {
    switch (m_metricaMap.at(m_metricType)) {
        case 0:
            return inputVec.euclideanDis(dbVec);
        case 1:
            return inputVec.manhattenDis(dbVec);
        case 2:
            return inputVec.chebyshevDis(dbVec);
        case 3:
            return inputVec.canberraDis(dbVec);
        case 4:
            return inputVec.minkwskiDis(dbVec);
        default:
            return -1;
    }
}

/*
* Func name: findKnn
* Input: VectorCalDis inputVec (The vector to find Knn to)
* Output: a vector of pairs holding the k nearest neighbour's classification and distance.
* Function operation: Calculates the distances of every vector in KnnDB from the input vector
* with the distance method m_metricType. Saves the result in a vector of pairs holding the classification
* and the distance, and sorts the vector so that the knn will be in the first k indexes.
* Shrinks the result to a vector of k, and returns it sorted by the classifications.
*/
vector<pair<string, double>> KnnDB::findKnn(VectorCalDis inputVec) {
    // Gets the vectors from KnnVec
    vector <KnnVec> vectors = m_DB;
    vector<pair<string, double>> results;
    for (int i = 0; i < vectors.size(); i++) {
        // Finds the distance of the input vector and another vector
        double distance = getDistance(inputVec, vectors[i]);
        // Saves the classification and the distance of the other vector.
        pair<string, double> result = make_pair(vectors[i].getClassification(), distance);
        results.push_back(result);
    }
        // Puts the Knn in the first k indexes.
        KnnDB::partialBubbleSortDis(results, m_k);  
        results.resize(m_k);
        // Groups the Knn by their classification
        KnnDB::partialBubbleSortCls(results, m_k); 
        return results;
}


/*
* Func name: mostPrevalentCls
* Input: vector<pair<string, double>> (a vector of pairs with a classification string
* as the first value and the distance as the second, expected to be ordered by the classfication),
* closest.
* Output: the classfication the appears the most times
* Function operation: Goes over the vectors of paris with classifications, and counts every
* classification. every classification that reaches a new count of appearences, becomes the new
* most prevalent classification. returns the most prevalent classification at the end.
*/
string KnnDB::mostPrevalentCls(vector<pair<string, double>> closest) {
    // The first classification appears one time at the first index.
    string current = closest[0].first;
    // For now it is the classificatio that appeared the most.
    string resultStr = closest[0].first;
    int count = 1;
    int resultCount = 1;
    for (int i = 1; i < closest.size(); i++) {
        // if the classification didn't change, counts it
        if (current.compare(closest[i].first) == 0) {
            count++;
        } else {

            /* if classification count is larger than the old most prevalent
               it is now the new most prevalent */
            if (count > resultCount) {
                resultCount = count;
                resultStr = closest[i - 1].first;
            }
            /* if there aren't enough pairs to check to get a new
               most prevalent classification, returns the current*/
            if (resultCount >= closest.size() - i) {
                return resultStr;
            }
            // starts a new count for the new classification.
            count = 1;
            current = closest[i].first;
        }
    }
    return resultStr;
}

/*
* Func name: partialBubbleSort
* Input: vector<pair<string, double>> &v (a ref to vector of pairs), int k
* (num of sort loops in the outside loop).
* Output: None
* Function operation: Loops over the vector of pairs and sorts only by looping k times at
* the outside loop, in order to have the smallest distance values in the first k indexes.
*/
void KnnDB::partialBubbleSortDis(vector<pair<string, double>> &v, int k) {
    // loops k times
    for (int i = v.size() - 1; k > 0; i--, k--)
        // first elements are already in place
        for (int j = v.size() - 1; j >= v.size() - i; j--)
            if (cmpByDistance(v[j - 1], v[j]) > 0)
                swap(v[j - 1], v[j]);
}

/*
* Func name: partialBubbleSortCls
* Input: vector<pair<string, double>> &v (a ref to vector of pairs), int k
* (num of sort loops in the outside loop).
* Output: None
* Function operation: Loops over the vector of pairs and sorts only by looping k times at
* the outside loop, in order to group the classes together.
*/
void KnnDB::partialBubbleSortCls(vector<pair<string, double>> &v, int k) {
    // loops k times
    for (int i = v.size() - 1; k > 0; i--, k--)
        // first elements are already in place
        for (int j = v.size() - 1; j >= v.size() - i; j--)
            if (cmpByClass(v[j - 1], v[j]) > 0)
                swap(v[j - 1], v[j]);
}


/*
* Func name: cmpByDistance
* Input: const pair<string, double> v1, const pair<string, double> v2 -
* pairs with first value as calssification and the 2nd one as distance.
* Output: the comperassion result of the distances.
* Function operation: The function returns a positive number if
* p1's distance is larger than p2's. 0 if they are the same and a
* negative number if it is smaller.
*/
double KnnDB::cmpByDistance(const pair<string, double> p1, const pair<string, double> p2) {
    return p1.second - p2.second;
}

/*
* Func name: cmpByClass
* Input: const pair<string, double> v1, const pair<string, double> v2 -
* pairs with first value as calssification and the 2nd one as distance.
* Output: the comperassion result of the classfications.
* Function operation: The function returns a result of a comperassion
* between strings.
*/
double KnnDB::cmpByClass(const pair<string, double> p1, const pair<string, double> p2) {
    return p1.first.compare(p2.first);
}
    
        