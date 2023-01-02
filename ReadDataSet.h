#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

class ReadDataSet
{
	string m_fileName;
    int m_numOfRows;

public:
	ReadDataSet(string fileName) {
		m_fileName = fileName;
        m_numOfRows = 0;    //initial value that will be updates during readFile function
	}
	vector<vector<string>> readFile();
	map<vector<double>, string> createMapOfData(vector<vector<string>> fileContent);
    int getNumOfRows();
};

