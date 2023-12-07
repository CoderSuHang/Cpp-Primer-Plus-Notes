#pragma once
// ch12_01_strngbad.h -- flawed string class definition
#include <iostream>
#ifndef CH12_01_STRNGBAD_H_
#define CH12_01_STRNGBAD_H_

class StringBad
{
private:
	char* str;
	int len;
	static int num_strings;
public:
	StringBad(const char* s);
	StringBad();
	~StringBad();
// friend function
	friend std::ostream& operator<<(std::ostream& os, const StringBad& st);
};
#endif