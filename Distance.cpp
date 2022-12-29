#include "Distance.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include <list>

/*
* input validation of 2 vectors.
* in case vectors are in different length, the program will end.
* 
* @param v1, v2- vectors to check.
*/
void Distance::validationOfTwoVec(vector<double> v1, vector<double> v2) {

   if (v1.size() != v2.size())
   {
       cout << "invalid input!";
           exit(1);
   }
 }

/*
* checks if number is whole.
* 
* @return true if is whole, false otherwise.
*/
bool Distance::isWholeNumber() {
	return floor(m_distanceValue) == m_distanceValue;
}


/*
* if a number is whole will force it to be printed with point
* zero in the end (and not as integer).
*/

void Distance::printDistance() {
	if(isWholeNumber()) {
        cout << m_distanceValue << ".0" << endl;
	}
	else {
        cout << m_distanceValue << endl;
	}
}

/*
* this function sets the distance metric according to the input.
*
* @param distanceType the string represent the distance metric
* @return the right compute distance function.
*/
double Distance::setRightDistanceFunction(string distanceType) {
    if (distanceType == "AUC") {
        return computeEuclideanDistance(m_v1, m_v2);
    }
    else if (distanceType == "MAN") {
        return computeManhattanDistance(m_v1, m_v2);
    }
    else if (distanceType == "CHB") {
        return computeChebyshevDistance(m_v1, m_v2);
    }
    else if (distanceType == "CAN") {
        return computeCanberraDistance(m_v1, m_v2);
    }
    else if (distanceType == "MIN") {
        return computeMinkowskiDistance(m_v1, m_v2);

    }
    else {
        exit(1);
    }
}

/*
* this function return the distance value.
*
* @return the distance value.
*/
double Distance::getDistanceValue() {
    return m_distanceValue;
}


/*
* Chebyshev distance.
*
* @param v1,v2 double type vectors.
* @return distance calculated by Chebyshev algorithm.
*/
double computeChebyshevDistance(vector<double> v1, vector<double> v2) {
    std::vector<double> subtract(v1.size(), 0);

    for (int i = 0; i < subtract.size(); i++) {
        subtract[i] = abs(v1[i] - v2[i]);
    }

    double max = 0;
    for (int i = 0; i < subtract.size(); i++) {
        if (subtract[i] > max)
            max = subtract[i];
    }

    return max;
}

/*
* Canberra distance.
*
* @param v1,v2 double type vectors.
* @return distance calculated by Canberra algorithm.
*/
double computeCanberraDistance(vector<double> v1, vector<double> v2) {
    std::vector<double> tempVector(v1.size(), 0);

    double sum = 0;

    for (int i = 0; i < tempVector.size(); i++) {
        tempVector[i] = abs(v1[i] - v2[i]) / (abs(v1[i]) + abs(v2[i]));
    }

    for (int i = 0; i < tempVector.size(); i++) {
        sum += tempVector[i];
    }


    return sum;
}

/*
* Euclidean distance.
*
* @param v1,v2 double type vectors.
* @return distance calculated by Euclidean algorithm.
*/
double computeEuclideanDistance(vector<double> v1, vector<double> v2) {

    double sum = 0;

    for (int i = 0; i < v2.size(); i++)
    {
        sum += pow((v1[i] - v2[i]), 2);
    }

    return sqrt(sum);

}

/*
* Manhattan distance.
*
* @param v1,v2 double type vectors.
* @return distance calculated by Manhattan algorithm.
*/
double computeManhattanDistance(vector<double> v1, vector<double>v2) {
    double sum = 0;

    for (int i = 0; i < v2.size(); i++)
    {
        sum += abs((v1[i] - v2[i]));
    }

    return sum;

}

/*
* Minkowski distance.
*
* @param v1,v2 double type vectors.
* @return distance calculated by Minkowski algorithm.
*/
double computeMinkowskiDistance(vector<double> v1, vector<double>v2) {

    float order = v1.size() - 1;
    double sum = 0;
    double tempSum = 0;
    float x = 1.0 / order;
    for (int i = 0; i < v1.size(); i++)
    {
        tempSum = abs(v1[i] - v2[i]);
        sum += pow(tempSum, order);
        tempSum = 0;
    }


    return pow(sum, (1 / order));

}