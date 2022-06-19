#include <iostream>
#include <fstream>

using namespace std;

// печать матрицы
void printMatrix(double** matr, int n, ofstream& f);
// печать вектор-столбца
void printVectorCol(double* v, int n, ofstream& f);
//
double getSumU(int n, int i, int j, double** mL, double** mU);
//
double getSumL(int n, int i, int j, double** mL, double** mU);
// LU-разложение
void decomp(double** mA, int n, double** mL, double** mU);
//
double getSumY(int n, double** mL, double* vB, double* vY, int i);
//
double getSumX(int n, double** mU, double* vX, int i);
// решатель
void solver(double** mA, int n, double** mL, double** mU, double* vB, double* vY, double* vX);


void LU(double** matrA, double* vB, int n)
{
    
    // динамическое выделение памяти
    double** matrL = new double* [n];
    double** matrU = new double* [n];
    for (int i = 0; i < n; i++)
    {
        matrL[i] = new double[n];
        matrU[i] = new double[n];
    }
    double* vX = new double[n];
    double* vY = new double[n];

    // инициализация матриц и векторов нулями
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrL[i][j] = 0;
            matrU[i][j] = 0;
        }

        vX[i] = 0;
        vY[i] = 0;
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
void printMatrix(double** matr, int n, ofstream& f)
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
void printVectorCol(double* v, int n, ofstream& f)
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
double getSumU(int n, int i, int j, double** mL, double** mU)
{
    double res = 0;

    for (int k = 0; k < i; k++)
    {
        res += mL[i][k] * mU[k][j];
    }

    return res;
}

//
double getSumL(int n, int i, int j, double** mL, double** mU)
{
    double res = 0;

    for (int k = 0; k < i; k++)
    {
        res += mL[j][k] * mU[k][i];
    }

    return res;
}

// LU-разложение
void decomp(double** mA, int n, double** mL, double** mU)
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
double getSumY(int n, double** mL, double* vB, double* vY, int i)
{
    double res = 0;

    for (int k = 0; k < i; k++)
    {
        res += mL[i][k] * vY[k];
    }

    return res;
}

//
double getSumX(int n, double** mU, double* vX, int i)
{
    double res = 0;

    for (int k = n - 1; k > i; k--)
    {
        res += mU[i][k] * vX[k];
    }

    return res;
}

// решатель
void solver(double** mA, int n, double** mL, double** mU, double* vB, double* vY, double* vX)
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

