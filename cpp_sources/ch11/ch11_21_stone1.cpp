// ch11_21_stone1.cpp -- user-defined conversions
// compole with stonewt.cpp
#include <iostream>
#include "ch11_19_stonewt1.h"

int main()
{
	using std::cout;
	Stonewt poppins(9, 2.8);
	double p_wt = poppins;
	cout << "Convert to double => ";
	cout << "Poppins: " << p_wt << " pounds.\n";
	cout << "Convert to int => ";
	cout << "Poppins: " << int(poppins) << " pounds.\n";

	return 0;
}