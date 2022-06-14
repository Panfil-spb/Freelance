#include <iostream>
#include <vector>
#include <fstream>
#include <locale>

using namespace std;

using namespace std;
// печать матрицы
void printMatrix(float** matr, int n, ofstream& f);
// печать вектор-столбца
void printVectorCol(float* v, int n, ofstream& f);
//
float getSumU(int n, int i, int j, float** mL, float** mU);
//
float getSumL(int n, int i, int j, float** mL, float** mU);
// LU-разложение
void decomp(float** mA, int n, float** mL, float** mU);
//
float getSumY(int n, float** mL, float* vB, float* vY, int i);
//
float getSumX(int n, float** mU, float* vX, int i);
// решатель
void solver(float** mA, int n, float** mL, float** mU, float* vB, float* vY, float* vX);


void LU()
{
    int n; // размерность системы
    cout << "Введите размерность матрицы: ";
    cin >> n;
    // динамическое выделение памяти
    float** matrA = new float* [n];
    float** matrL = new float* [n];
    float** matrU = new float* [n];
    for (int i = 0; i < n; i++)
    {
        matrA[i] = new float[n];
        matrL[i] = new float[n];
        matrU[i] = new float[n];
    }
    float* vB = new float[n];
    float* vX = new float[n];
    float* vY = new float[n];

    // инициализация матриц и векторов нулями
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrA[i][j] = 0;
            matrL[i][j] = 0;
            matrU[i][j] = 0;
        }

        vB[i] = 0;
        vX[i] = 0;
        vY[i] = 0;
    }

    // заполнение матрицы A случайными числами из интервала [1; 100]
    for (int i = 0; i < n; i++) // по строкам
    {
        for (int j = 0; j < n; j++) // по столбцам
        {
            cout << "matr[" << i << "][" << j << "] = ";
            cin >> matrA[i][j];
        }
    }

    // задание случайных значений свободных коэффициентов
    for (int i = 0; i < n; i++)
    {
        cout << "vB[" << i << "] = ";
        cin >> vB[i];
    }

    /***************************************************************************/

        // LU-разложение
    decomp(matrA, n, matrL, matrU);

    // решение системы
    solver(matrA, n, matrL, matrU, vB, vY, vX);

    /***************************************************************************/
    system("cls");
        // печать результатов
    ofstream f;
    f.open("LU.txt");
    printf("A = \n");
    f << "A = " << endl;
    printMatrix(matrA, n, f);
    printf("\n");
    f << endl;
    f << "B = " << endl;
    printf("B = \n");
    printVectorCol(vB, n, f);
    printf("\n");
    f << endl;
    f << "L = " << endl;
    printf("L = \n");
    printMatrix(matrL, n, f);
    printf("\n");
    f << endl;

    f << "U = " << endl;
    printf("U = \n");
    printMatrix(matrU, n, f);
    printf("\n");
    f << endl;
    f << "Y = " << endl;
    printf("Y = \n");
    printVectorCol(vY, n, f);
    printf("\n");
    f << endl;
    f << "X = " << endl;
    printf("X = \n");
    printVectorCol(vX, n, f);
    printf("\n");
    f << endl;
    f.close();
    /***************************************************************************/

        // освобождение памяти
    for (int i = 0; i < n; i++)
    {
        delete[] matrA[i];
        delete[] matrL[i];
        delete[] matrU[i];
    }
    delete[] matrA;
    delete[] matrL;
    delete[] matrU;
    delete[] vB;
    delete[] vX;
    delete[] vY;

    printf("\n");
    system("pause");
}

// печать матрицы
void printMatrix(float** matr, int n, ofstream& f)
{
    for (int i = 0; i < n; i++) // по строкам
    {
        for (int j = 0; j < n; j++) // по столбцам
        {
            f.width(13);
            f << matr[i][j];
            printf("%7.3f ", matr[i][j]);
        }
        f << endl;
        printf("\n"); // новая строка
    }
}

// печать вектор-столбца
void printVectorCol(float* v, int n, ofstream& f)
{
    for (int i = 0; i < n; i++)
    {
        f.width(13);
        f << v[i] << endl;
        printf("%7.3f ", v[i]);
        printf("\n");
    }
}

//
float getSumU(int n, int i, int j, float** mL, float** mU)
{
    float res = 0;

    for (int k = 0; k < i; k++)
    {
        res += mL[i][k] * mU[k][j];
    }

    return res;
}

//
float getSumL(int n, int i, int j, float** mL, float** mU)
{
    float res = 0;

    for (int k = 0; k < i; k++)
    {
        res += mL[j][k] * mU[k][i];
    }

    return res;
}

// LU-разложение
void decomp(float** mA, int n, float** mL, float** mU)
{
    // i = 0
    for (int j = 0; j < n; j++)
    {
        mU[0][j] = mA[0][j];
        mL[j][0] = mA[j][0] / mU[0][0];
    }

    // i = 1 .. n-1
    for (int i = 1; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            mU[i][j] = mA[i][j] - getSumU(n, i, j, mL, mU);

            mL[j][i] = (mA[j][i] - getSumL(n, i, j, mL, mU)) / mU[i][i];
        }
    }
}

//
float getSumY(int n, float** mL, float* vB, float* vY, int i)
{
    float res = 0;

    for (int k = 0; k < i; k++)
    {
        res += mL[i][k] * vY[k];
    }

    return res;
}

//
float getSumX(int n, float** mU, float* vX, int i)
{
    float res = 0;

    for (int k = n - 1; k > i; k--)
    {
        res += mU[i][k] * vX[k];
    }

    return res;
}

// решатель
void solver(float** mA, int n, float** mL, float** mU, float* vB, float* vY, float* vX)
{
    // Y. Решение прямой подстановкой
    for (int i = 0; i < n; i++)
    {
        vY[i] = (vB[i] - getSumY(n, mL, vB, vY, i)) / mL[i][i];
    }

    // X. Решение обратной подстановкой
    for (int i = n - 1; i >= 0; i--)
    {
        vX[i] = (vY[i] - getSumX(n, mU, vX, i)) / mU[i][i];
    }
}

void print_matr(double** m, int n, ofstream& f) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout.width(10);
            cout << m[i][j];
            f.width(10);
            f << m[i][j];
        }
        cout << endl;
        f << endl;
    }
}

void print_vector(double* v, int n, ofstream& f) {
    for (int j = 0; j < n; j++) {
        cout.width(10);
        cout << v[j] << endl;
        f.width(10);
        f << v[j] << endl;
    }
}

void sqrt_method()
{
    int n;
    cout << "n = ";
    cin >> n;
    double** a = new double* [n];
    double** s = new double* [n];
    double** s_t = new double* [n];
    double** d = new double* [n];
    for (int i = 0; i < n; i++) {
        a[i] = new double[n];
        s[i] = new double[n];
        s_t[i] = new double[n];
        d[i] = new double[n];
    }
    double* b = new double[n];
    double* x = new double[n];
    double* y = new double[n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "a[" << i << "][" << j << "] = ";
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        cout << "b[" << i << "] = ";
        cin >> b[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) {
                s[i][j] = sqrt(a[i][j]);
            }
            if (i == 0 && j > 0) {
                s[0][j] = a[0][j] / s[0][0];
            }
            if (i == j && i != 0) {
                double sum = 0;
                for (int k = 0; k < i; k++) {
                    sum += pow(s[k][i], 2);
                }
                s[i][i] = sqrt(a[i][i] - sum);
            }
            if (i > 0 && i < j) {
                double sum = 0;
                for (int k = 0; k < i; k++) {
                    sum += s[k][i] * s[k][j];
                }
                s[i][j] = (a[i][j] - sum) / s[i][i];
            }
            if (i > 0 && i > j) {
                s[i][j] = 0;
            }
        }
    }


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            s_t[j][i] = s[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            y[0] = b[0] / s[0][0];
        }
        if (i > 0) {
            double sum = 0;
            for (int k = 0; k < i; k++) {
                sum += s[k][i] * y[k];
            }
            y[i] = (b[i] - sum) / s[i][i];
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        if (i == n - 1) {
            x[i] = y[i] / s[i][i];
        }
        if (i >= 0) {
            double sum = 0;
            for (int k = i + 1; k < n; k++) {
                sum += s[i][k] * x[k];
            }
            x[i] = (y[i] - sum) / s[i][i];
        }
    }

    ofstream f;
    f.open("sqrt_method.txt");
    cout << endl << "a" << endl;
    f << endl << "a" << endl;
    print_matr(a, n, f);
    cout << endl << "s" << endl;
    f << endl << "s" << endl;
    print_matr(s, n, f);
    cout << endl << "s_t" << endl;
    f << endl << "s_t" << endl;
    print_matr(s_t, n, f);
    cout << endl << "y" << endl;
    f << endl << "y" << endl;
    print_vector(y, n, f);
    cout << endl << "x" << endl;
    f << endl << "x" << endl;
    print_vector(x, n, f);
}


int main()
{
	setlocale(0, "");
	char c = '1';
	while (c != '0') {
		system("cls");
		cout << "1. LU" << endl;
		cout << "2. Квадратичные корни" << endl;
		cout << "0. Выход" << endl;
		cout << "Ваш выбор: ";
		cin >> c;
		switch (c)
		{
		case '1':
            system("cls");
			LU();
			system("cls");
			cout << "СЛАУ решено методом LU разложением." << endl;
			system("pause");
			break;
		case '2':
            system("cls");
            sqrt_method();
            cout << endl << "СЛАУ решено методом квадратного разложения разложением." << endl;
            system("pause");
			break;
		case '0':
            system("cls");
            cout << "Завершение работы" << endl;
            system("pause");
			break;
		default:
			break;
		}
	}
	return 0;
}