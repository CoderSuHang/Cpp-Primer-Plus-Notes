#pragma once

// ch11_04_mytime1.h -- Time class before operator overloading
#ifndef CH11_O4_MYTIME1_H_
#define CH11_O4_MYTIME1_H_

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
	void Show() const;
};
#endif