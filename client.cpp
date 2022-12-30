#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include <vector>
#include <string>
#include <iterator>
#include <sstream>
#include "Distance.h"
#include "ParseAndValidate.h"

using namespace std;

/*
* checks if input (vector) is not valid.
*
* @param s, string represent future vector.
* @return true if is not valid, false otherwise.
*/
bool inputIsNotValid(string s) {
    // case 1: empty input
    if (s.size() == 0) {

        return true;
    }

    // case 2: dealing with chars
    for (int i = 0; i < s.size(); i++) {
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

    if (inputIsNotValid(s)) {
        cout << "invalid input!";
        exit(1);
    }

    istringstream is(s);
    vector<double> v((istream_iterator<double>(is)), istream_iterator<double>());
    double x;
}

int main(int argc, char *argv[]) {
    const char *ip_address = argv[1];
    const int port_no = stoi(argv[2]);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);

    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }

    while (true) {
        string s;

        //while loop to get another input in case of invalid input:
        while (true) {
            getline(cin, s);
            ParseAndValidate input(s);

            if (s == "-1") {
                close(sock);
                exit(1);
            } else break;
        }

        char const *data_addr = s.c_str();

        int data_len = strlen(data_addr);
        int sent_bytes = send(sock, data_addr, data_len, 0);

        if (sent_bytes < 0) {
            // error
        }
        string label;
        char buffer[4096];
        int expected_data_len = sizeof(buffer);


        int read_bytes = recv(sock, buffer, expected_data_len, 0);

        if (read_bytes == 0) {
            // connection is closed
        } else if (read_bytes < 0) {
            cout << "error";
        } else {
            while (read_bytes == expected_data_len) {
                // Read more data from the socket into the buffer
                read_bytes = recv(sock, buffer, expected_data_len, 0);

                // Check for errors or end of data
                if (read_bytes == 0) {
                    // The other side of the connection has closed the socket
                    break;
                } else if (read_bytes < 0) {
                    // An error occurred
                    // TODO: handle the error
                    break;
                }
            }


            //print the predicted class of the vector:
            //convert array to string
            cout << buffer << endl;
        }
    }
}