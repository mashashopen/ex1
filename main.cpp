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
#include <algorithm>

#include <stdlib.h>

using namespace std;

/*
* checks if input (vector) is not valid.
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

/*
* checks if string is actully a integer number.
*
* @param s,the string to check.
* @return true if it is integer, false otherwise.
*/
bool isNumber(const string& s)
{
    for (char const& ch : s) {
        if (std::isdigit(ch) == 0)
            return false;
    }
    return true;
}

/*
* command line args validation.
*
* @param argc, argv, k, file, disMetirc- all arguments from cmd.
* @return true if all args are valid and false otherwise.
*/
bool areValidArguments(int argc,char* argv[],int& k, string& file, string& disMetric) {
    /*argv:
    1. k number 
    2. the dataset file
    3. the distance metric type
    */
    bool valid = true;

     //corrcet number of args:
    if (argc == 4){
        //checking if first arg is an integter (k number)
        if (!isNumber(argv[1]) || strtol(argv[1], NULL, 10) <= 0) {
            valid = false;
        }

        //checking if third arg is correct string of distance metric:
        string distType = argv[3];
        if (!(distType == "AUC" || distType == "MAN" || distType == "CHB" || distType == "CAN" || distType == "MIN")) {
            valid = false;
        }
    }
    else if (argc > 4) {
        cout << "Too many arguments supplied.\n";
        valid = false;
    }
    else{ //(argc < 4)
        cout << "Missing arguments.\n";
        valid = false;
    }
    return valid;

  
}


int main(int argc, char* argv[])
{

    int k;
    string disMetric;
    string file;

    //checking input from command line...
    if (!(areValidArguments(argc, argv, k, file, disMetric)))
    {
        cout << "invalid input!" << endl;
        exit(1);
    }

    //after validation- set the args:
     k = strtol(argv[1], NULL, 10);
     file = argv[2];
     disMetric = argv[3];
    

     //get input vector and use knn model forever
     while (true) {
         // the vector to classified: 
         vector<double> v1 = getVectorAsInput();

         ReadDataSet classified(file);
         vector<vector<string>> fileContent = classified.readFile();
         map<vector<double>, string> mappedData = classified.createMapOfData(fileContent);

         Knn knnModel(v1, k, disMetric, mappedData);

         cout << knnModel.predict() << endl;
     }

    return 0;
}
