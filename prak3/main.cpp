#include "TempMeasurement.h"
#include <vector>
#include <string>
#include <fstream>

int main() {
	TempMeasurement tmeasure;
	vector<string> valid_test_strings = { "2023.12.15 Krasnoyarsk -27.5", "2015.10.21 Moskva -5",
			"2021.11.06 Rostov-na-Donu 20", "1999.05.29 Samara 20.6", "2005.08.10 Ufa 25.3",
			"2011.07.31 Krasnodar 27.8" };
	vector<string> expected_strings = { " Date: 2023.12.15\n City: Krasnoyarsk\n Temperature: -27.5 °C Degrees \n\n",
		" Date: 2015.10.21\n City: Moskva\n Temperature: -5 °C Degrees \n\n",
		" Date: 2021.11.06\n City: Rostov-na-Donu\n Temperature: 20 °C Degrees \n\n",
		" Date: 1999.05.29\n City: Samara\n Temperature: 20.6 °C Degrees \n\n",
		" Date: 2005.08.10\n City: Ufa\n Temperature: 25.3 °C Degrees \n\n",
		" Date: 2011.07.31\n City: Krasnodar\n Temperature: 27.8 °C Degrees \n\n" };

	stringstream expected_strings_stream, tests_string_stream;
	copy(expected_strings.begin(), expected_strings.end(), ostream_iterator<string>(expected_strings_stream));
	copy(valid_test_strings.begin(), valid_test_strings.end(), ostream_iterator<string>(tests_string_stream, "\n"));
	tmeasure.set_measurements(tests_string_stream);
	tests_string_stream.str(string());
	tmeasure.printIncomes(tests_string_stream);
	string s1 = tests_string_stream.str(), s2 = expected_strings_stream.str();
	std::cout << (s1 == s2);
	tests_string_stream.str(string());
	return 0;
}