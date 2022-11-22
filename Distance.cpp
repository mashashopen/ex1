#include "Distance.h"
#include <iostream>
#include <vector>


using namespace std;


double Distance::calculateDistance() {
	return m_distanceValue;
}
bool Distance::isWholeNumber() {
	return floor(m_distanceValue) == m_distanceValue;
}
void Distance::printDistance() {
	if(isWholeNumber()) {
		cout << m_distanceValue << ".0" << endl;
	}
	else {
		cout << m_distanceValue << endl;
	}
}

double computeChebyshevDistance(vector<double> v1, vector<double> v2) {
    vector<double> subtract(v1.size(), 0);

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

double computeCanberraDistance(vector<double> v1, vector<double> v2) {
    vector<double> tempVector(v1.size(), 0);

    double sum = 0;

    for (int i = 0; i < tempVector.size(); i++) {
        tempVector[i] = abs(v1[i] - v2[i]) / (abs(v1[i]) + abs(v2[i]));
    }

    for (int i = 0; i < tempVector.size(); i++) {
        sum += tempVector[i];
    }


    return sum;
}

double computeEuclideanDistance(vector<double> v1, vector<double> v2) {

    double sum = 0;

    for (int i = 0; i < size(v2); i++)
    {
        sum += pow((v1[i] - v2[i]), 2);
    }

    return sqrt(sum);

}
double computeManhattanDistance(vector<double> v1, vector <double>v2) {
    double sum = 0;

    for (int i = 0; i < size(v2); i++)
    {
        sum += abs((v1[i] - v2[i]));
    }

    return sum;

}

double computeMinkowskiDistance(vector<double> v1, vector <double>v2) {

    float order = size(v1) - 1;
    double sum = 0;
    double tempSum = 0;
    float x = 1.0 / order;
    for (int i = 0; i < size(v1); i++)
    {
        tempSum = abs(v1[i] - v2[i]);
        sum += pow(tempSum, order);
        tempSum = 0;
    }


    return pow(sum, (1 / order));

}