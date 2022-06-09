#include <locale.h>
#include <iostream>
#define BITSIZE 8
using namespace std;

class BitNum
{
public:
	int bits[BITSIZE];
	bool valid;
	bool sign;

	BitNum(int num) {
		if (num >= pow(2, BITSIZE) || num <= -pow(2, BITSIZE - 1)) {
			cout << "Число " << num << " перепоняет массив!" << endl;
			for (int i = 0; i < BITSIZE; i++) bits[i] = 0;
			valid = false;
		}
		else {
			// если число положительное 
			if (num >= 0) {
				int n = num;
				for (int i = BITSIZE - 1; i >= 0; i--) {
					bits[i] = n % 2;
					n /= 2;
				}
				valid = true;
				sign = true;
			}
			// если отрицательное сразу переводим в обратную форму
			else {
				int n = -num;
				for (int i = BITSIZE - 1; i > 0; i--) {
					bits[i] = (n + 1) % 2;
					n /= 2;
				}
				bits[0] = 1;
				valid = true;
				sign = false;

				Plus(BitNum(1));
			}
		}

	}

	void Plus(BitNum n) {
		for (int i = BITSIZE - 1; i >= 0; i--) {
			if (n.bits[i] == 0) continue;
			else if (bits[i] == 0) {
				bits[i] = n.bits[i];
				continue;
			}
			else {
				bits[i] = 0;
				for (int j = i - 1; j >= 0; j--) {
					bits[j] = (bits[j] + 1) % 2;
					if (bits[j] == 1) break;

				}
			}
		}
		if (sign && n.sign) sign = true;
		else if (!sign && !n.sign) sign = false;
		else if ((!sign && n.sign) && (abs(To10()) > abs(n.To10()))) sign = false;
		else if ((!sign && n.sign) && (abs(To10()) < abs(n.To10()))) sign = true;
		else if ((sign && !n.sign) && (abs(To10()) > abs(n.To10()))) sign = true;
		else if ((sign && !n.sign) && (abs(To10()) < abs(n.To10()))) sign = false;
	}

	void PrintNum() {
		for (int i = 0; i < BITSIZE; i++) cout << bits[i];
	}

	int To10() {
		int res = 0;
		int Buf[BITSIZE];
		if (sign) for (int i = 0; i < BITSIZE; i++) res += bits[i] * pow(2, BITSIZE - 1 - i);
		else {
			BitNum n = BitNum(0);
			for (int i = 0; i < BITSIZE; i++) n.bits[i] = (bits[i] + 1) % 2;
			n.Plus(1);	
			for (int i = 0; i < BITSIZE; i++) res += n.bits[i] * pow(2, BITSIZE - 1 - i);
			res *= -1;
		}
		return res;
	}

	void Mult(BitNum n) {
		int Res[BITSIZE], Buf[BITSIZE];
		for (int i = 0; i < BITSIZE; i++) {
			Res[i] = 0;
			Buf[i] = 0;
		}
		for (int i = 0; i < BITSIZE; i++) {
			if (n.bits[BITSIZE - i - 1] == 0) continue;
			else {
				for (int j = 0; j < BITSIZE; j++) Buf[j] = 0;
				int k = BITSIZE - 1;
				for (int j = BITSIZE - i - 1; j >= 0; j--) {
					Buf[j] = bits[k];
					k--;
				}

				for (int j = BITSIZE - 1; j >= 0; j--) {
					if (Buf[j] == 0) continue;
					else if (Res[j] == 0) {
						Res[j] = Buf[j];
						continue;
					}
					else {
						Res[j] = 0;
						for (int l = j - 1; l >= 0; l--) {
							Res[l] = (Res[l] + 1) % 2;
							if (Res[l] == 1) break;

						}
					}
				}
			}
		}
		for (int i = 0; i < BITSIZE; i++) bits[i] = Res[i];

	}
private:

};

void menu() {
	cout << "1. Сложение" << endl;
	cout << "2. Вычитание" << endl;
	cout << "3. Умножение" << endl;
	cout << "0. Выход" << endl;
	cout << "Ваш выбор: ";
}

int main()
{
	setlocale(0, "");
	int num1, num2;
	char c;
	cout << "Первое число: ";
	cin >> num1;
	cout << "Второе число: ";
	cin >> num2;
	BitNum n1 = BitNum(num1), n2 = BitNum(num2), n3 = BitNum(0);

	
	if (!n1.valid || !n2.valid) {
		cout << "Не валидные числа!" << endl;
		system("pause");
		return 1;
	}

	while (true) {
		system("cls");
		menu();
		cin >> c;
		n1 = BitNum(num1);
		n2 = BitNum(num2);
		switch (c)
		{
		case '0':
			return 0;
		case '1':
			if (num1 + num2 >= pow(2, BITSIZE) || num1 + num2 <= -pow(2, BITSIZE - 1))
			{
				cout << "Переполнение массива!" << endl;
				system("pause");
				break;
			}
			n1 = BitNum(num1);
			n2 = BitNum(num2);
			n3 = BitNum(num1);
			n1.PrintNum();
			cout << " + ";
			n2.PrintNum();
			cout << " = ";
			n1.Plus(n2);
			n1.PrintNum();

			cout << endl << n3.To10() << " + " << n2.To10() << " = " << n2.To10() << endl;
			system("pause");
			break;
		case '2':
			if (num1 - num2 >= pow(2, BITSIZE) || num1 - num2 <= -pow(2, BITSIZE - 1))
			{
				cout << "Переполнение массива!" << endl;
				system("pause");
				break;
			}
			n1 = BitNum(num1);
			n2 = BitNum(-num2);
			n3 = BitNum(num1);

			n1.PrintNum();
			cout << " + ";
			n2.PrintNum();
			cout << " = ";
			n1.Plus(n2);
			n1.PrintNum();

			cout << endl << n3.To10() << " - " << n2.To10() * (-1) << " = " << n1.To10() << endl;
			system("pause");
			break;
		case '3':
			if (num1 * num2 >= pow(2, BITSIZE) || num1 * num2 <= -pow(2, BITSIZE - 1))
			{
				cout << "Переполнение массива!" << endl;
				system("pause");
				break;
			}

			n1 = BitNum(num1);
			n2 = BitNum(num2);
			n3 = BitNum(num1);

			n1.PrintNum();
			cout << " * ";
			n2.PrintNum();
			cout << " = ";
			n1.Mult(n2);
			n1.PrintNum();
			cout << endl << n3.To10() << " * " << n2.To10() << " = " << n1.To10() << endl;
			system("pause");
			break;
		default:
			break;
		}
	}
	
}
