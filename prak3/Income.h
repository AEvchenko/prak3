#pragma once
#include <string>

using namespace std;

struct Income {
    struct Date {
        string year = "None";
        string month = "None";
        string day = "None";
    };
    Date date;
    string city = "None";
    double temperature = 0;
    int pos = 0;

    bool operator == (const Income& obj) const noexcept {
        return this->date.day == obj.date.day &&
            this->date.month == obj.date.month &&
            this->date.year == obj.date.year &&
            this->city == obj.city &&
            this->temperature == obj.temperature;
    }
};
