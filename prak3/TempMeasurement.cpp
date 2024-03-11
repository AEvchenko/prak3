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
    vector<string> date = validator.split_data(fields.at(0), '.');
    obj.date.year = date.at(0);
    obj.date.month = date.at(1);
    obj.date.day = date.at(2);
    obj.city = fields.at(1);
    obj.temperature = stod(fields.at(2));
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

void TempMeasurement::adjust_positions(const int& pos) noexcept {
    for (auto i = this->data.begin() + pos; i != this->data.end(); i++)
        i->pos--;
}

void TempMeasurement::set_positions() {
    const size_t size = this->data.size();
    for (size_t i = 0; i < size; i++)
    {
        this->data.at(i).pos = i;
    }
}

void TempMeasurement::remove_measure(const int& pos) noexcept {
    const auto size = this->data.size();
    if (pos > size || !size)
        return;
    this->data.erase(this->data.begin() + pos);
    adjust_positions(pos);
}

void TempMeasurement::remove_measurements() noexcept {
    this->data.clear();
}

int TempMeasurement::get_pos(const string& line) const {
    if (validator.is_valid(line)){
        Income obj = parseIncome(line);
        auto it = find(this->data.begin(), this->data.end(), obj);
        if (it != this->data.end()) {
            return it->pos;
        }
        else {
            // Обработка случая, когда объект не найден.
            return -1;  // или другое значение, которое подходит для вашей логики.
        }

    }
    return -1;
}

void TempMeasurement::printIncome(const int& pos, ostream& out) const {
    const auto size = this->data.size();
    if (pos > size || !size)
        return;
    const Income obj = this->data.at(pos);

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