#pragma once
// ch11_07_mytime2.h -- Time class after operator overloading
#ifndef CH11_O7_MYTIME2_H_
#define CH11_O7_MYTIME2_H_

class Time
{
private:
	int hours;
	int minutes;
public:
	Time();
	Time(int h, int m = 0);
	void AddMin(int m);
	void AddHr(int h);
	void Reset(int h = 0, int m = 0);
	Time operator+(const Time& t) const;
	Time operator-(const Time& t) const;
	Time operator*(double n) const;
	void Show() const;
};
#endif