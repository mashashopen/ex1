#include <iostream>
#include <string.h>

#include <vector>
#include <string>

#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include "ReadDataSet.h"
#include "Knn.h"
#include "Distance.h"
#include "ParseAndValidate.h"

#include <stdlib.h>

using namespace std;

/*
* command line args validation.
*
* @param argc, argv
* @return true if all args are valid and false otherwise.
*/
bool areValidArguments(int argc, char *argv[]) {
    /*argv:
    1. file
    2. port number
    */
    bool valid = true;

    //correct number of args:
    if (argc == 3) {
        //checking if second arg (port number) is correct range
        if (strtol(argv[2], NULL, 10) < 1024 || strtol(argv[2], NULL, 10) > 65535) {
            valid = false;
        }
    } else if (argc > 3) {
        cout << "Too many arguments supplied.\n";
        valid = false;
    } else { //(argc < 3)
        cout << "Missing arguments.\n";
        valid = false;
    }
    return valid;

}


int main(int argc, char *argv[]) {

    //checking input from command line...
    if (!(areValidArguments(argc, argv))) {
        cout << "invalid input! port number is not in correct range." << endl;
        exit(1);
    }

    //after validation - set the args:
    string file = argv[1];
    const int server_port = strtol(argv[2], NULL, 10);

    ReadDataSet classified(file);


    vector<vector<string>> fileContent = classified.readFile(); //read file
    //separate data to vector -> label
    map<vector<double>, string> mappedData = classified.createMapOfData(fileContent);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
        exit(1);
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
        exit(1);
    }


    if (listen(sock, 5) < 0) {
        perror("error listening to a socket");
        exit(1);
    }

    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);

    if (client_sock < 0) {
        perror("error accepting client");
        exit(1);
    }

    while (client_sock) {
        char buffer[4096] = {};
        const char *classResult = "";   //this the server will send as an answer to the client

        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
        if (read_bytes == 0) {
            cout << "connection is closed" << endl;
            exit(1);
        } else if (read_bytes < 0) {
            cout << "error" << endl;
            exit(1);
        }

        string s;

        // convert array to string
        for (int i = 0; i < expected_data_len; i++) {
            if (!buffer[i]) {     //include only actual data without zero values
                break;
            }
            s = s + buffer[i];
        }

        if (s == "-1") {
            close(client_sock);
            client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
            continue;
        }

        ParseAndValidate input(s);

        // parse the string into vector, distance metric and k
        string distMetric = input.getDistMetric();
        vector<double> v = input.getVector();
        int k = input.getK();



        if (input.isValidInput()) {

            // checking if  k > number of rows:
            if (classified.getNumOfRows() < k) {
                string msg = "invalid input";
                classResult = msg.c_str();

                int sent_bytes = send(client_sock, classResult, strlen(classResult), 0);
                if (sent_bytes < 0) {
                    perror("error sending to client");
                    exit(1);
                }
                //reset the buffer:
                memset(buffer, 0, sizeof buffer);
            }

            Knn knnModel(v, k, distMetric, mappedData);
            classResult = knnModel.predict().c_str();
            int sent_bytes = send(client_sock, classResult, strlen(classResult), 0);
            if (sent_bytes < 0) {
                perror("error sending to client");
                exit(1);
            }
            //reset the buffer:
            memset(buffer, 0, sizeof buffer);

        } else {   //input not valid
            string msg = "invalid input";
            classResult = msg.c_str();

            int sent_bytes = send(client_sock, classResult, strlen(classResult), 0);
            if (sent_bytes < 0) {
                perror("error sending to client");
                exit(1);
            }
            //reset the buffer:
            memset(buffer, 0, sizeof buffer);
        }

    }

    close(sock);
    return 0;
}

