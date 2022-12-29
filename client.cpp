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

using namespace std;

bool vectorInputIsNotValid(string s) {
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
* checks if string is actully a integer number.
*
* @param s,the string to check.
* @return true if it is integer, false otherwise.
*/
bool isNumber(const string &s) {
    for (char const &ch: s) {
        if (std::isdigit(ch) == 0)
            return false;
    }
    return true;
}


string getInputFromUser() {
    string s;
    getline(cin, s);
    size_t found;

    for (string s1 :Distance::possibleMetrics()) {
        found = s.find(s1);
        if (found > 0 && found < sizeof(s)) {
            break;
        }
    }
    string subVector = s.substr(0, found);
    //vector validation:
    if (vectorInputIsNotValid(subVector)) {
        cout << "invalid input!";
        //how to return and get another input?
    }

    string disMetric = s.substr(found, 3);

    string subK = s.substr(found + 4);
    //k validation:
    if (!(isNumber(subK))) {
        cout << "invalid input!";
        //how to return and get another input?
    }

    return s;
}

int main(int argc, char *argv[]) {
    const char *ip_address = argv[1];
    const int port_no = stoi(argv[2]);

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    //string t = "1 2 3 4 MAN 3";     //this we will receive as input from user
    //char const *data_addr = t.c_str();

    string t = getInputFromUser();
    char const *data_addr = t.c_str();

    // forever loop to get input from user:


/*
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

    int data_len = strlen(data_addr);
    int sent_bytes = send(sock, data_addr, data_len, 0);

    if (sent_bytes < 0) {
        // error }
        char buffer[4096];
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(sock, buffer, expected_data_len, 0);
        if (read_bytes == 0) {
            // connection is closed
        } else if (read_bytes < 0) {
            // error
        } else {
            cout << buffer;
        }
        close(sock);

    }
    return 0;

    */
}

