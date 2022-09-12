#include <iostream>
using namespace std;
void Swap(int* a, int i, int j)
{
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}
bool NextSet(int* a, int n)
{
    int j = n - 2;
    while (j != -1 && a[j] >= a[j + 1]) j--;
    if (j == -1)
        return false; // больше перестановок нет
    int k = n - 1;
    while (a[j] >= a[k]) k--;
    Swap(a, j, k);
    int l = j + 1, r = n - 1; // сортируем оставшуюся часть последовательности
    while (l < r)
        Swap(a, l++, r--);
    return true;
}
void Print(int* mas, int n)  // вывод перестановки
{
    static int count = 1; // номер перестановки
    cout.width(3); // ширина поля вывода номера перестановки
    cout << count++ << ": ";
    for (int i = 0; i < n; i++)
        cout << mas[i] << " ";
    cout << endl;
}
int main()
{
    int n, * mas;
    cout << "N = ";
    cin >> n;
    mas = new int[n];
    for (int i = 0; i < n; i++) {
        cout << "mas[" << i << "] = ";
        cin >> mas[i];
    }
    system("cls");
    Print(mas, n);
    while (NextSet(mas, n))
        Print(mas, n);
    system("pause");
    return 0;
}