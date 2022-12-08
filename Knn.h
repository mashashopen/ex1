#include <map>

class Knn {

	//members:
	int m_k; // the number to find k nearest neighbors
	vector<double> m_v;  //the input: vector with sizes of flowers //which metric to use (AUC/MAN/CHB/CAN/MIN)
	map<vector<double>, string> m_mappedClassifiedData;
	string m_distanceType;

public:
	Knn(int val, string s){
		m_k = val;
		m_distanceType = s;
	}

	double CalculateDistance();

};
