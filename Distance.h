#include <vector>
#include <string>

using namespace std;

class Distance {
	vector<double> m_v1, m_v2;
	double m_distanceValue;
	string m_distName;
public:

	Distance(vector<double> v1, vector<double> v2, string type) {
		m_v1 = v1;
		m_v2 = v2;
		m_distanceValue = setRightDistanceFunction(type);

		//validation of the input vector and the vector from the classified file: 
		validationOfTwoVec(m_v1, m_v2);
	}
	void validationOfTwoVec(vector<double> v1, vector<double> v2);
	bool isWholeNumber();
	void printDistance();
	double setRightDistanceFunction(string distanceType);
	double getDistanceValue();
};
double computeChebyshevDistance(vector<double> v1, vector<double> v2);
double computeCanberraDistance(vector<double> v1, vector<double> v2);
double computeEuclideanDistance(vector<double> v1, vector<double> v2);
double computeManhattanDistance(vector<double> v1, vector <double> v2);
double computeMinkowskiDistance(vector<double> v1, vector <double> v2);
vector<double> getVectorAsInput();
bool inputIsNotValid(string s);