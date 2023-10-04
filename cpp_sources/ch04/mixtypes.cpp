/*
// mixtypes.cpp -- some type combinations
#include <iostream>

struct antarctica_years_end {
	int year;
};

int main() {
	antarctica_years_end s01, s02, s03;
	s01.year = 1998;
	antarctica_years_end* pa = &s02;
	pa->year = 1999;
	//trio是一个数组，trio[0]是一个结构，而trio[0].year是该结构的一个成员
	antarctica_years_end trio[3];
	trio[0].year = 2003;
	//数组名是一个指针，因此可以使用间接陈冠符号：
	std::cout << trio->year << std::endl;
	//定义一个指针数组，arp[1]等价于&s02，即指向s02的指针
	const antarctica_years_end* arp[3] = {&s01, &s02, &s03};
	std::cout << arp[1]->year << std::endl;
	//arp是指针数组的数组名，代表第一个元素的地址
	const antarctica_years_end** ppa = arp;
	auto ppd = arp;
	//ppa=arp说明ppa指向了第一元素，第一个元素是s01的结构指针&s01
	//因此ppa是指向结构指针的指针，那么*ppa等价于第一个元素&s01
	std::cout << (*ppa)->year << std::endl;
	std::cout << (*(ppd+1))->year << std::endl;

	return 0;
}
*/