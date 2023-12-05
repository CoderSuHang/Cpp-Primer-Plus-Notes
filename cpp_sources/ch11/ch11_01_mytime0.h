#pragma once
// ch11_01_mytime0.h -- Time class before operator overloading
#ifndef CH11_O1_MYTIME0_H_
#define CH11_O1_MYTIME0_H_

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
	Time Sum(const Time& t) const;
	void Show() const;
};
#endif