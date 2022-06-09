#include <iostream>
#include <math.h>

#define PI 3.14159265

using namespace std;

int main() {
	// ввод первоначальных данных
	double r, l, h;
	cout << "r = ";
	cin >> r;
	cout << "l =  ";
	cin >> l;
	cout << "h = ";
	cin >> h;

	// если уровень воды больше либо равна двум радиусам
	if (h >= 2 * r) {
		cout << "V = " << PI * pow(r, 2) * l;
	}
	// если уровень воды меньше либо равен 0
	else if (h <= 0 || r <= 0 || l <= 0) {
		cout << "V = 0";
	}
	// если уровень воды на середине
	else if (h == r) {
		cout << "V = " << PI * pow(r, 2) * l / 2;
	}
	// если уровень воды выше середины
	else if(h > r){
		double a = h - r;
		double b = sqrt((pow(r, 2) - pow(a, 2)));
		double u = 2 * asin(b / r);
		cout << "V = " << (((PI * pow(r, 2)) - (pow(r, 2) * (u - sin(u)))) * l) / 2;

	}
	// если уровень воды меньше радиуса
	else {
		double a = h - r;
		double b = sqrt((pow(r, 2) - pow(a, 2)));
		double u = 2 * asin(b / r);
		cout << "V = " << (pow(r, 2) * (u - sin(u))) * l / 2;
	}
	cout << endl;
	system("pause");
	return 0;
}