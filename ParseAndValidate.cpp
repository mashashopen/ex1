//
// Created by masha on 29/12/2022.
//

#include "ParseAndValidate.h"
#include "Distance.h"
#include <iostream>
#include <sstream>
#include <iterator>


size_t ParseAndValidate::getIdxOfMetric(){
    for (string disMetric: Distance::possibleMetrics()) {
        m_idxOfDist = m_input.find(disMetric);
        if (m_idxOfDist > 0 && m_idxOfDist < m_input.length()) { // found the index of the metric inside the input
            break;
        }
    }
    return m_idxOfDist;
}

int ParseAndValidate::getK(){
    // need to change the 1 value!!!!! still dont know how
    string subK = m_input.substr(m_idxOfDist + 4, 1); //dist metric is size of 3
    if(!isNumber(subK)){
        m_isValidInput = false;
        return -1;
    }
    else{
        return stoi(subK);
    }
}


vector<double> ParseAndValidate::getVector(){

    string subVector = m_input.substr(0, m_idxOfDist);

    if (!stringVectorIsValid(subVector)){
        m_isValidInput = false;
        vector<double> emptyVector;
        return emptyVector;
    }

    istringstream is(subVector);
    vector<double> v((istream_iterator<double>(is)), istream_iterator<double>());
    double x;

    while (is >> x) v.push_back(x);
    return v;
}


string ParseAndValidate::getDistMetric(){
    if(!isValidMetric()){
        m_isValidInput = false;
        string s;
        return s;
    }

    string distMetric = m_input.substr(m_idxOfDist, 3);
    return distMetric;
}

bool ParseAndValidate::stringVectorIsValid(string s) {
    // case 1: empty input
    if (s.size() == 0){
        m_isValidInput = false;
    }

    // case 2: dealing with chars
    for (int i = 0; i < s.size(); i++){
        if (isalpha(s[i])) {
            m_isValidInput = false;
        }
    }
    return m_isValidInput;
}

/*
* checks if string is actually a integer number.
*
* @param s,the string to check.
* @return true if it is integer, false otherwise.
*/
bool ParseAndValidate::isNumber(const string &s) {
    for (char const &ch: s) {
        if (std::isdigit(ch) == 0)
            return false;
    }
    return true;
}
bool ParseAndValidate::isValidMetric(){
    return (m_idxOfDist > 0 && m_idxOfDist < m_input.length());
}

bool ParseAndValidate::isValidInput(){
    return m_isValidInput;
}

