#include "ReadDataSet.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;


vector<vector<string>> ReadDataSet:: readFile() {
	string fname = "datasets/wine/wine_Classified.csv";

	vector<vector<string>> content;
	vector<string> row;
	string line, word;

	fstream file(m_fileName, ios::in);
	if (file.is_open()) {
		while (getline(file, line)) {
			row.clear();

			stringstream str(line);

			while (getline(str, word, ','))
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
		cout << "Could not open the file\n";

	return content;
}

// map all vectors into vector -> label

map<vector<double>, string> ReadDataSet:: createMapOfData(vector<vector<string>> fileContent)
{
	map<vector<double>, string> classified;

	vector<double> numbers;
	string number;
	string label;

	for (int i = 0;i < fileContent.size();i++) {
		numbers.clear();
		for (int j = 0;j < fileContent[i].size();j++) {
			if (j != fileContent[i].size() - 1) {
				number = fileContent[i][j];
				double number_d = stod(number);
				numbers.push_back(number_d);
			}
			else {
				label = fileContent[i][j];
			}

		}
		classified[numbers] = label;

	}

	return classified;
}


