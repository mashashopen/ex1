#include "ReadDataSet.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;


///setting file name acording to argv[2]- the dataset
void ReadDataSet:: setFileName(string fileName){
	if (fileName == "iris_Classified.csv") {
		//m_fileName ="path"
		return;
	}
	else if (fileName == "wine_Classified.csv") {
		//m_fileName ="path"
		return;
	}
	else if (fileName == "beans.Classified.csv") {
		//m_fileName ="path"
		return;
	}
	//in case that the input (argv[2]) is wrong and doesnt match any of the datasets:
	cout << "Wrong data set!";
	exit(1);

}


vector<vector<string>> ReadDataSet:: readFile() {
    //string fname = "datasets/wine/wine_Classified.csv";

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
				numbers.push_back(stod(number));
			}
			else {
				label = fileContent[i][j];
			}

		}
		classified[numbers] = label;

	}
	return classified;
}


