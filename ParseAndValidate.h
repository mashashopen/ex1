//
// Created by masha on 29/12/2022.
//
#include <string>
#include <vector>
#ifndef EX1_PARSEANDVALIDATE_H
#define EX1_PARSEANDVALIDATE_H


using namespace std;

class ParseAndValidate {

    string m_input;
    size_t m_idxOfDist;

public:
    ParseAndValidate(string input){
        m_input = input;
        m_idxOfDist = getIdxOfMetric();
    }

    int getK();
    vector<double> getVector();
    string getDistMetric();
    size_t getIdxOfMetric();

    bool stringVectorIsNotValid(string s);
    bool isNumber(const string &s);
    bool isValidMetric();

};





#endif //EX1_PARSEANDVALIDATE_H
