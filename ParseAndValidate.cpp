#include "ParseAndValidate.h"
#include "Distance.h"
#include <iostream>
#include <sstream>
#include <iterator>

/*
* this function return the index where distance metric is beginning.
*
* @return the index.
*/
size_t ParseAndValidate::getIdxOfMetric(){
    for (string disMetric: Distance::possibleMetrics()) {
        m_idxOfDist = m_input.find(disMetric);
        if (m_idxOfDist > 0 && m_idxOfDist < m_input.length()) { // found the index of the metric inside the input
            break;
        }
    }
    return m_idxOfDist;
}

/*
* this function return the input k (int) number.
*
* @return k (int) number.
*/
int ParseAndValidate::getK(){
    string subK = m_input.substr(m_idxOfDist + 4); //dist metric is size of 3
    if(!isNumber(subK)){
        m_isValidInput = false;
        return -1;
    }
    else{
        return stoi(subK);
    }
}

/*
* this function return the input vector .
*
* @return the vector .
*/
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

/*
* this function return the distance metric input.
*
* @return a string represent the distance metric.
*/
string ParseAndValidate::getDistMetric(){
    if(!isValidMetric()){
        m_isValidInput = false;
        string s;
        return s;
    }

    string distMetric = m_input.substr(m_idxOfDist, 3);
    return distMetric;
}

/*
* this function checks if the (input) vector is valid.
*
* @param s, string to check.
* @return true if is valid and false otherwise.
*/
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

/*
* this function checks if metric distance is valid.
*
* @return true if is valid and false otherwise.
*/
bool ParseAndValidate::isValidMetric(){
    return (m_idxOfDist > 0 && m_idxOfDist < m_input.length());
}

/*
* this function if the total input   is valid.
*
* @return true if is valid and false otherwise.
*/
bool ParseAndValidate::isValidInput(){
    return m_isValidInput;
}

