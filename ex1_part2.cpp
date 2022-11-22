// ex1_part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <sstream>


using namespace std;


float computeChebyshevDistance(vector<double> v1, vector<double> v2){
    vector<double> subtract(v1.size(), 0);

    for (int i = 0; i < subtract.size(); i++) {
        subtract[i] = abs(v1[i] - v2[i]);
    }

    float max = 0;
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


int main()
{

    string s1;
    string s2;

    getline(cin, s1);
    getline(cin, s2);

    istringstream is1(s1);
    istringstream is2(s2);

    vector<double> v1((istream_iterator<double>(is1)), istream_iterator<double>());
    vector<double> v2((istream_iterator<double>(is2)), istream_iterator<double>());

    double x;

    while (is1 >> x) v1.push_back(x);
    while (is2 >> x) v2.push_back(x);

    cout << computeChebyshevDistance(v1, v2) << endl;
    cout << computeCanberraDistance(v1, v2) << endl;
    
 
    return 0; 
}

// TODOS: input check, create separated file for all the distances calaulations 