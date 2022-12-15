#include "ReadDataSet.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;



/*
* this function reads the data from the file that user ask for.
*
* @return vectors so that each vector consists of numbers.
*/
vector<vector<string>> ReadDataSet:: readFile() {

	vector<vector<string>> content;
	vector<string> row;
	string line, word;

	fstream file(m_fileName, ios::in);
	if (file.is_open()) {
		while (getline(file, line)) {
			row.clear();

			stringstream str(line);

			while (getline(str, word, ',')) {
				row.push_back(word);
			}
			content.push_back(row);
		}
	}

	return content;
}


/*
* this function maps files content into vector -> label
*
* @param vectors so that each vector consists of numbers.
* @return map so that the key is vector and the value is the lable.
*/
map<vector<double>, string> ReadDataSet:: createMapOfData(vector<vector<string>> fileContent)
{
	map<vector<double>, string> classified;

	vector<double> numbers;
	string number;
	string label;

	// check if row doesnt contain vector and label (at leat 2 elements)
	if (fileContent.size() == 0) {
		cout << "not valid content" << endl;
		exit(1);
	}

	for (int i = 0;i < fileContent.size();i++) {
		// check if row doesnt contain vector and label (at leat 2 elements)
		if (fileContent[i].size() == 1) {
			cout << "not valid content" << endl;
			exit(1);
		}
		numbers.clear();
		for (int j = 0;j < fileContent[i].size();j++) {
			
			if (j != fileContent[i].size() - 1) {
				try {
					number = fileContent[i][j];
					double number_d = stod(number);
					numbers.push_back(number_d);
				}
				catch (...){
					cout << "not valid content" << endl;
					exit(1);
				}
			}
			else {
				label = fileContent[i][j];
			}

		}
		classified[numbers] = label;

	}

	return classified;
}