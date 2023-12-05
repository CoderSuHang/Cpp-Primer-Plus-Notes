// ch11_09_usetime2.cpp -- using the first draft of the Time class
// compile usetime2.cpp and mytime2.cpp together

#include <iostream>
#include "ch11_07_mytime2.h"

int main()
{
	using std::cout;
	using std::endl;
	Time weeding(4, 35);
	Time waxing(2, 47);
	Time total;
	Time diff;
	Time adjusted;

	cout << "weeding time = ";
	weeding.Show();
	cout << endl;

	cout << "waxing time = ";
	waxing.Show();
	cout << endl;

	cout << "total work time = ";
	total = weeding + waxing;
	total.Show();
	cout << endl;

	diff = weeding - waxing;
	cout << "weeding time - waxing time = ";
	diff.Show();
	cout << endl;

	adjusted = total * 1.5;
	cout << "adjusted work time = ";
	adjusted.Show();
	cout << endl;

	return 0;
}