#include <iostream>
#include <vector>
#include <sstream>
#include "Distance.h"
#include <iterator>
#include <string>
#include <map>
#include "Knn.h"

using namespace std;



	// calculate the distance between vector input to all classified vectros:
double Knn:: CalculateDistance() {
	map<double, string, less<double>> distanceLabel;
	map<vector<double>, string>::iterator it;
	vector<double> myInput = m_v;
	for (it = m_mappedClassifiedData.begin(); it != m_mappedClassifiedData.end(); it++)
	{
		vector<double> classifiedVector = it->first;
		Distance d(myInput, classifiedVector, m_distanceType);
		distanceLabel[d.setRightDistanceFunction()] = it->second;
	}
	return 0;
}



	//// finding the k nearest vectors to the input vector:
	//void FindKnearest() {
	//	//we will need to sort the array of distance from CalculateDistanc
	//	//and then take the k classes respectively, in this function we call CalculateDistanc
	//}



	//// when we have the k nearest vectors to our input vector, we will check which class 
	//// got the "higher score"--> that eill be the predicted class of out input.
	//int predict() {
	//	//in this fucntion we will call FindKnearest()
	//}


