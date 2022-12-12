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

void setArgs(int argc,char* argv[],int &k, string &disMetric) {
    // argv:
    //1. k number 
    //2. the dataset
    //3. the distance metric

     //corrcet number of args:
    if (argc == 3)// should be 4 with the dataset
    {
        k = *argv[1];
        disMetric = string(argv[2]); 

    }
    else if (argc > 3) {// should be 4 with the dataset
        cout << "Too many arguments supplied.\n";
        exit(1);
    }
    else if (argc < 3) {// should be 4 with the dataset
        cout << "Missing arguments.\n";
        exit(1);
    }
   

}

int main(int argc, char *argv[])
{
    int k;
    string disMetric;
    //string dataSet;
    
    setArgs(argc,argv,k,disMetric);
    cout << k; // print 51 ,why? should be 3 :(

    // the vector to classified: 
    vector<double> v1 = getVectorAsInput();
  
    ReadDataSet classified("C:/Users/Maayan Vikel/Desktop/datasets/iris/iris_classified.csv");
    vector<vector<string>> fileContent = classified.readFile();
    map<vector<double>, string> mappedData = classified.createMapOfData(fileContent);

        Knn knnModel(v1, k, disMetric, mappedData);

        cout << knnModel.predict() << endl;

    return 0;
}
