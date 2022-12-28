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
vector<double> sringToVector(string s) {

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




int main(){

    string file = "iris_classified.csv";    // need to receive as argument
    ReadDataSet classified(file);
     vector<vector<string>> fileContent = classified.readFile(); //read file
     //separate data to vector -> label
     map<vector<double>, string> mappedData = classified.createMapOfData(fileContent);
    

    /*
    const int server_port = 5555;   // need to receive as argument
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
    perror("error creating socket");
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    if (bind(sock, (struct sockaddr*) &sin, sizeof(sin)) < 0){
    perror("error binding socket");
    }

    if (listen(sock, 5) < 0){
    perror("error listening to a socket");
    }

    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock, (struct sockaddr*)&client_sin, &addr_len);

    if (client_sock < 0){
    perror("error accepting client");
    }

    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(client_sock, buffer, expected_data_len, 0);

    string s;
    string disMetric = "";
    int k = 3;

    // convert array to string
    for(int i = 0; i < expected_data_len; i++){
        s = s + buffer[i];
    }*/
    string s = "1 2 3 4 MAN 3";

    const char* possibleMetrics[2] = { "MAN", "CHB"};
    size_t found;

    // PARSE THE STRING!!!!

    for (int i = 0; i < sizeof(possibleMetrics); i++){
        found = s.find(possibleMetrics[i]);
        if (found > 0){
            break;
        }
    }
     string subVector = s.substr(0 , found);
     string disMetric = s.substr(found, 3);
     
     string subK = s.substr(found + 4);

     vector<double> v = sringToVector(subVector);
     int k = stoi(subK);



    Knn knnModel(v, k, disMetric, mappedData);
    cout << knnModel.predict()<<endl;

    /*
    if (read_bytes == 0){
    // connection is closed
    }
    else if (read_bytes < 0)
    {
    // error
    }
    else{
        cout << buffer;
    }
    int sent_bytes = send(client_sock, buffer, read_bytes, 0);
    if (sent_bytes < 0){
    perror("error sending to client");
    }

    close(sock);
    */
    return 0;
}