#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Income.h"
#include "Validator.h"

using namespace std;


class TempMeasurement
{
private:
    vector<Income> data;
    vector<string> readLinesFromFile(istream& file);
    vector<Income> parseIncomes(const vector<string>& lines) const;
    Income parseIncome(const string& line) const;
    void set_measurements(const vector<Income>& objects);
    void adjust_positions(const int& pos);
    void set_positions();
public:
    void set_measurement(const string& line);
    Validator validator;
    void set_measurements(istream& file);
    void remove_measure(const int& pos);
    void remove_measurements();
    int get_pos(const string& line) const;
    void printIncome(const int& pos, ostream& out) const;
    void printIncomes(ostream& out) const;
};

