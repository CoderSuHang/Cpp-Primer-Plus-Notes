#pragma once
// ch11_16_stonewt.h -- definition for the Stonewt class
#ifndef CH11_16_STONEWT_H_
#define CH11_16_STONEWT_H_

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
};
#endif