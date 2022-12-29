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
    bool m_isValidInput;

public:
    ParseAndValidate(string input){
        m_input = input;
        m_idxOfDist = getIdxOfMetric();
        m_isValidInput = true;
    }

    int getK();
    vector<double> getVector();
    string getDistMetric();
    size_t getIdxOfMetric();

    //need to make private:

    bool stringVectorIsValid(string s);
    bool isNumber(const string &s);
    bool isValidMetric();
    bool isValidInput();

};





#endif //EX1_PARSEANDVALIDATE_H
