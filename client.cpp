#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include <string>
#include <sstream>
#include "Distance.h"
#include "ParseAndValidate.h"

#include <bits/stdc++.h>

using namespace std;

/*
* this function check if part of the string is in valid ip type
*
* @param s the part to check
* @return true if part is valid and false otherwise
*/
bool validPart(char *s) {
    int n = strlen(s);
    if (n > 3)
        return false;
    for (int i = 0; i < n; ++i) {
        if ((s[i] >= '0' && s[i] <= '9') == false)
            return false;
    }
    string str(s);
    if (str.find('0') == 0 && n > 1)
        return false;
    stringstream y(str);
    int x;
    y >> x;
    return (x >= 0 && x <= 255);
}

/*
* this function validate ip address.
*
* @param ip_string the ip address to check.
* @return true if is valid and false otherwise.
*/
bool isValidIp(char *ip_string) {
    if (ip_string == NULL)
        return false;
    int num, i, dots = 0;
    int len = ::strlen(ip_string);
    int counter = 0;
    for (int j = 0; j < len; ++j) {
        if (ip_string[i] == '.')
            counter++;

    }
    if (counter != 3)
        return false;
    const char *DELIM;
    char *ptr = ::strtok(ip_string, DELIM);
    if (ptr == NULL)
        return false;
    while (ptr) {
        if (validPart(ptr)) {
            ptr = ::strtok(NULL, ".");
            if (ptr != NULL)
                ++dots;
        } else
            return false;
    }
    if (dots != 3) {
        return false;
    }
    return true;

}

/*
* command line args validation.
*
* @param argc, argv
* @return true if all args are valid and false otherwise.
*/
bool areValidArguments(int argc, char *argv[]) {
    /*argv:
    1. ip address
    2. port number
    */
    bool valid = true;

    //corrcet number of args:
    if (argc == 3) {
        //checking if second arg (port number) is correct range
        if (strtol(argv[2], NULL, 10) < 1024 || strtol(argv[2], NULL, 10) > 65535) {
            valid = false;
        }
        //checking if first arg (ip address) is correct range
        if (!isValidIp(argv[1])) {
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

int main(int argc, char *argv[]) {
    const char *ip_address = argv[1];
    const int port_no = stoi(argv[2]);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
        exit(1);
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
        string s = "";
        getline(cin, s);
        ParseAndValidate input(s);

        char const *data_addr = s.c_str();

        int data_len = strlen(data_addr);
        int sent_bytes = send(sock, data_addr, data_len, 0);

        if(s == "-1"){
            close(sock);
            exit(1);
        }

        if (sent_bytes < 0) {
            // error
        }
        string label;
        char buffer[4096] = {};
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