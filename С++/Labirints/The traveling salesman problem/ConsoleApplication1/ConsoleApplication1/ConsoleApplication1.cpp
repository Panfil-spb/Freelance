#include <iostream>
#include <vector>
#include <fstream>
#include <locale>

using namespace std;
class Map
{
public:
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    struct final_way {
        vector<int> way;
        int sum = -1;
    };

    final_way fin;
    // структура клетки
    struct cell {
        int x;
        int y;
    };
    // переменная хранящая координаты склада
    cell sclad;
    // весктора координат магазинов
    vector <cell> shops;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // карта
    int** map;
    // размерность карты
    int size_x, size_y;
    // функция загрузки карты и получение координат склада и магазинов
    void load_map() {
        ifstream file("map.txt");
        if (file.is_open()) {
            // получаем размерность лабиринта
            file >> size_x;
            file >> size_y;
            // выделяем память под карту
            map = new int*[size_y];
            for (int i = 0; i < size_y; i++) {
                map[i] = new int[size_x];
            }
            // читаем карту
            for (int i = 0; i < size_y; i++) {
                for (int j = 0; j < size_x; j++) {
                    file >> map[i][j];
                    // если была считана клетка магазина
                    if (map[i][j] == 2) {
                        // иницилизируем клетку
                        cell curr;
                        curr.x = j;
                        curr.y = i;
                        // добавляем ее в конец
                        shops.push_back(curr);
                    }
                    else if (map[i][j] == 3) {
                        sclad.x = j;
                        sclad.y = i;
                    }
                }
            }


        }


    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // структура кратчайшего пути между пунктами
    struct short_way {
        vector <cell> way;
        int len;
        bool flag = false;
    };

    short_way** tabl;
    int size_table;
    // функция создания таблицы кратчайших путей
    void create_tabl() {
        size_table = shops.size() + 1;
        tabl = new short_way * [size_table];
        for (int i = 0; i < size_table; i++) {
            tabl[i] = new short_way[size_table];
        }
    }
    // функция заполнения таблицы
    void init_table() {
        for (int i = 0; i < size_table; i++) {
            for (int j = 0; j < size_table; j++) {
                if (i == j) continue;
                else {
                    if (!tabl[i][j].flag) {
                        if (!i) {
                            tabl[i][j].way = find(sclad, shops[j - 1]);
                            tabl[i][j].flag = true;
                            tabl[i][j].len = tabl[i][j].way.size();

                            tabl[j][i].flag = true;
                            tabl[j][i].len = tabl[i][j].way.size();
                            tabl[j][i].way = tabl[i][j].way;
                        }
                        else if (!j) {
                            tabl[i][j].way = find(shops[i - 1], sclad);
                            tabl[i][j].flag = true;
                            tabl[i][j].len = tabl[i][j].way.size();

                            tabl[j][i].flag = true;
                            tabl[j][i].len = tabl[i][j].way.size();
                            tabl[j][i].way = tabl[i][j].way;
                        }
                        else {
                            tabl[i][j].way = find(shops[i - 1], shops[j - 1]);
                            tabl[i][j].flag = true;
                            tabl[i][j].len = tabl[i][j].way.size();

                            tabl[j][i].flag = true;
                            tabl[j][i].len = tabl[i][j].way.size();
                            tabl[j][i].way = tabl[i][j].way;
                        }
                    }
                }
            }
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // проверка предыдущей ячейки
    bool check_last(vector<cell> way, cell curr) {
        for (int i = 0; i < way.size(); i++) {
            if (way[i].x == curr.x && way[i].y == curr.y) return false;
        }
        return true;
    }

    // функция шага
    void step(vector<vector<cell>> &ways, vector<cell> &way, cell start, cell finish, cell curr) {

        if (curr.x + 1 < size_x && (finish.x == curr.x + 1 && finish.y == curr.y))
        {
            ways.push_back(way);
            return;
        }
        if (curr.y - 1 >= 0 && (finish.x == curr.x && finish.y == curr.y - 1))
        {
            ways.push_back(way);
            return;
        }
        if (curr.x - 1 >= 0 && (finish.x == curr.x - 1 && finish.y == curr.y))
        {
            ways.push_back(way);
            return;
        }
        if (curr.y + 1 < size_y && (finish.x == curr.x && finish.y == curr.y + 1))
        {
            ways.push_back(way);
            return;
        }
        // идем дальше
        if (curr.x + 1 < size_x &&  map[curr.y][curr.x + 1] == 0)
        {
            cell next;
            next.x = curr.x + 1;
            next.y = curr.y;
            if (check_last(way, next))
            {
                way.push_back(next);
                step(ways, way, start, finish, next);
                way.pop_back();
            }

        }
        if (curr.y - 1 >= 0 && map[curr.y - 1][curr.x] == 0)
        {
            cell next;
            next.x = curr.x;
            next.y = curr.y - 1;
            if (check_last(way, next))
            {
                way.push_back(next);
                step(ways, way, start, finish, next);
                way.pop_back();
            }
        }
        if (curr.x - 1 >= 0 && map[curr.y][curr.x - 1] == 0)
        {
            cell next;
            next.x = curr.x - 1;
            next.y = curr.y;
            if (check_last(way, next))
            {
                way.push_back(next);
                step(ways, way, start, finish, next);
                way.pop_back();
            }
        }
        if (curr.y + 1 < size_y && map[curr.y + 1][curr.x] == 0)
        {
            cell next;
            next.x = curr.x;
            next.y = curr.y + 1;
            if (check_last(way, next))
            {
                way.push_back(next);
                step(ways, way, start, finish, next);
                way.pop_back();
            }
        }
        return;
    }


    // поиск пути
    vector<cell> find(cell start, cell finish) {
        vector<cell> way;
        vector<vector<cell>> ways;
        way.push_back(start);
        step(ways, way, start, finish, start);
        int min_len, min_i;

        // находим кратчайший путь из всех найденных
        min_i = 0;
        min_len = ways[0].size();
        for (int i = 0; i < ways.size(); i++) {
            if (ways[i].size() < min_len) {
                min_len = ways[i].size();
                min_i = i;
            }
        }
        return ways[min_i];
    }    
    // функция вывода лабиринта
    void print_map() {
        cout << "\tКАРТА" << endl;
        for (int i = 0; i < size_y; i++) {
            for (int j = 0; j < size_x; j++) cout << map[i][j] << ' ';
            cout << endl;
        }
        cout << "0 - Дорога" << endl;
        cout << "1 - Здание" << endl;
        cout << "2 - Магазин" << endl;
        cout << "3 - Склад" << endl;
        system("pause");
        cout << endl;
    }


    bool check_table_way(vector<int> way, int num) {
        for (int i = 0; i < way.size(); i++) {
            if (way[i] == num) return false;
        }
        return true;
    }

    void step_table(vector<int> &way, int sum, int num) {
        if (way.size() == shops.size() + 1) {
            if (fin.sum < 0) {
                fin.sum = sum + tabl[num][0].len;
                fin.way = way;
                fin.way.push_back(0);
            }
            else {
                if (fin.sum > sum + tabl[num][0].len) {
                    fin.sum = sum + tabl[num][0].len;
                    fin.way = way;
                    fin.way.push_back(0);
                }
            }
            return;
        }
        for (int i = 1; i < shops.size() + 1; i++) {
            if (check_table_way(way, i)) {
                way.push_back(i);
                step_table(way, sum + tabl[num][i].len, i);
                way.pop_back();
            }
        }
    }
    // ищем самый короткий путь от пункта к пункту
    void find_short_all_way() {
        int size = shops.size() + 1;
        int sum = 0;
        vector<int> way;
        way.push_back(0);
        for (int i = 1; i < size; i++) {
            way.push_back(i);
            step_table(way, sum + tabl[0][i].len, i);
            way.pop_back();
        }
    }

    void change_map(vector<cell> way) {
        for (int i = 0; i < way.size(); i++) {
            int x = way[i].x;
            int y = way[i].y;
            if(map[y][x] == 0) map[y][x] = 4;
        }

    }

    void print_way() {
        for (int i = 0; i < fin.way.size() - 1; i++) {
            change_map(tabl[fin.way[i]][fin.way[i + 1]].way);
        }
        print_map();
        
    }


    Map();
    ~Map();

private:

};

Map::Map()
{
}

Map::~Map()
{
}

int main()
{
    setlocale(0, "");
    Map p = Map();
    p.load_map();
    p.print_map();
    p.create_tabl();
    p.init_table();
    p.find_short_all_way();
    p.print_way();
    return 0;
}