// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <sstream>
#include "Distance.h"
#include <iterator>
#include <string>



using namespace std;

bool inputIsNotValid(string s) {
    // case 1: empty input
    if (s.size() == 0)
    {
        return true;
    }
 
    // case 2: dealing with chars
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == char()) {
            return true;
        }
    }
    return false;
}

vector<double> getVectorAsInput() {
    string s;
    getline(cin, s);

    if (inputIsNotValid(s)){
        cout << "invalid input!";
        exit(1);
    } 

    istringstream is(s);
    vector<double> v((istream_iterator<double>(is)), istream_iterator<double>());
    double x;

    while (is >> x) v.push_back(x);
    return v;
}

int main()
{

    vector<double> v1 = getVectorAsInput();
    vector<double> v2 = getVectorAsInput();

    // input validation of 2 vectors:
    // case 3: vectors are in different length:
    if (v1.size() != v2.size())
    {
        cout << "invalid input!";
            exit(1);
    }
 
        Distance manhattan(v1, v2, &computeManhattanDistance);
        Distance chebyshev(v1, v2, &computeChebyshevDistance);
        Distance minkowski(v1, v2, &computeMinkowskiDistance);
        Distance euclidean(v1, v2, &computeEuclideanDistance);
        Distance canberra(v1, v2, &computeCanberraDistance);

    euclidean.printDistance();
    manhattan.printDistance();
    chebyshev.printDistance();
    canberra.printDistance();
    minkowski.printDistance();

    return 0;
}