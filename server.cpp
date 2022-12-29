#include <iostream>
#include <string.h>

#include <vector>
#include <string>

#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "ReadDataSet.h"
#include "Knn.h"
#include "Distance.h"
#include <sstream>
#include <iterator>

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
        if (isalpha(s[i])) {
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
vector<double> stringToVector(string s) {

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




int main() {

    string file = "iris_classified.csv";    // need to receive as argument
    ReadDataSet classified(file);
    vector<vector<string>> fileContent = classified.readFile(); //read file
    //separate data to vector -> label
    map<vector<double>, string> mappedData = classified.createMapOfData(fileContent);

    const int server_port = 5555;   // need to receive as argument
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }

    while (true){

            if (listen(sock, 5) < 0) {
                perror("error listening to a socket");
            }

            struct sockaddr_in client_sin;
            unsigned int addr_len = sizeof(client_sin);
            int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);

            if (client_sock < 0) {
                perror("error accepting client");
            }

            char buffer[4096];
            int expected_data_len = sizeof(buffer);
            int read_bytes = recv(client_sock, buffer, expected_data_len, 0);

            string s;
            string distMetric;
            int k;

            // convert array to string
            for (int i = 0; i < expected_data_len; i++) {
                s = s + buffer[i];
            }

            size_t found;


            for (string disMetric: Distance::possibleMetrics()) {
                found = s.find(disMetric);
                if (found > 0 && found < s.length()) { // found the index of the metric inside the input
                    break;
                }
            }
            // parse the string into vector, distance metric and k

            string subVector = s.substr(0, found);
            distMetric = s.substr(found, 3);

            string subK = s.substr(found + 4);

            vector<double> v = stringToVector(subVector);
            k = stoi(subK);

            Knn knnModel(v, k, distMetric, mappedData);

            if (read_bytes == 0) {
                cout << "connection is closed" << endl;
            } else if (read_bytes < 0) {
                cout << "error" << endl;
            } else {
                cout << buffer;
            }
            const char *classResult = knnModel.predict().c_str();
            cout << classResult << endl;
            int sent_bytes = send(client_sock, classResult, read_bytes, 0);
            if (sent_bytes < 0) {
                perror("error sending to client");
            }
        }
    close(sock);
    return 0;
}

