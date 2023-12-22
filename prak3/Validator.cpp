#include "Validator.h"

bool Validator::is_valid_line(const string& str) const {
    string exp = "^[1-2]\\d{3}\\.\\d{2}\\.\\d{2}"
        " (([A-Z][a-z]{2,})[- ]?([a-z]{2,}-[A-Z][a-z]{2,})?([A-Z][a-z]{2,})?)"
        " (\\d{1,2}(\\.\\d{1,2})?$)|(\\-[1-9][0-9]{0,1}(\\.\\d{1,2})?$)";
    regex regular(exp);
    cmatch res;
    if (regex_match(str.c_str(), res, regular))
        return true;
    return false;
}

vector<string> Validator::split_data(const string& str, const char& delim) const {
    istringstream strs(str);
    vector<string> fields;
    string field;
    while (getline(strs, field, delim)) {
        fields.push_back(field);
    }
    return fields;
}

void Validator::adjust_data(vector<string>& data) const {
    if (data.size() == 3)
        return;
    data[1] += (" " + data[2]);
    swap(data[2], data[3]);
    data.erase(data.begin() + 3);
}

bool Validator::in_range(const int& value, const int& low, const int& high) const {
    return value >= low && value <= high;
}

bool Validator::is_leap_year(const int& year) const {
    return (year % 4 == 0) || (year % 400 == 0);
}

bool Validator::is_valid_date(const string& str) const {
    vector<int> date;
    vector<string> date_str = split_data(str, '.');
    transform(date_str.begin(), date_str.end(), back_inserter(date), [](string& val) { return stoi(val); });
    if (in_range(date[0], valids.year[0], valids.year[1]) &&
        in_range(date[1], valids.month[0], valids.month[1]) &&
        in_range(date[2], valids.day[0], valids.day[1])) {
        bool is_leap = is_leap_year(date[0]);
        bool is_feb = date[1] == 2;
        if (is_leap && is_feb && (!in_range(date[2], 1, 29)))
            return false;
        if (!is_leap && is_feb && (!in_range(date[2], 1, 28)))
            return false;
        return true;
    }
    return false;
}

bool Validator::is_valid_city(const string& str) const {
    return find(valids.cities.begin(), valids.cities.end(), str) != valids.cities.end();
}

bool Validator::is_valid(const string& str) const {
    if (is_valid_line(str)) {
        vector<string> fields = split_data(str, ' ');
        adjust_data(fields);
        return is_valid_date(fields[0]) && is_valid_city(fields[1]) &&
            in_range(stoi(fields[2]), valids.temperature[0], valids.temperature[1]);
    }
    return false;
}
