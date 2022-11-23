// ex1_part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <sstream>
#include "Distance.h"
#include <stdlib.h>



using namespace std;


vector<double> getVectorAsInput() {
    string s;
    getline(cin, s);

    // ==================== input validation =====================
    // case 1: empty input
    if (size(s) == 0)
    {
        cout << "invalid input!";
            exit(1);
    }

    // case 2: space before vector's first element
    if (s[0] == char (' '))
    {
        cout << "invalid input!";
            exit(1);
    }

    // case 3: more than 1 space between 2 elements:
  
    // case 4: redundant space after the last element
    if (s[size(s)-1] == char(' '))
    {
        cout << "invalid input!";
        exit(1);
    }
    // case 5: dont think its necessary
    // case 6-10 
    // case 11: 2.
    // case 12: .2
  

    istringstream is(s);
    vector<double> v((istream_iterator<double>(is)), istream_iterator<double>());
    double x;

    while (is >> x) v.push_back(x);

    // case 16: dealing with chars
    for (int i = 0; i < size(v); i++)
    {
        if (v[i] == char()) {
            cout << "invalid input!";
            exit(1);
        }

    }

    return v;
}

bool IsAllZeros(vector<double> v) {
    for (int i = 0; i < size(v); i++)
    {
        if (v[i] == 0) {
            continue;
        }
        return true;
    }
}


int main()
{


    vector<double> v1 = getVectorAsInput();
    vector<double> v2 = getVectorAsInput();

    // input validation of 2 vectors:
    // case 13: vectors are equal 
    if (v1 == v2)
    {
        cout << "invalid input!";
        exit(1);
    }
    //case 15: vectors are in different length
    if (size(v1) != size(v2))
    {
        cout << "invalid input!";
            exit(1);
    }
    // case 14: one vector is zero and the other one is not
    if ( (IsAllZeros(v1)) ^ (IsAllZeros(v2)) )
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

// TODOS: continue input check if necessary