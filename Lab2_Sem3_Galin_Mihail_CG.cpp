#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;

HWND console = GetConsoleWindow();
HDC hdc = GetDC(console);

COLORREF blue = RGB(0, 0, 255);
COLORREF green = RGB(0, 255, 0);
COLORREF red = RGB(255, 0, 0);
COLORREF white = RGB(255, 255, 255);

const int n = 50;

double getPt(double n1, double n2, double perc) {
	return n1 + ((n2 - n1) * perc);
}

class Point {
public:
	double x = 0, y = 0;

	Point() {
		x = 50 + rand() % 500;
		y = 50 + rand() % 500;
	}
};

int main()
{
	srand(unsigned(time(0)));
	vector<vector<Point>> points;

	while (true) {
		system("cls");
		points.clear();
		for (int i = n; i > 0; --i) {
			vector <Point> temp;
			for (int j = i; j > 0; --j) {
				Point tempPoint;
				temp.push_back(tempPoint);
			}
			points.push_back(temp);
		}

		for (auto& point : points[0]) {
			SetPixel(hdc, point.x, point.y, white);
		}

		for (double i = 0; i < 1; i += 0.00001)
		{
			for (int j = 0; j < points.size(); j++) {
				for (int k = 0; k < points[j].size() - 1; k++) {
					points[j + 1][k].x = getPt(points[j][k].x, points[j][k + 1].x, i);
					points[j + 1][k].y = getPt(points[j][k].y, points[j][k + 1].y, i);
				}
			}

			SetPixel(hdc, points[points.size() - 1][0].x, points[points.size() - 1][0].y, white);
		}
	}
	return 0;
}