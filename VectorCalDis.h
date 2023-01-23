#ifndef VECTOR_H
#define VECTOR_H
#include <string>
#include <vector>

/*
* Class that inheret vector and adds distance methods.
*/
class VectorCalDis : public std::vector<double>{
    public:
        VectorCalDis();
        VectorCalDis(std::vector<double> v);
        static VectorCalDis vectorFromString(std::string&);
        static vector <VectorCalDis>* createUnClisDB(std::string dirToFile);
        void resizeShorter(VectorCalDis&);
        double euclideanDis(VectorCalDis&);
        double chebyshevDis(VectorCalDis&);
        double minkwskiDis(VectorCalDis&);
        double canberraDis(VectorCalDis&);
        double manhattenDis(VectorCalDis&);
        bool didOverflow(double, double);

};
#endif