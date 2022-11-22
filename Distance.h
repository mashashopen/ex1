#include <vector>

using namespace std;

class Distance {
	vector<double> m_v1, m_v2;
	double m_distanceValue;
public:
	Distance(vector<double> v1, vector<double> v2, double (*calculateDistance)(vector<double>, vector<double>)) {
		m_v1 = v1;
		m_v2 = v2;
		m_distanceValue = calculateDistance(v1, v2);
	}

	double calculateDistance();
	bool isWholeNumber();
	void printDistance();
};
double computeChebyshevDistance(vector<double> v1, vector<double> v2);
double computeCanberraDistance(vector<double> v1, vector<double> v2);
double computeEuclideanDistance(vector<double> v1, vector<double> v2);
double computeManhattanDistance(vector<double> v1, vector <double>v2);
double computeMinkowskiDistance(vector<double> v1, vector <double>v2);
vector<double> getVectorAsInput();