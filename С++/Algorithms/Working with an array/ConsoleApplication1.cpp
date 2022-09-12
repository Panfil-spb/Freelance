#include <iostream>
#include <cstdlib>
#include <locale>

using namespace std;

void menu()
{
	system("cls");
	cout << "1. Ввести массив" << endl;
	cout << "2. Вывести массив" << endl;
	cout << "3. Отсортировать массив" << endl;
	cout << "4. Добавить элементы" << endl;
	cout << "5. Вывести максимальный элемент" << endl;
	cout << "6. Вывести сумму элементов" << endl;
	cout << "7. Изменить массив" << endl;
	cout << "0. Завершение работы" << endl;
	cout << "Ваш выбор: ";
}

void sort(int* mas, int size)
{
	for (int i = 1; i < size; i++)
	{
		for (int j = i; j > 0 && mas[j - 1] < mas[j]; j--)
		{
			int temp = mas[j - 1];
			mas[j - 1] = mas[j];
			mas[j] = temp;
		}
	}
}

int* add_elements(int* mas, int* size)
{
	int count;
	int* new_mas, *mass;

	system("cls");
	cout << "Введите количество новых элементов: ";
	cin >> count;

	new_mas = new int[count];

	for (int i = 0; i < count; i++)
	{
		cout << "new_mas[" << i << "] = ";
		cin >> new_mas[i];
	}

	mass = new int[*size + count];

	for (int i = 0; i < *size; i++) mass[i] = mas[i];
	for (int i = 0; i < count; i++) mass[i + *size] = new_mas[i];
	
	*size += count;

	return mass;

	


}

int max_elem(int* mas, int size)
{
	int max = mas[0];

	for (int i = 0; i < size; i++)
	{
		if (mas[i] > max) max = mas[i];
	}

	return max;
}

int min_elem(int* mas, int size)
{
	int min = mas[0];

	for (int i = 0; i < size; i++)
	{
		if (mas[i] < min) min = mas[i];
	}

	return min;
}


void sum_elements(int* mas, int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++) sum += mas[i];
	system("cls");
	cout << "Сумма всех элементов: " << sum << endl;
	system("pause");
}

int* put_mass(int* len)
{
	system("cls");
	int* mas;
	int size, num;
	cout << "Введите размер массива: ";
	cin >> size;
	*len = size;
	mas = new int[size];
	for (int i = 0; i < size; i++)
	{
		cout << "mas[" << i << "] = ";
		cin >> num;
		mas[i] = num;
	}
	return mas;
}

void print_mas(int* mas, int len)
{
	if (mas == NULL)
	{
		cout << "Массив не заполнен!" << endl;
		system("pause");
		return;
	}
	system("cls");
	cout << "Ваш массив:" << endl;
	for (int i = 0; i < len; i++)
	{
		cout << mas[i] << " ";
	}
	cout << endl;
	system("pause");
}

void change(int* mas, int size)
{
	int x = (max_elem(mas, size) + min_elem(mas, size)) / 2;

	for (int i = 0; i < size; i++) mas[i] *= x;


}

int main()
{
	setlocale(0, "");
	int* mass = NULL;
	int size;
	char ch = ' ';
	do
	{
		menu();
		cin >> ch;
		switch (ch)
		{
		case '1':
			free(mass);
			mass = put_mass(&size);
			break;
		case '2':
			if (mass == NULL)
			{
				cout << "Массив не введен!" << endl;
				system("pause");
				break;
			}
			print_mas(mass, size);
			break;
		case '3':
			if (mass == NULL)
			{
				cout << "Массив не введен!" << endl;
				system("pause");
				break;
			}
			sort(mass, size);
			break;
		case '4':
			if (mass == NULL)
			{
				cout << "Массив не введен!" << endl;
				system("pause");
				break;
			}
			mass = add_elements(mass, &size);
			break;
		case '5':
			if (mass == NULL)
			{
				cout << "Массив не введен!" << endl;
				system("pause");
				break;
			}
			system("cls");
			cout << "Максимальный элемент: " << max_elem(mass, size) << endl;
			system("pause");
			break;
		case '6':
			if (mass == NULL)
			{
				cout << "Массив не введен!" << endl;
				system("pause");
				break;
			}
			sum_elements(mass, size);
			break;
		case '7':
			change(mass, size);
			break;
		case '0':
			break;
		default:
			cout << "Такого пункта нет!" << endl;
			system("pause");
			break;
		}

	} while (ch != '0');
}