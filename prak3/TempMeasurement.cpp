#include "TempMeasurement.h"

void TempMeasurement::set_measurement(const string& line) {
    if (validator.is_valid(line))
    {
        Income obj = parseIncome(line);
        if (find(this->data.begin(), this->data.end(), obj) == this->data.end()) {
            if (this->data.size())
                obj.pos = this->data.back().pos + 1;
            this->data.push_back(obj);
        }
    }
}

void TempMeasurement::set_measurements(const vector<Income>& objects) {
    for (const auto i : objects) {
        if (find(this->data.begin(), this->data.end(), i) == this->data.end())
            this->data.push_back(i);
    }
}

vector<string> TempMeasurement::readLinesFromFile(istream& file){
    vector<string> lines;
    string line;
    while (getline(file, line)) {
         if (validator.is_valid(line))
            lines.push_back(line);
    }
    return lines;
}

Income TempMeasurement::parseIncome(const string& line) const{
    Income obj;
    vector<string> fields = validator.split_data(line, ' ');
    vector<string> date = validator.split_data(fields[0], '.');
    obj.date.year = date[0];
    obj.date.month = date[1];
    obj.date.day = date[2];
    obj.city = fields[1];
    obj.temperature = stod(fields[2]);
    return obj;
}

vector<Income> TempMeasurement::parseIncomes(const vector<string>& lines) const{
    vector<Income> objects;
    for (const auto line : lines) {
        Income obj = parseIncome(line);
        objects.push_back(obj);
    }
    return objects;
}

void TempMeasurement::set_measurements(istream& file){
    vector<string> lines = readLinesFromFile(file);
    if (lines.empty())
        return;
    vector<Income> objects = parseIncomes(lines);
    set_measurements(objects);
    set_positions();
}

void TempMeasurement::adjust_positions(const int& pos) {
    for (auto i = this->data.begin() + pos; i != this->data.end(); i++)
        i->pos--;
}

void TempMeasurement::set_positions() {
    const size_t size = this->data.size();
    for (size_t i = 0; i < size; i++)
    {
        this->data[i].pos = i;
    }
}

void TempMeasurement::remove_measure(const int& pos) {
    const auto size = this->data.size();
    if (pos > size || !size)
        return;
    this->data.erase(data.begin() + pos);
    adjust_positions(pos);
}

void TempMeasurement::remove_measurements() {
    this->data.clear();
}

int TempMeasurement::get_pos(const string& line) const {
    if (validator.is_valid(line)){
        Income obj = parseIncome(line);
        return find(this->data.begin(), this->data.end(), obj)->pos;
    }
    return -1;
}

void TempMeasurement::printIncome(const int& pos, ostream& out) const {
    const auto size = this->data.size();
    if (pos > size || !size)
        return;
    const Income obj = this->data[pos];

    out << " Date: " << obj.date.year << '.' << obj.date.month << '.' << obj.date.day << '\n';
    out << " City: " << obj.city << '\n';
    out << " Temperature: " << obj.temperature << " °C Degrees " << '\n';
    out << '\n';
}

void TempMeasurement::printIncomes(ostream& out) const{
    out.clear();
    for (const Income obj : this->data) {
        printIncome(obj.pos, out);
    }
}