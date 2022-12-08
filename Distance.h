#include <vector>
#include <string>

using namespace std;

class Distance {
	vector<double> m_v1, m_v2;
	double m_distanceValue;
	string m_distName;
public:

	Distance(vector<double> v1, vector<double> v2, string name) {
		m_v1 = v1;
		m_v2 = v2;
		m_distName = name;
		m_distanceValue = setRightDistanceFunction();
	}

	bool isWholeNumber();
	void printDistance();
	double setRightDistanceFunction();
};
double computeChebyshevDistance(vector<double> v1, vector<double> v2);
double computeCanberraDistance(vector<double> v1, vector<double> v2);
double computeEuclideanDistance(vector<double> v1, vector<double> v2);
double computeManhattanDistance(vector<double> v1, vector <double> v2);
double computeMinkowskiDistance(vector<double> v1, vector <double> v2);
vector<double> getVectorAsInput();
bool inputIsNotValid(string s);