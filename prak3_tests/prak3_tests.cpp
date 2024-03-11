#include "pch.h"
#include "..\prak3\TempMeasurement.h"
#include "..\prak3\TempMeasurement.cpp"
#include "..\prak3\Validator.h"
#include "..\prak3\Validator.cpp"
#include "..\prak3\Income.h"
#include "CppUnitTest.h"
#include <sstream>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace prak3tests
{
	TEST_CLASS(prak3tests)
	{
	public:
		TempMeasurement tmeasure;
		vector<string> valid_test_strings = { "2023.12.15 Krasnoyarsk -27.5", "2015.10.21 Moskva -5",
		"2021.11.06 Rostov-na-Donu 20", "1999.05.29 Samara 20.6", "2005.08.10 Ufa 25.3",
		"2011.07.31 Krasnodar 27.8" };
		vector<string> invalid_test_strings = { "2022.13.05 Moskva 15",  "2022.06.25 Omsk abc"
		"2077.12.31 Chelyabinsk 40", "2022.11.15 Ufa -70", "2022.10.10 Krasnoyarsk 28a",
		"2022.07.11 Voronezh 30.55555",  "2024.02.30 Perm -28", "2023.02.29 Volgograd -30.5", 
			"2022.1.15 Ufa -70", "2022.06.5 Omsk abc", "0022.13.05 Moskva 15",  "022.10.10 Krasnoyarsk 28a",
		"2017.12.08 Chel1_yabinsk -30",  "aaaa.12.03 Perm -28" };
		vector<string> expected_strings = { " Date: 2023.12.15\n City: Krasnoyarsk\n Temperature: -27.5 °C Degrees \n\n",
			" Date: 2015.10.21\n City: Moskva\n Temperature: -5 °C Degrees \n\n",
			" Date: 2021.11.06\n City: Rostov-na-Donu\n Temperature: 20 °C Degrees \n\n",
			" Date: 1999.05.29\n City: Samara\n Temperature: 20.6 °C Degrees \n\n",
			" Date: 2005.08.10\n City: Ufa\n Temperature: 25.3 °C Degrees \n\n",
			" Date: 2011.07.31\n City: Krasnodar\n Temperature: 27.8 °C Degrees \n\n" };
		stringstream tests_string_stream;

		TEST_METHOD(printMeasurementTest)
		{
			string test_string = "2023.12.15 Krasnoyarsk -27.5";
			stringstream tests_string_stream;

			tmeasure.set_measurement(test_string);
			tmeasure.printIncomes(tests_string_stream);

			Assert::AreEqual(expected_strings.at(0), tests_string_stream.str());
			tmeasure.remove_measurements();
			tests_string_stream.str(string());
		}
		TEST_METHOD(removeMeasurements)
		{
			for (auto i : valid_test_strings)
				tmeasure.set_measurement(i);
			tmeasure.remove_measurements();
			tmeasure.printIncomes(tests_string_stream);
			Assert::AreEqual(string(), tests_string_stream.str());
			tests_string_stream.str(string());
		}
		TEST_METHOD(removeMeasurement)
		{
			tmeasure.set_measurement(valid_test_strings.at(0));
			tmeasure.set_measurement(valid_test_strings.at(1));
			tmeasure.set_measurement(valid_test_strings.at(2));
			tmeasure.remove_measure(1);
			tmeasure.printIncomes(tests_string_stream);
			Assert::AreEqual(expected_strings.at(0) + expected_strings.at(2), tests_string_stream.str());
			tests_string_stream.str(string());
		}
		TEST_METHOD(validMeasurement)
		{
			for (auto i : valid_test_strings)
				Assert::IsTrue(tmeasure.validator.is_valid(i));
		}
		TEST_METHOD(invalidMeasurement)
		{
			for (auto i : invalid_test_strings)
				Assert::IsFalse(tmeasure.validator.is_valid(i));
		}
		TEST_METHOD(setValidMeasurement)
		{
			for (auto i : valid_test_strings)
				tmeasure.set_measurement(i);
			const size_t length = valid_test_strings.size();
			for (size_t i = 0; i < length; i++) {
				tmeasure.printIncome(i, tests_string_stream);
				Assert::AreEqual(expected_strings.at(i), tests_string_stream.str());
				tests_string_stream.str(string());
			}
			tmeasure.remove_measurements();
		}
		TEST_METHOD(setInvalidMeasurement)
		{
			for (auto i : invalid_test_strings)
				tmeasure.set_measurement(i);
			const size_t length = invalid_test_strings.size();
			for (size_t i = 0; i < length; i++) {
				tmeasure.printIncome(i, tests_string_stream);
				Assert::AreEqual(string(), tests_string_stream.str());
				tests_string_stream.str(string());
			}
		}
		TEST_METHOD(setValidMeasurements)
		{
			stringstream expected_strings_stream;
			copy(expected_strings.begin(), expected_strings.end(), ostream_iterator<string>(expected_strings_stream));
			copy(valid_test_strings.begin(), valid_test_strings.end(), ostream_iterator<string>(tests_string_stream, "\n"));
			tmeasure.set_measurements(tests_string_stream);
			tests_string_stream.str(string());
			tmeasure.printIncomes(tests_string_stream);
			Assert::AreEqual(expected_strings_stream.str(), tests_string_stream.str());
			tests_string_stream.str(string());
		}
		TEST_METHOD(setInvalidMeasurements)
		{
			copy(invalid_test_strings.begin(), invalid_test_strings.end(), ostream_iterator<string>(tests_string_stream, "\n"));
			tmeasure.set_measurements(tests_string_stream);
			tests_string_stream.str(string());
			tmeasure.printIncomes(tests_string_stream);
			Assert::AreEqual(string(), tests_string_stream.str());
			tests_string_stream.str(string());
		}
		TEST_METHOD(traceDuplicates)
		{
			tmeasure.set_measurement(valid_test_strings.at(0));
			tmeasure.set_measurement(valid_test_strings.at(1));
			tmeasure.set_measurement(valid_test_strings.at(2));
			tmeasure.set_measurement(valid_test_strings.at(0));
			tmeasure.set_measurement(valid_test_strings.at(1));
			tmeasure.set_measurement(valid_test_strings.at(0));
			tmeasure.printIncomes(tests_string_stream);
			Assert::AreEqual(expected_strings.at(0) + expected_strings.at(1) + expected_strings.at(2), tests_string_stream.str());
			tmeasure.remove_measurements();
			tests_string_stream.str(string());
		}
	};
}
