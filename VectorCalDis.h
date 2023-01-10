#ifndef VECTOR_H
#define VECTOR_H
#include <string>
#include <vector>

/*
* Class that inheret vector and adds distance methods.
*/
class VectorCalDis : public std::vector<double>{
    public:
        static VectorCalDis vectorFromString(std::string&);
        void resizeShorter(VectorCalDis&);
        double euclideanDis(VectorCalDis&);
        double chebyshevDis(VectorCalDis&);
        double minkwskiDis(VectorCalDis&);
        double canberraDis(VectorCalDis&);
        double manhattenDis(VectorCalDis&);
        bool didOverflow(double, double);
};
#endif