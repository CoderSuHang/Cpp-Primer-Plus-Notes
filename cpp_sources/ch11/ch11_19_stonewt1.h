#pragma once

// ch11_19_stonewt1.h -- revised definition for the Stonewt class
#ifndef CH11_19_STONEWT1_H_
#define CH11_19_STONEWT1_H_

class Stonewt
{
private:
	enum { Lbs_per_stn = 14 };
	int stone;
	double pds_left;
	double pounds;
public:
	Stonewt(double lbs);
	Stonewt(int stn, double lbs);
	Stonewt();
	~Stonewt();
	void show_lbs() const;
	void show_stn() const;
// conversion functions
	operator int() const;
	operator double() const;
};
#endif