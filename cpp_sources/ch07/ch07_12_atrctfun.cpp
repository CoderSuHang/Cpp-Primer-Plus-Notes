// ch07_12_atrctfun.cpp -- functions with a structure argument
#include <iostream>
#include <cmath>

struct polar {
	double distance;
	double angle;
};

struct rect {
	double x;
	double y;
};

polar rect_to_polar(rect xypos);
void show_polar(polar dapos);

int main() {
	using namespace std;

	rect rplace;
	polar pplace;

	cout << "Enter the x and y values: ";
	while (cin >> rplace.x >> rplace.y) {
		pplace = rect_to_polar(rplace);
		show_polar(pplace);
		cout << "Next two numbers (q to quit): ";
	}
	cout << "Done.\n";

	return 0;
}

polar rect_to_polar(rect xypos) {
	using namespace std;
	polar answer;

	//数学库中的sqrt()使用水平和垂直坐标来计算距离:
	answer.distance =
		sqrt(xypos.x * xypos.x + xypos.y * xypos.y);
	//数学库中的atan2()函数可根据x和y的值计算角度:
	answer.angle = atan2(xypos.y, xypos.x);
	return answer;
}

void show_polar(polar dapos) {
	using namespace std;
	//弧度值乘以180/Π，约为57.29577951
	const double Rad_to_deg = 57.29577951;

	cout << "distance = " << dapos.distance;
	cout << ", angle = " << dapos.angle * Rad_to_deg;
	cout << " degrees\n";
}