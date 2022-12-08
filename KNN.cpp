#include <iostream>
#include <vector>
#include <sstream>
//#include "Distance.h"
#include <iterator>
#include <string>
#include <map>

using namespace std;


class knn {

	//members:
	int m_k; // the number to find k nearest neighbors
	vector<double> m_v;  //the input: vector with sizes of flowers
	string m_distanceType; //which metric to use (AUC/MAN/CHB/CAN/MIN)
	map<vector<double>, string> m_mappedClassifiedData;

	//also we want to keep our k nearest vectors, and all vectors from training data,how?


public:
	//constructor that takes in an int
	knn(int val, string s) {
		m_k = val;
		m_distanceType = s;
	}

	//diconstructor
	~knn()
	{
		// nothing to do
	}

	// calculate the distance between vector input to all classified vectros:
	double CalculateDistance() {




		//for loop to go over the samples (vectors) in the classified file:


	}

	// finding the k nearest vectors to the input vector:
	void FindKnearest() {
		//we will need to sort the array of distance from CalculateDistanc
		//and then take the k classes respectively, in this function we call CalculateDistanc
	}



	// when we have the k nearest vectors to our input vector, we will check which class 
	// got the "higher score"--> that eill be the predicted class of out input.
	int predict() {
		//in this fucntion we will call FindKnearest()
	}


};