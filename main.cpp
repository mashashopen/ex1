// ex1_part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <sstream>
#include "Distance.h"


using namespace std;


vector<double> getVectorAsInput() {
    string s;
    getline(cin, s);
    istringstream is(s);
    vector<double> v((istream_iterator<double>(is)), istream_iterator<double>());
    double x;
    //add here input checks!!
    while (is >> x) v.push_back(x);

    return v;
}


int main()
{

    vector<double> v1 = getVectorAsInput();
    vector<double> v2 = getVectorAsInput();

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

// TODOS: input check 