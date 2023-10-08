/*// ch05_14_waiting.cpp -- using clock() in a time-delay loop
#include <iostream>
#include <ctime>

int main() {
	using namespace std;
	cout << "Enter the delay time, in seconds: ";
	float secs;
	cin >> secs;
	clock_t delay = secs * CLOCKS_PER_SEC;
	cout << "starting\n";
	clock_t start = clock();
	while (clock() - start < delay)
		;
	cout << "done\n";

	return 0;
}*/