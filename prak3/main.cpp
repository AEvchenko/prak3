#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <iostream>
#include "Valids.h"

using namespace std;

int main() {
	Valids valids;
	//multimap <char, string> foundElements, foundelements1;
	//char key = 'K';
	//auto begin1 = std::chrono::steady_clock::now();
	//copy_if(valids.cities.begin(), valids.cities.end(), inserter(foundElements, foundElements.begin()), [key](auto& city) {return city.first == key; });
	//auto end1 = std::chrono::steady_clock::now();
	//auto elapsed_ms1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - begin1);
	//cout << elapsed_ms1.count() <<'\n';
	//auto begin2 = std::chrono::steady_clock::now();
	//for (auto i : valids.cities)
	//	if (i.first == key)
	//		foundelements1.insert(i);
	//auto end2 = std::chrono::steady_clock::now();
	//auto elapsed_ms2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2);
	//cout << elapsed_ms2.count();
	//auto cc = valids.cities.equal_range(key);
	char key = 'K';
	vector< string> foundElements;
	//copy_if(valids.cities.begin(), valids.cities.end(), back_inserter(foundElements), [key](auto& city) {return city.first == key; });
	//return find(foundElements.begin(), foundElements.end(), str) != foundElements.end();
	transform(valids.cities.begin(), valids.cities.end(), back_inserter(foundElements), [key](auto& val) {if (val.first == key) return val.second; else return string(); });
	return 0;
}