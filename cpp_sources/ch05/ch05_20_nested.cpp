/*// nested.cpp -- nested loops and 2-D array
#include <iostream>
const int Cities = 5;
const int Years = 4;

int main() {
	using namespace std;
	const char* cities[Cities] = {
		"Gribble City",
		"Gribbletwon",
		"New Gribble",
		"San Gribble",
		"Gribble Vista"
	};

	int maxtemps[Years][Cities] = {
		{96, 100, 87, 63, 84},
		{101, 102, 88, 83, 84},
		{76, 100, 53, 85, 84},
		{96, 180, 89, 93, 87}
	};

	cout << "Maximum temperatures for 2008 - 2011\n\n";
	for (int city = 0; city < Cities; ++city) {
		cout << cities[city] << ":\t";
		for (int year = 0; year < Years; ++year)
			cout << maxtemps[year][city] << "\t";
		cout << endl;
	}

	return 0;
}*/