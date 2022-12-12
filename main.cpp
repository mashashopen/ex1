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
* command line args validation.
*
* @param
* @return true if all args are valid and false otherwise.
*/
bool setArgs(int argc,char* argv[],int& k, string& file, string& disMetric) {
    // argv:
    //1. k number 
    //2. the dataset
    //3. the distance metric

     //corrcet number of args:
    if (argc == 4)
    {
        //checking if first arg is an integter (k number)
        if (true)
        {

            //checking if second arg is correct string of database:
            if (argv[2]=="iris_Classified.csv" || argv[2]== "wine_Classified.csv" || argv[2]=="beans.Classified.csv")
            {

                //checking if third arg is correct string of distance metric:
                if (argv[3]== "AUC" ||argv[3]== "MAN" || argv[3]=="CHB" || argv[3]=="CAN"|| argv[3]=="MIN")
                {
                    return true;
                }

            }

        }

    }
    else if (argc > 4) {
        cout << "Too many arguments supplied.\n";
        return false;
    }
    else if (argc < 4) {
        cout << "Missing arguments.\n";
        return false;
    }

  
}




int main(int argc, char* argv[])
{

    int k;
    string disMetric;
    string file;

    //checking input from command line...
    if (!(setArgs(argc, argv, k, file, disMetric)))
    {
        cout << "invalid input!" << endl;
        exit(1);
    }

    //after validation- set the args:
     k = strtol(argv[1], NULL, 10);
     file = argv[2];
     disMetric = argv[3];
    

    // the vector to classified: 
    vector<double> v1 = getVectorAsInput();
  
    ReadDataSet classified("C:/Users/Maayan Vikel/Desktop/datasets/wine/wine_Classified.csv");
    vector<vector<string>> fileContent = classified.readFile();
    map<vector<double>, string> mappedData = classified.createMapOfData(fileContent);

        Knn knnModel(v1, k, disMetric, mappedData);

        cout << knnModel.predict() << endl;

    return 0;
}
