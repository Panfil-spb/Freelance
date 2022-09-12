#include <iostream>
#include <time.h>
#include <random>
#include <locale>

using namespace std;

class Matr
{
public:
	double** matr;
	int size;
	Matr(int n);
	Matr operator+(Matr l);
	Matr operator*(Matr l);

};

Matr::Matr(int n)
{
	size = n;
	matr = new double* [size];
	for (int i = 0; i < size; i++) {
		matr[i] = new double[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			matr[i][j] = rand() % 25;
		}
	}
}


Matr Matr::operator+(Matr l) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			matr[i][j] += l.matr[i][j];
		}
	}
	return *this;
}

Matr Matr::operator*(Matr l) {
	double** m = new double* [size];
	for (int i = 0; i < size; i++) {
		m[i] = new double[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
		{
			m[i][j] = 0;
			for (int k = 0; k < size; k++)
				m[i][j] += matr[i][k] * l.matr[k][j];
		}
	}
		
	matr = m;
	return *this;
}

ostream& operator << (ostream& os, const Matr& a) {
	for (int i = 0; i < a.size; i++) {
		for (int j = 0; j < a.size; j++) {
			cout.width(5);
			os << a.matr[i][j];
		}
		cout << endl;
	}
	return os;
}

int main()
{
	setlocale(0, "");
	srand(time(NULL));
	Matr y(3), e(3);
	char c;
	while (true) {
		system("cls");
		cout << "1. +" << endl;
		cout << "2. *" << endl;
		cout << "0. Выход" << endl;
		cout << "Ваш выбор: ";
		cin >> c;
		switch (c)
		{
		case '1':
			system("cls");
			cout << y;
			cout << endl << "+" << endl;
			cout << e;
			cout << endl << "=" << endl;
			cout << (y + e);
			system("pause");
			break;
		case '2':
			system("cls");
			cout << y;
			cout << endl << "*" << endl;
			cout << e;
			cout << endl << "=" << endl;
			cout << (y * e);
			system("pause");
			break;
		case '0':
			system("cls");
			cout << "Завершение работы программы." << endl;
			system("pause");
			return 0;
		default:
			break;
		}
	}

}