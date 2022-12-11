// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <sstream>
#include "Distance.h"
#include <iterator>
#include <string>
#include "ReadDataSet.h"
#include "Knn.h"



using namespace std;

/*
* checks if input is not valid.
*
* @param s, string represent future vector.
* @return true if is not valid, false otherwise.
*/
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

/*
* get vector as string input.
*
* @param s, string from user.
* @return v,the vector .
*/
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

    // input validation of 2 vectors:
    // case 3: vectors are in different length:
    /*if (v1.size() != v2.size())
    {
        cout << "invalid input!";
            exit(1);
    }*/
 
        //Distance manhattan(v1, v2, "MAN");
        ReadDataSet classifiedWines("datasets/iris/iris_Classified.csv");
        vector<vector<string>> winesContent = classifiedWines.readFile();
        map<vector<double>, string> mappedData = classifiedWines.createMapOfData(winesContent);

        Knn knnModel(v1, 3, "MAN", mappedData);

        cout << knnModel.predict() << endl;




    return 0;
}
