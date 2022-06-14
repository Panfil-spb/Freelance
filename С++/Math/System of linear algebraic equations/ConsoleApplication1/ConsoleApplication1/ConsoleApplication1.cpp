#include <iostream>
#include <vector>
#include <fstream>
#include <locale>

using namespace std;

void LU(vector <vector <double>> A, vector <vector <double>>& L,
	vector <vector <double>>& U, int n)
{
	U = A;

	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			L[j][i] = U[j][i] / U[i][i];

	for (int k = 1; k < n; k++)
	{
		for (int i = k - 1; i < n; i++)
			for (int j = i; j < n; j++)
				L[j][i] = U[j][i] / U[i][i];

		for (int i = k; i < n; i++)
			for (int j = k - 1; j < n; j++)
				U[i][j] = U[i][j] - L[i][k - 1] * U[k - 1][j];
	}

}

void proisv(vector <vector <double>> A, vector <vector <double>> B,
	vector <vector <double>>& R, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				R[i][j] += A[i][k] * B[k][j];
}

void print_in_file(vector <vector <double>> A, int n, ofstream &f)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			f.width(13);
			f << A[i][j];
            cout.width(13);
            cout << A[i][j];
		}
		f << endl;
        cout << endl;
	}
}

void LU_method() {
	int n;
    cout << "Введите размерность матрицы: ";
    cin >> n;
	vector <vector <double>> A(n), L(n), U(n), R(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int a;
			cout << "A[" << i << "][" << j << "] = ";
			cin >> a;
			A[i].push_back(a);
			L[i].push_back(0);
			U[i].push_back(0);
			R[i].push_back(0);
		}
	}
	ofstream f;
	f.open("LU-method.txt");
	LU(A, L, U, n);
	f << "Fisrt matrix" << endl;
    cout << "Fisrt matrix" << endl;
	print_in_file(A, n, f);
	f << "U matrix" << endl;
    cout << "U matrix" << endl;
	print_in_file(U, n, f);
	f << "L matrix" << endl;
    cout << "L matrix" << endl;
	print_in_file(L, n, f);
	proisv(L, U, R, n);
	f << "L*U matrix" << endl;
    cout << "L*U matrix" << endl;
	print_in_file(R, n, f);
    f.close();
}

double sign(double x) {
    if (x == 0.0) return 0;
    if (x > 0.0) return 1;
    else return -1;
}

void sqrt_method() {
    ofstream f;
    f.open("sqrt_method.txt");
    int n, m;
    cout << "Введите размерность матрицы: ";
    cin >> n;

    m = n + 1;                      //Расширенная матрица
    //double** A = new double* [n + 1]; //Выделяем память под строки
    //for (int i = 1; i <= n; i++)
    //    A[i] = new double[m + 1];     //Под столбцы
    vector <vector <double>> A(n + 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int a;
            cout << "A[" << i << "][" << j << "] = ";
            cin >> a;
            A[i].push_back(a);
        }
    }
    system("cls");
    //Вывод на экран
    f << "Матрица A: " << endl;
    cout << "Матрица A: " << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j == m - 1) f << "|";
            f.width(13);
            f << A[i][j] << " ";
            cout.width(13);
            cout << A[i][j] << " ";
        }
        f << endl;
        cout << endl;
    }
    f << endl;
    cout << endl;

    /*    A = S*DS,
          S — верхняя треугольная матрица с положительными элементами на главной диагонали,
          S*— транспонированная матрица S,
          D — диагональная матрица, на диагонали которой находятся числа, равные ± 1*/
    vector <vector <double>> S(n + 1), D(n + 1);
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            S[i].push_back(0);
            D[i].push_back(0);
        }
    }

/*------------------------Инициализация первых элементов матриц S и D------------------------*/
    S[0][0] = sqrt(abs(A[0][0]));
    D[0][0] = sign(A[0][0]);
    for (int j = 1; j < n; ++j) {
        S[0][j] = A[0][j] / (S[0][0] * D[0][0]);
    }
    /*Все элементы матрицы S считаются по следующей схеме:
       s[i,j]= (A[i,j] - sum(от l=1 до l=i-1)(s[l,i]*s[l,j]*D[l,l]))/s[i,i]*D[i,i]
      А все элементы диагональной матрицы D считаются следующим образом:
       D[i,i]= sign(A[i,j] - sum(от l=1 до l=i-1)(S[l][i] * S[l][i] * D[l][l]
    /*------------------------  Инициализация первых элементов матриц S и D------------------------*/

    /*------------------------Расчитывамем все оставшиеся значения S и D------------------------*/
    for (int i = 1; i < n; ++i) {
        double sum = 0;
        for (int l = 0; l < i - 1; ++l)
            sum = sum + S[l][i] * S[l][i] * D[l][l];
        S[i][i] = sqrt(abs(A[i][i] - sum));
        D[i][i] = sign(A[i][i] - sum);
        for (int j = i; j < n; ++j) {
            sum = 0;
            for (int l = 0; l < i - 1; l++) {
                sum = sum + S[l][i] * S[l][j] * D[l][l];
            }
            S[i][j] = (A[i][j] - sum) / (S[i][i] * D[i][i]);
        }
    }
    /*------------------------Расчитывамем все оставшиеся значения S и D------------------------*/

    /*Выводим матрицу после прямого хода, чтобы проверить, что она была приведена
         к ступенчатому виду
      Так как счет идет с ошибкой вычисления, то для наглядности занулим то,
       что находится ниже главной диагонали, а также проверим вектор правой части на наличие
        цифр с ошибкой вычисления                                                       */

    f << "Главная диагональ матрицы D:" << endl;
    cout << "Главная диагональ матрицы D:" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (abs(S[i][j]) < 0.000001) S[i][j] = 0;

    for (int i = 0; i < n; i++) {
        f.width(13);
        f << D[i][i] << " ";
        cout.width(13);
        cout << D[i][i] << " ";
    }
    f << endl;
    cout << endl;
    f << "Полученная матрица S:" << endl;
    cout << "Полученная матрица S:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            f.width(13);
            f << S[i][j] << " ";
            cout.width(13);
            cout << S[i][j] << " ";
        }
        cout << endl;
        f << endl;
    }
    f << endl;
    cout << endl;


    /*Итак, если после предыдущих действий имеем матрицу S. Чтобы довести решение
       нам требуется представить исходную матрицу в виде:
                 A = S*S, где S* - транспонированная матрица S
      Не будем совершать лишних действий по выделению памяти под новую матрицу,
       а просто поменяем местами индексы у матрицы S[i,j] местами, это и будет S*.
                                                                                    */

  /*-------------------------------------Обратный ход-------------------------------------*/
  /*Обратный ход состоит в в последовательном решении двух систем уравнений
   (1) S*y = f
   где f это последний столбец в расширенной матрице (вектор)
   в нашем случае это переменная вида A[i,m], где m это последний стобец матрицы
    Формула для нахождения y[i]
    y[i] = (f[i] - sum(от l=1 до l=i-1)(s[l,i]*y[l]))/s[i,i], где i = 2,3,..,m*/
    
    vector <double> y(n + 1);
    y.push_back(A[0][m - 1] / S[0][0] * D[0][0]);        //y[1] всегда равен f[1]/s[1,1]
    for (int i = 1; i < n; ++i) {
        double sum = 0;
        for (int l = 0; l < i - 1; ++l)
            sum = sum + S[l][i] * y[l] * D[l][l];
        y.push_back((A[i][m - 1] - sum) / (S[i][i] * D[i][i]));
    }
    f << "Вектор y:" << endl;
    cout << "Вектор y:" << endl;
    for (int i = 0; i < n; ++i) {
        cout.width(13);
        cout << y[i] << ' ';
        f.width(13);
        f << y[i] << ' ';
    }
    cout << endl;
    f << endl;

    /*Используя значения y, найденные в предыдущем уравнении, решаем второе уравнение
                                 (2) Sx = y
       формула для нахождения x[i]
            x[i] = (y[i] - sum(от l=1+1 до l=i)(s[i,l]*x[l]))/s[i,i], гдн i = i-1,i-2,..,1
                                                                                            */
    double* x = new double[n + 1];
    x[n] = y[n] / S[n][n];           //Последний x[n] всегда равен u[n]/s[n,n]
    for (int i = n - 1; i >= 1; --i) {
        double sum = 0;
        for (int l = i + 1; l <= n; ++l)
            sum = sum + S[i][l] * x[l];
        x[i] = (y[i] - sum) / S[i][i];
    }
    /*---------------------------------------Обратный ход--------------------------------------*/

    //Выводим решения
    f << endl << "Ответ" << endl;
    cout << endl << "Ответ" << endl;
    for (int i = 0; i < n; i++) {
        f.width(13);
        f << x[i] << ' ';
        cout.width(13);
        cout << x[i] << ' ';
    }
    f.close();
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
			LU_method();
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