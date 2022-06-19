#include <iostream>
#include <fstream>

using namespace std;

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

void sqrt_method(double ** a, double* b, int n)
{    
    double** s = new double* [n];
    double** s_t = new double* [n];
    double** d = new double* [n];
    for (int i = 0; i < n; i++) {
        s[i] = new double[n];
        s_t[i] = new double[n];
        d[i] = new double[n];
    }
   
    double* x = new double[n];
    double* y = new double[n];

    
    

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
