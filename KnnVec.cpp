
#include <cstring>
#include <fstream>
#include <sstream>
#include "KnnVec.h"

using namespace std;

/*
* Func name: getClassification
* Input: void
* Output: string (the classification of the vector)
* Function operation: return a copy of the classification of the vector 
*/
string KnnVec :: getClassification(){
    return string(this->m_classificationType);
}

/*
* Func name: setClassification
* Input: string (the classification of the vector)
* Output: void
* Function operation: change the classification of the vector 
*/

void KnnVec :: setClassification(std :: string type){
    this->m_classificationType = string(type);
}

/*
* Func name: initializeFromAnotherVec
* Input: vector<double> v
* Output: void
* Function operation: copy values from another vector, in the same order 
*/

void KnnVec :: initializeFromAnotherVec(vector<double> v){
    for(auto x : v)
        this->push_back(x);
}

/*
* Func name: is_number
* Input: const std::string& s
* Output: bool
* Function operation: check that there are no alpha beit characters in the string 
*/
bool KnnVec :: is_number(const std::string& s){
    //return true only if s not contains characrters that not numeric (- and . allowed)
    return(strspn( s.c_str(), "-.0123456789" ) == s.size() );
}


/*
* Func name: createFromStr
* Input: std :: string newVec
* Output: KnnVec
* Function operation: create new vector from string that every value is seperate with , and his classification is the last value 
*/
KnnVec KnnVec :: createFromStr(std :: string line){
    KnnVec v;
    string val;
    string newVec;
    VectorCalDis temp;
    // used for breaking to seperates values
        stringstream s(line);
    // read every value of date and
    // store it in a string with spaces, run untill he gets the last val (the classification), ignore - or . chars
        while (getline(s, val, ',') && is_number(val)) {
            newVec += val;
            //insert space between every value
            newVec += " ";
        }
        //check if we can create vector from the values
        temp = vectorFromString(newVec);
        //if temp is not empty, create the new vector
        if(temp.size() != 0){
            //the val contain the last value, which is the classification
            v.setClassification(val);
            v.initializeFromAnotherVec(temp);
            return v;
        }
        //else, return an empty vector
        return v;  
}

KnnVec KnnVec::convertToKnn(std::string clas, VectorCalDis v) {
    KnnVec newV = KnnVec();
    //set the classification
    newV.setClassification(clas);
    //copy the values of v to the newV
    copy(v.begin(), v.end(), back_inserter(newV));
    return newV;
}


 




