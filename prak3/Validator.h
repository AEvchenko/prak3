#pragma once
#include <string>
#include <sstream>
#include <regex>
#include "Valids.h"

using namespace std;

class Validator {
private:

    Valids valids;
    bool is_valid_line(const string& str) const;
    void adjust_data(vector<string>& data) const;
    bool in_range(const int& value, const int& low, const int& high) const;
    bool is_leap_year(const int& year) const;
    bool is_valid_date(const string& str) const;
    bool is_valid_city(const string& str) const;

public:
    vector<string> split_data(const string& str, const char& delim) const;
    bool is_valid(const string& str) const;
};

