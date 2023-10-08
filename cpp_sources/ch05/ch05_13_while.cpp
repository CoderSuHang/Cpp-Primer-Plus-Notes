/*// ch05_13_while.cpp -- introducing the while loop
#include <iostream>
const int ARSIZE = 20;
int main() {
	using namespace std;
	char name[ARSIZE];

	cout << "Your first name, please: ";
	cin >> name;
	cout << "Here is your name, verticalized and ASCIIized:\n";
	int i = 0;
	while (name[i] != '\0') {
		cout << name[i] << ": " << int(name[i]) << endl;
		i++;
	}

	return 0;
}*/