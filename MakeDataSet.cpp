
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <unordered_map>

using namespace std;


vector<vector<string>> readFile() {
	string fname = "datasets/wine/wine_Classified.csv";

	vector<vector<string>> content;
	vector<string> row;
	string line, word;

	fstream file(fname, ios::in);
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
	for (int i = 0;i < content.size();i++) {
		cout << content[i][content[i].size() - 1] << " ";
		i += content[i].size();
	}
	return content;
}

// map all vectors into vector -> label

map<vector<double>, string> createMap(vector<vector<string>> content)
{
	map<vector<double>, string> classified;

	vector<double> numbers;
	string number;
	string label;

	for (int i = 0;i < content.size();i++) {
		numbers.clear();
		for (int j = 0;j < content[i].size();j++) {
			if (j != content[i].size() - 1) {
				number = content[i][j];
				numbers.push_back(stod(number));
			}
			else {
				label = content[i][j];
			}

		}
		classified[numbers] = label;

	}
	return classified;
}

int main() {
	vector<vector<string>> content = readFile();
	map<vector<double>, string> classified = createMap(content);

}
