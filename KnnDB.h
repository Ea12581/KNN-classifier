#ifndef KNNDB_H
#define KNNDB_H
#include <vector>
#include <string>
#include <map>
#include "KnnVec.h"

using namespace std;
/**
 * Class to create DB of clissified vector and classify other vectors acording to DB
*/
class KnnDB{
private:
    //vector member to restore all the clissifieds vectors
    vector <KnnVec> m_DB;
    // the k number of the closes vectors
    int m_k;
    // which metric we use to calculate the k closes
    std :: string m_metricType;
    // a mapping from the metric as a string to and int indifier.
    std :: map<string, int>  m_metricaMap;

public:


    void printDB(vector<pair<string, double>> v);


    static vector <KnnVec>* createDB(std :: string dirToFile);
    KnnDB(std :: string dbFile, int k, std :: string metric);
    KnnDB(std :: string dbFile);
    KnnDB();
    void setDB(vector<KnnVec>);
    vector<KnnVec> getDB();
    void setK(int k);
    int getK();
    void setMetric(string metric);
    string getMetric();
    double getDistance(VectorCalDis inputVec, KnnVec dbVec);
    // Creates a mapping that maps from the metrica str to an int
    void createMap();
    // Gets a vector of the Knn vectors with the relervant info in pairs.
    vector<pair<string, double>> findKnn(VectorCalDis);
    // Returns the most prevelant classification in the vector.
    string mostPrevalentCls(vector<pair<string, double>>);
    double cmpByDistance(const pair<string, double>, const pair<string, double>);
    // compares paris by their first value.
    double cmpByClass(const pair<string, double>, const pair<string, double>);
    // sorts the vector so that the k "smallest" classes will be in the first k indexes.
    void partialBubbleSortCls(vector<pair<string, double>> &v, int k);
    // sorts the vector so that the k shortest distances will be in the first k indexes.
    void partialBubbleSortDis(vector<pair<string, double>> &v, int k);
    void classifyPairs(vector<pair<VectorCalDis, string>>&);
    //create Knn DB from VakDisCal DB
    vector<KnnVec> createDBFromValCalDis(vector<VectorCalDis> db);
    //find the classification of ValCalVector
    string findClassification(VectorCalDis v);
};
#endif