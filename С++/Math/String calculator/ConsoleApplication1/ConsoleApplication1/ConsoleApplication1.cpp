
#include <iostream>
#include <iomanip>
#define PI 3.14159265358979323

double number();
double factor();
double expr();
double brackets();

int main()
{
	double n;
	system("chcp 1251");
	system("cls");
	setlocale(LC_ALL, "Russian");
	std::cout << "Введите выражение: ";

	n = expr();

	std::cout << "Результат вычисления: " << std::setprecision(8) << n << std::endl;

	std::cin.get();
	return 0;
}

double number()
{
	double result = 0.0;
	double k = 10.0;
	int sign = 1;
	char c;

	c = std::cin.get();

	while (c == ' ')
		c = std::cin.get();

	if (c == '-')
		sign = -1;
	else
		std::cin.putback(c);

	while (true)
	{
		c = std::cin.get();

		while (c == ' ')
			c = std::cin.get();

		if (c >= '0' && c <= '9')
			result = result * 10.0 + (c - '0');
		else
		{
			std::cin.putback(c);
			break;
		}
	}

	c = std::cin.get();

	if (c == '.')
	{
		while (true)
		{
			c = std::cin.get();

			if (c >= '0' && c <= '9')
			{
				result += (c - '0') / k;
				k *= 10.0;
			}
			else
			{
				std::cin.putback(c);
				break;
			}
		}
	}
	else
		std::cin.putback(c);

	return sign * result;
}

double factor()
{
	double result = brackets();
	double temp;
	char c;

	while (true)
	{
		c = std::cin.get();

		while (c == ' ')
			c = std::cin.get();

		switch (c)
		{
		case 'l':
			c = std::cin.get();
			if (c == 'n') {
				temp = brackets();
				if (temp == 0.0)
				{
					std::cout << "Логарифм от 0 нельзя взять!" << std::endl;
					exit(-1);
				}
				else if (temp < 0.0)
				{
					std::cout << "Нельзя взять ln от отрицательного числа!" << std::endl;
					exit(-1);
				}
				result = log(temp);
			}
			else {
				std::cout << "Неверное написание функции!" << std::endl;
				exit(-1);
			}
			break;
		case 't':
			c = std::cin.get();
			if (c == 'g') {
				temp = brackets();
				
				while (temp > (2*180)) temp -= (2*180);
				if (temp == 90 || temp == 270)
				{
					std::cout << "Тангенса 90 или 270 градусов нельзя получить!" << std::endl;
					exit(-1);
				}
				temp = temp * PI / 180;
				result = tan(temp);
				break;
			}
			else {
				std::cout << "Неверное написание функции!" << std::endl;
				exit(-1);
			}
			break;
		case 's':
			c = std::cin.get();
			if (c == 'i') {
				c = std::cin.get();
				if (c == 'n') {
					temp = brackets();
					while (temp > (2 * 180)) temp -= (2 * 180);
					temp = temp * PI / 180;
					result = sin(temp);
					break;
				}
				else {
					std::cout << "Неверное написание функции!" << std::endl;
					exit(-1);
				}
			}
			else if (c == 'q') {
				c = std::cin.get();
				if (c == 'r') {
					c = std::cin.get();
					if (c == 't') {
						temp = brackets();
						if (temp < 0) {
							std::cout << "Нельзя взять корень от отрицательного числа!" << std::endl;
							exit(-1);
						}
						result = sqrt(temp);
						break;
					}
					else {
						std::cout << "Неверное написание функции!" << std::endl;
						exit(-1);
					}
				}
				else {
					std::cout << "Неверное написание функции!" << std::endl;
					exit(-1);
				}
			}
			else {
				std::cout << "Неверное написание функции!" << std::endl;
				exit(-1);
			}
			break;
		case 'c':
			c = std::cin.get();
			if (c == 'o') {
				c = std::cin.get();
				if (c == 's') {
					temp = brackets();
					while (temp > (2 * 180)) temp -= (2 * 180);
					temp = temp * PI / 180;
					result = cos(temp);
					break;
				}
				else{
					std::cout << "Неверное написание функции!" << std::endl;
					exit(-1);
				}
			}
			else {
				std::cout << "Неверное написание функции!" << std::endl;
				exit(-1);
			}
			break;
		case '*':
			result *= brackets();
			break;
		case '/':
			temp = brackets();

			if (temp == 0.0)
			{
				std::cout << "Деление на нуль!" << std::endl;
				exit(-1);
			}

			result /= temp;
			break;
		case '^':
			temp = brackets();
			if (result == 0 && temp < 0) {
				std::cout << "Деление на нуль!" << std::endl;
				exit(-1);
			}
			if (temp - int(temp) != 0 && result < 0) {
				std::cout << "Нельзя брать корень от отрицательного числа!" << std::endl;
				exit(-1);
			}

			result = pow(result, temp);
			break;
		default:
			if ((int(tolower(c)) >= 97 && int(tolower(c)) <= 122) || (int(tolower(c)) >= -32 && int(tolower(c)) <= -1)) {
				std::cout << "Неверное написание функции!" << std::endl;
				exit(-1);
			}
			std::cin.putback(c);
			return result;
		}
	}
}

double expr()
{
	double result = factor();
	char c;

	while (true)
	{
		c = std::cin.get();

		while (c == ' ')
			c = std::cin.get();

		switch (c)
		{
		case '+':
			result += factor();
			break;
		case '-':
			result -= factor();
			break;
		default:
			if ((int(tolower(c)) >= 97 && int(tolower(c)) <= 122) || (int(tolower(c)) >= -32 && int(tolower(c)) <= -1)) {
				std::cout << "Неверное написание функции!" << std::endl;
				exit(-1);
			}
			std::cin.putback(c);
			return result;
		}
	}
}

double brackets()
{
	double result;
	int sign = 1;
	char c;

	c = std::cin.get();

	while (c == ' ')
		c = std::cin.get();

	if (c == '-')
	{
		sign = -1;
		c = std::cin.get();
	}

	while (c == ' ')
		c = std::cin.get();

	if (c == '(')
	{
		result = sign * expr();

		c = std::cin.get();

		if (c != ')')
		{
			std::cout << "Неверная расстановка скобок!" << std::endl;
			exit(-1);
		}
		std::cin.putback(c);
		return result;
	}
	else
	{
		std::cin.putback(c);

		return sign * number();
	}
}