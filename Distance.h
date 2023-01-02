#include <vector>
#include <string>
#include <list>
using namespace std;

class Distance {
	vector<double> m_v1, m_v2;
	double m_distanceValue;
	string m_distName;
    bool m_validVectors;
public:

	Distance(vector<double> v1, vector<double> v2, string type) {
		m_v1 = v1;
		m_v2 = v2;
		//validation of the input vector and the vector from the classified file:
        m_validVectors = validationOfTwoVec(m_v1, m_v2);
		m_distanceValue = setRightDistanceFunction(type);
		
	}

    static const list<string> possibleMetrics() { return {"MAN", "CHB", "AUC", "CAN", "MIN"}; }
	bool validationOfTwoVec(vector<double> v1, vector<double> v2);
	double setRightDistanceFunction(string distanceType);
	double getDistanceValue();
};
double computeChebyshevDistance(vector<double> v1, vector<double> v2);
double computeCanberraDistance(vector<double> v1, vector<double> v2);
double computeEuclideanDistance(vector<double> v1, vector<double> v2);
double computeManhattanDistance(vector<double> v1, vector <double> v2);
double computeMinkowskiDistance(vector<double> v1, vector <double> v2);