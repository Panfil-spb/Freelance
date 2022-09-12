#include <iostream>
#include <vector>
#include <fstream>
#include <locale>
#include "sqrt_method.h"
#include "LU.h"

using namespace std;


int main()
{
	setlocale(0, "");
    char c2 = '1';
    char c1 = '1';
    int n;
    double** a= NULL;
    double* b = NULL;
    while (c1 != '0') {
        system("cls");
        cout << "1. Ввести матрицу" << endl;
        cout << "2. Решить систему" << endl;
        cout << "0. Выход" << endl;
        cout << "Ваш выбор: ";
        cin >> c1;
        switch (c1)
        {
        case '1':
            if (a != NULL) {
                for (int i = 0; i < n; i++) {
                    delete[] a[i];
                }
                delete[] a;
                a = NULL;
            }

            if (b != NULL) {
                delete[] b;
                b = NULL;
            }
            system("cls");
            cout << "n = ";
            cin >> n;
            a = new double* [n];
            
            for (int i = 0; i < n; i++) {
                a[i] = new double[n];
                for (int j = 0; j < n; j++) {
                    cout << "a[" << i << "][" << j << "] = ";
                    cin >> a[i][j];
                }
            }

            b = new double[n];

            for (int i = 0; i < n; i++) {
                cout << "b[" << i << "] = ";
                cin >> b[i];
            }
            break;
        case '2':
            if (a == NULL || b == NULL) {
                system("cls");
                cout << "Матрица и вектор не введены!" << endl;
                system("pause");
                break;
            }
            c2 = '1';
            while (c2 != '0') {
                system("cls");
                cout << "1. LU" << endl;
                cout << "2. Квадратичные корни" << endl;
                cout << "0. Назад" << endl;
                cout << "Ваш выбор: ";
                cin >> c2;
                switch (c2)
                {
                case '1':
                    system("cls");
                    LU(a, b, n);
                    system("cls");
                    cout << "СЛАУ решено методом LU разложением." << endl;
                    system("pause");
                    break;
                case '2':
                    system("cls");
                    sqrt_method(a, b, n);
                    cout << endl << "СЛАУ решено методом квадратного разложения разложением." << endl;
                    system("pause");
                    break;
                case '0':
                    break;
                default:
                    break;
                }
            }
            break;
        case '0':
            break;
        default:
            break;
        }
        
    }
	return 0;
}