#ifndef KNNVEC_H
#define KNNVEC_H
#include <string>
#include <vector>
#include "VectorCalDis.h"
using namespace std;
/**
 * Class for a clissified vector
*/
class KnnVec : public VectorCalDis{
    //type member for clissifing the vector
    private:
    //member for his classification
         std :: string m_classificationType;
    public:
    /**
     * constructor that gets a clissified type
    */
        // Get his classification
        std :: string getClassification();
        // Set his classification
        void setClassification(std :: string type);
        // Initialize from other vector
        void initializeFromAnotherVec(vector<double> v);
        // Create vector from string.
        KnnVec static createFromStr(std :: string newVec);
        // Brief check to determine that the string contains only numeric chars
        bool static is_number(const std::string& s);
        // Create vector from classification and VecCalDis
        KnnVec static convertToKnn(std :: string clas, VectorCalDis v);
        
};
#endif