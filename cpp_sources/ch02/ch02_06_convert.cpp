// convert.cpp -- converts stone to pounds
#include <iostream>
int stoneolb(int);

int main()
{
	using namespace std;
	
	int stone;
	cout << "Enter the weight in stone: ";
	cin >> stone;
	int pounds = stoneolb(stone);
	cout << stone << " stone = ";
	cout << pounds << " pounds" << endl;
	return 0;
}

int stoneolb(int sts)
{
	return 14 * sts;
}
