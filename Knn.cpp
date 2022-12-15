#include <iostream>
#include <vector>
#include <sstream>
#include "Distance.h"
#include <iterator>
#include <string>
#include <map>
#include "Knn.h"

using namespace std;

/*
* this function calculate the distance between vector input to all classified vectros.
*
* @return map so that the key is the distance value and the value is the lable. 
*/
map<double, string> Knn:: CalculateDistance() {
	map<double, string, less<double>> distanceLabel;
	map<vector<double>, string>::iterator it;
	for (it = m_mappedClassifiedData.begin(); it != m_mappedClassifiedData.end(); it++)
	{
		vector<double> classifiedVector = it->first;
		Distance d(m_v, classifiedVector, m_distanceType);
		distanceLabel[d.getDistanceValue()] = it->second;
	}

	return distanceLabel;
}


/*
* this function finds the k nearest vectors to the vector input.
*
* @return map so that the key is the distance value and the value is the lable (of all k nearwst vectors).
*/
map<double, string> Knn::FindKnearest() {
		///the distanceLabel map created in CalculateDistance is already sorted,
		// we now need to take k first values :
	map<double, string>::iterator it;
	map<double, string> kNearestNeighbors;
	int count = 0;
	for (it = m_mapDistanceLabel.begin(); it != m_mapDistanceLabel.end(); it++) {
			if (count == m_k)
				break;
			else
				count += 1;
				kNearestNeighbors[it->first] = it->second;
	}
		return kNearestNeighbors;
	}


/*
* this function predict the label of the input vector .
*
* @return the predicted label of the vector.
*/
	string Knn::predict() {
		//// now we have the map of k nearest vectors to our input vector. we need check which label 
		//// got the "higher score"--> that will be the predicted class of out input.
		vector<string> labels;
		string predictedLable;
		int freq = 0;
		map<double,string>::iterator it;
		// convert all lables into vector:
		for (it= m_kNearest.begin(); it != m_kNearest.end(); it++)
		{
			labels.push_back(it->second);
		}
		// find the most frequent string in this vector:
		for (int i = 0; i < labels.size(); i++)
		{
			int counter = 0;
			for (int j = 0; j < labels.size(); j++)
			{
				if (labels[j]== labels[i]) {
					counter = counter + 1;
				}
			}
			if (counter>=freq) {
				predictedLable = labels[i];
				freq = counter;
			}
		}	
		return predictedLable;
<<<<<<< HEAD:KNN.cpp
	}
=======
	}
	//check
>>>>>>> 9aba2048018c69e9e33ae6a7545cee1fa560b915:Knn.cpp
