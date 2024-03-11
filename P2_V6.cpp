
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Date {
    int year;
    int month;
    int day;
};

struct Income {
    Date date;
    string city;
    double temperature;
};

vector<string> readLinesFromFile(const string& filename) {
    vector<string> lines;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Файл нельзя открыть!!!" << endl;
        return lines;
    }

    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();
    return lines;
}

Income parseIncome(const string& line) {
    Income obj;
    istringstream iss(line);

    char dot;
    iss >> obj.date.year >> dot >> obj.date.month >> dot >> obj.date.day;
    iss >> obj.city >> obj.temperature;

    return obj;
}

void printIncome(const Income& obj) {
    cout << " Date: " << obj.date.year << "." << obj.date.month << "." << obj.date.day << endl;
    cout << " City: " << obj.city << endl;
    cout << " Temperature: " << obj.temperature << " °C Degrees " << endl;
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "ru");

    vector<Income> objects;
    vector<string> lines = readLinesFromFile("Temper.txt");

    for (const auto& line : lines) {
        Income obj = parseIncome(line);
        objects.push_back(obj);
    }

    for (const Income& obj : objects) {
        printIncome(obj);
    }

    return 0;
}
