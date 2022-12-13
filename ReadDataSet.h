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

public:
	ReadDataSet(string fileName) {
		
		m_fileName = fileName;
	}
	vector<vector<string>> readFile();
	map<vector<double>, string> createMapOfData(vector<vector<string>> fileContent);
};

