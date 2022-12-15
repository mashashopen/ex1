#include <map>

class Knn {

	///members:
	int m_k; // the number to find k nearest neighbors
	vector<double> m_v;  //the input: vector with sizes of flowers //which metric to use (AUC/MAN/CHB/CAN/MIN)
	map<vector<double>, string> m_mappedClassifiedData;
	string m_distanceType;
	//
	map<double, string> m_mapDistanceLabel;
	map<double, string> m_kNearest;

public:
	Knn(vector<double> v, int val, string s, map<vector<double>, string> mappedClassifiedData){
		m_k = val;
		m_distanceType = s;
		m_mappedClassifiedData = mappedClassifiedData;
		m_v = v;
		m_mapDistanceLabel = CalculateDistance();
		m_kNearest = FindKnearest();
	}

	map<double, string> CalculateDistance();
	map<double, string> FindKnearest();
	string predict();
};
