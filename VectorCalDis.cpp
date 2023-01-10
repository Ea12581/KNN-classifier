#include <vector>
#include <math.h>
#include <cmath>
#include <string>
#include <limits>
#include "VectorCalDis.h"

using namespace std;

    /*
    * Func name: didOverflow
    * Input: double num1, double num2 (two doubles)
    * Output: bool (True if overflow, false if not)
    * Function operation: Tests to see if the result of num1 - num2 will
    * overflow  or underflow. if it does, returns true. if it doesn't, returns
    * false.
    */
    bool VectorCalDis::didOverflow (double num1, double num2) {
        double result = num1 - num2;
        if (num1 == 0 || num2 == 0) {
            return false;
        }
        if ((((num1 < 0.0) == (num2 > 0.0)) || ((num1 > 0.0) == (num2 < 0.0))) &&
        abs(num2) > (numeric_limits<double>::max() - abs(num1))) {
            return true;
        }
        return false;
    }
    
    /*
    * Function Name: vectorFromString
    * Input: string line (a string from the user)
    * Output: VectorCalDis (empty if failed)
    * Function operation: Goes over the line, skipping spaces
    * and looking for only legal chars: a digit, a '.' or a '-'.
    * if it finds a digit, starts counting for a sequance of digits.
    * more than 307 digits in a row can lead to an overflow for a
    * double. however if it is stopped with '.' the counting stops.
    * allows '-' only if it's before a digit or '.', and after
    * a space or the first char in the input.
    * allows '.' only if it is before or after a digit, it isn't after
    * another '.' and only numbers, and it can also be after a space
    * or a '-' (if it is before a number).
    * If the string follows all these rules, it means it has doubles in
    * it and they can be added to a vector. returns a new VectorCalDis
    * with the values of the string.
    */
    VectorCalDis VectorCalDis::vectorFromString(string &line) {
    int countBeforePoint = 0;
    int flag = 0;
    int i = 0;
    // Will be returned for illegal strings.
    VectorCalDis emptyV;
    VectorCalDis v;
    // Goes over the string.
    while (i < line.size()) {
    // skips spaces
    if (line[i] == ' ') {
        i++;
        continue;
    } else {
        // only allows digits, '.' or '-'.
        if(isdigit(line[i]) || line[i] == '-' || line[i] == '.') {
            int j = i;
            // goes over a potential double value.
            while (line[j] != ' ' && j < line.size()) {
                if (isdigit(line[j])) {
                    if (flag == 0) {
                    // counts digits before the decimal point.
                    countBeforePoint++;
                    }
                    j++;
                    // May overflow, avoids it.
                    if (countBeforePoint > 307) {
                        return emptyV;
                    }
                } else {

                    /*
                    * '-' can only be as:
                    * The first char and have a digit or a '.' after it.
                    * A char after a space and have a digit or a '.' after it.
                    */ 
                    if (line[j] == '-' && ((j == 0) || (line[j - 1] == ' ')) &&
                        (isdigit(line[j + 1]) || (line[j + 1] == '.' ))) {
                        j++;
                    } else {
                        /*
                        * '.' can only be as:
                        * With a digit after it or before it, and with a space where there is no digit.
                        * With a '-' before it and a digit after it.
                        * If there wasn't any other '.' and a sequence of numbers before it.
                        */
                        if (line[j] == '.' && flag == 0 &&
                            (((j != 0) && (isdigit(line[j - 1]) ||
                            (line[j - 1] == '-' || line[j - 1] == ' ') && isdigit(line[j + 1]))) ||
                            isdigit(line[j + 1])))  {
                        // Found decimal point, stops counting
                        flag = 1;
                        j++; 
                        // The '.' or '-' are not legal.
                        } else {
                        return emptyV;
                        }
                    }
                }
            }
        // Will count digits again
        flag = 0;
        // Saves the legal double value in the vector.
        string num = line.substr(i, j);
        v.push_back(stod(num));
        // Jumps to after the value.
        i = j;
        // Illegal char.
        } else {
            return emptyV;
        }
    }
}
return v;
}

    /*
    * func name: resizeShorter
    * input: vector<double>& other
    * output: void
    * use: compares the vector to another vector and enlarges the shorter one.
    */
    void VectorCalDis::resizeShorter(VectorCalDis& other){
        //if v1 is the shorter
            if(this->size() < other.size()){
                this->resize(other.size());
            } else {
                other.resize(this->size());
            }
    }

    /*
    * Func name: didOverflow
    * Input: double num1, double num2 (two doubles)
    * Output: bool (True if overflow, false if not)
    * Function operation: Tests to see if the result of num1 - num2 will
    * overflow  or underflow. if it does, returns true. if it doesn't, returns
    * false.
    */
    bool didOverflow (double num1, double num2) {
        double result = num1 - num2;
        if (((num1 < 0.0) == (num2 > 0.0)) || ((num1 > 0.0) == (num2 < 0.0)) &&
        abs(num2) > (numeric_limits<double>::max() - abs(num1))) {
            return true;
        }
        return false;
    }

        /*
        * Func name: manhattenDis
        * Input: vector<double>& other an other vector.
        * Output: double (the manhatten distance or -1 for overflow)
        * Function operation: Goes over the vectors, calculates the
        * manhatten distance with sum(|v1[i] - v2[i]) and returns the
        * result.
        */
        double VectorCalDis::manhattenDis(VectorCalDis& other){
        //checks if they aren't the same size
        if(this->size() != other.size()){
            resizeShorter(other);
        }
        double distance = 0;
        for(int i = 0; i < other.size(); i++){
            distance += abs(this->at(i) - other.at(i));
            // Checks for overflow
            if (didOverflow(this->at(i), other.at(i))) {
                return -1;
            }
        }
        return distance;
    }

        /*
        * Func name: canberraDis
        * Input: vector<double>& other an other vector.
        * Output: double (the canberra distance or -1 for overflow)
        * Function operation: Goes over the vectors, calculates the
        * canberra distance with sum(|v1[i] - v2[i]| / (|v1[i]| + |v2[i]|))
        * and returns the result.
        */
        double VectorCalDis::canberraDis(VectorCalDis& other){
        //checks if they aren't the same size
        if(this->size() != other.size()){
            resizeShorter(other);
        }
        double distance = 0;
        for(int i = 0; i < other.size(); i++){
            if (this->at(i) == 0 && other.at(i) == 0) {
                continue;
            }
            distance += abs(this->at(i) - other.at(i)) /
            (abs(this->at(i)) + abs(other.at(i))); 

            /*
            * Checks for overflow.
            * Can overflow either when calculating v1[i] - v2[i] or
            * when calulating |v1[i]| + |v2[i]|. sends -|v2[i]| since
            * the method checks param1 - param2, so now it will check
            * param1 + param2 just like we want.
            * if the params are the same, the 2nd overflow won't matter
            * since we have 0/number = 0.
            */
            if (didOverflow(this->at(i), other.at(i)) || 
                ((this->at(i) != other.at(i)) && (didOverflow(this->at(i), -other.at(i))))) {
                return -1;
            }
        }
        return distance;
        }

    /*
    * func name: euclideanDis
    * input: vector<double> other
    * output: double (the distance or -1 for overflow)
    * use: calculates the euclidean distance between this vector and another one (other). It
    * calculates every (this_i - other_i)^2 for every index i, sum them up and returns the sqrt
    * of the sum.
    */
    double VectorCalDis::euclideanDis(VectorCalDis& other){
        //check if they are not the same size
        if(this->size() != other.size()){
            resizeShorter(other);
        }
        double distance = 0;
        //iterates over the vectors and calculates distance of all their dementions with ((pi-qi)^2)
        for(int i = 0; i < other.size(); i++){
            distance += (this->at(i) - other.at(i)) * (this->at(i) - other.at(i)); 
            //Checks for overflow
            if (didOverflow(this->at(i), other.at(i))) {
                return -1;
            }
        }
        return sqrt(distance);
    }

    /*
    * func name: chebyshevDis
    * input: vector<double> other
    * output: double (the distance or -1 for overflow)
    * use: calculates chebyshev distance betwen this vector and another one (other). compare every
    * delta this_i - other_i, between the values of the vectors and return the max
    */
    double VectorCalDis::chebyshevDis(VectorCalDis& other){
        //checks if they aren't the same size
        if(this->size() != other.size()){
            resizeShorter(other);
        }
        //take the first distance of index 0
        double maxDistance = abs(this->at(0) - other.at(0));
        //iterates over the vectors and calculates every distance in every index. replaces with the max if it's
        //greater.
        for(int i = 0; i < this->size(); i++){
            //Checks for overflow
            if (didOverflow(this->at(i), other.at(i))) {
                return -1;
            }
            if(maxDistance < abs(this->at(i) - other.at(i))){
                maxDistance = abs(this->at(i) - other.at(i));
            }
        }
        return maxDistance;

    }

    /**
    * func name: minkwskiDis
    * input: vector<double> other
    * output: double (the distance)
    * use: Calculates the minkwski distance between this vector and another one (other). calculates by
    * the formula D(this,other) = (sum(|this_i - other_i|^p)^1/p
    * our P == 4
    */
    double VectorCalDis::minkwskiDis(VectorCalDis& other){
        //checks if they aren't the same size
        if(this->size() != other.size()){
            resizeShorter(other);
        }
        float P = 4;
        double minkovswiSum = 0;
        // if P == 1, the distance equal to manhatten
        if(P == 1){
            return this->manhattenDis(other);
        }
        // if P == 2, the distance equal to euclidean
        if(P == 2){
            return this->euclideanDis(other);
        }
        //sums every expression (|this_i - other_i|^p
        for(int i = 0; i < this->size(); i++){
            minkovswiSum += pow(abs(this->at(i) - other.at(i)), P);
            /*
            * Checks for overflow.
            * Uses this logic for the pow:
            * x^p <= max <=> log(x^p) <= log(max) <=> p * log(x) <= log(max) <=> p <= log(max) / log(x).
            */
            if (didOverflow(this->at(i), other.at(i)) ||
                (P * log(abs(this->at(i) - other.at(i))) > log(numeric_limits<double>::max())) ) {
                return -1;
            }
        }
        minkovswiSum = pow(minkovswiSum, 1/P);
        return minkovswiSum;

    }
