#include <iostream>
#include <vector>
#include <fstream>
#include <locale>
#define SIZE_X 10
#define SIZE_Y 10
using namespace std;
//
struct cell {
    int x;
    int y;
};
//
cell start, finish;
// 
vector <vector <cell>> ways;
// лабиринт
int labirint[SIZE_Y][SIZE_X] = {
    {0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,0,0,0},
    {0,1,0,0,0,0,1,0,0,0},
    {0,1,0,0,0,0,1,0,0,0},
    {0,1,1,1,1,0,1,0,0,0},
    {0,0,0,0,1,0,1,0,0,0},
    {0,0,0,0,1,1,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    };

// проверка предыдущей ячейки
bool check_last(vector<cell> way, cell curr) {
    if (way.size() < 2) return true;
    cell back = way[way.size() - 2];

    if (back.x == curr.x && back.y == curr.y) return false;
    else return true;
}

// функция шага
void step(cell curr, vector<cell> way) {
    // если мы пришли в финиш
    if (curr.x == finish.x && curr.y == finish.y) {
        ways.push_back(way);
        return;
    }
    // идем дальше
    if (curr.x + 1 < SIZE_X && labirint[curr.y][curr.x + 1])
    {
        cell next;
        next.x = curr.x + 1;
        next.y = curr.y;
        if (check_last(way, next))
        {
            way.push_back(next);
            step(next, way);
            way.pop_back();
        }

    }
    if (curr.y - 1 >= 0 && labirint[curr.y - 1][curr.x])
    {
        cell next;
        next.x = curr.x;
        next.y = curr.y - 1;
        if (check_last(way, next))
        {
            way.push_back(next);
            step(next, way);
            way.pop_back();
        }
    }
    if (curr.x - 1 >= 0 && labirint[curr.y][curr.x - 1])
    {
        cell next;
        next.x = curr.x - 1;
        next.y = curr.y;
        if (check_last(way, next))
        {
            way.push_back(next);
            step(next, way);
            way.pop_back();
        }
    }
    if (curr.y + 1 < SIZE_Y && labirint[curr.y + 1][curr.x])
    {
        cell next;
        next.x = curr.x;
        next.y = curr.y + 1;
        if (check_last(way, next))
        {
            way.push_back(next);
            step(next, way);
            way.pop_back();
        }
    }
    return;
}


// поиск пути
void find() {
    vector<cell> way;
    way.push_back(start);
    step(start, way);
    int min_len, min_i;

    if (way.size() == 0) {
        cout << "Нет пути!" << endl;
        system("pause");
        return;
    }
    else {
        // находим кратчайший путь из всех найденных
        min_i = 0;
        min_len = ways[0].size();
        for (int i = 0; i < ways.size(); i++) {
            if (ways[i].size() < min_len) {
                min_len = ways[i].size();
                min_i = i;
            }
        }
        //
        int new_labirint[SIZE_Y][SIZE_X];
        for (int i = 0; i < SIZE_Y; i++)
        {
            for (int j = 0; j < SIZE_X; j++) {
                new_labirint[i][j] = 0;
            }
        }
        way = ways[min_i];
        for (int i = 0; i < way.size(); i++) {
            new_labirint[way[i].y][way[i].x] = 1;
        }

        cout << "\tКРАТЧАЙШИЙ ПУТЬ" << endl;
        for (int i = 0; i < SIZE_Y; i++) {
            for (int j = 0; j < SIZE_X; j++) cout << new_labirint[i][j] << ' ';
            cout << endl;
        }
        system("pause");
        system("cls");

    }
    
}

// функция проверки координат
int check_start_finish() {
    // проверка координат
    if (start.x < 0 || start.y < 0 || finish.x < 0 || finish.y < 0 || start.x >= SIZE_X || 
        start.y >= SIZE_Y || finish.x >= SIZE_X || finish.y >= SIZE_Y) {
        cout << "Ошибка ввода координат!" << endl;
        system("pause");
        return 1;
    }
    if (!labirint[start.y][start.x]) {
        cout << "Старт не может быть стеной!" << endl;
        system("pause");
        return 1;
    }
    if (!labirint[finish.y][finish.x]) {
        cout << "Финиш не может быть стеной!" << endl;
        system("pause");
        return 1;
    }
    return 0;
}
// функция вывода лабиринта
void print_lab() {
    cout << "\tЛАБИРИНТ" << endl;
    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_X; j++) cout << labirint[i][j] << ' ';
        cout << endl;
    }
    cout << "1 - Путь" << endl;
    cout << "0 - Стена" << endl;
    system("pause");
    cout << endl;
}

int main()
{
    setlocale(0, "");
    print_lab();
    // ввод координат
    cout << "Ввод старта : " << endl;
    cout << "x = ";
    cin >> start.x;
    cout << "y = ";
    cin >> start.y;

    cout << "Ввод финиша : " << endl;
    cout << "x = ";
    cin >> finish.x;
    cout << "y = ";
    cin >> finish.y;
    start.x -= 1;
    start.y -= 1;
    finish.x -= 1;
    finish.y -= 1;
    // проверка координат
    if (check_start_finish()) {
        return 1;
    }
    find();
    return 0;
}