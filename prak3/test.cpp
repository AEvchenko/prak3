#include <iostream>
#include "TempMeasurement.h"

int main(){
	TempMeasurement t;
	t.set_measurement("2023.06.27 Moskva 28.5");
	t.printIncomes(std::cout);
	t.Measure("Temper.txt");
	t.printIncomes(std::cout);
	return 0;
}