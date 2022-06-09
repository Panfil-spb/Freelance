// подключаемые библиотеки
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <thread>
#include <chrono>
#include <ctime>
#include <locale>

// подключаемое пространство имен
using namespace std;

// класс карты
class Map {
public:
	// переменные высоты и ширины
	int width, height;
	// метод установки размера
	void set_size(int h, int w) {
		height = h;
		width = w;
	}
	// метод подсчета заданного элемента
	int count_this_element(char ele) {
		int c = 0;
		// проходимся как по матрице
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				char ch = map_array[i][j];
				if (ch == 'm') ch = 'M';
				if (ch == ele) c++;
			}
		}
		// возвращаем количесвто
		return c;
	}
	// метод генерации мин на поле
	void lay_mine_field(int mine_number) {

		fill_map_with(' ');

		int total_cells = width * height;
		if (mine_number > total_cells) mine_number = total_cells;

		map_array.resize(height);

		int mine_count = 0;
		boolean re_gen = false;

	generate_mine:
		// расставляем мины
		for (int i = 0; i < height; i++) {
			if (!re_gen) map_array[i].resize(width);
			for (int j = 0; j < width; j++) {
				if (map_array[i][j] != 'M') {
					if (mine_count < mine_number) {
						int hasMine = rand() % 100 + 1;
						if (hasMine <= 8) {
							map_array[i][j] = 'M';
							mine_count++;
						}
						else map_array[i][j] = ' ';
					}
				}
			}
		}
		// так как мы расставляем мины с помощью рандома
		// и количесвто мин меньше нужного количесвта 
		if (mine_count < mine_number) {
			re_gen = true;
			// переходим опять к генерации
			goto generate_mine;
		}
	}
	// метод установка рандомной карты
	void set_random_map(int mine_num) {
		// рассавляем мины
		lay_mine_field(mine_num);
		char digit[] = { ' ','1','2','3','4','5','6' };
		// проходимся по координатам
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				// если в координате не мина
				if (map_array[y][x] != 'M') {
					int mine_count = 0;
					// проходимся вокруг координаты и считаем количество мин
					for (int i = y - 1; i <= y + 1; i++) {
						for (int j = x - 1; j <= x + 1; j++) {
							if (i >= 0 && i < height && j >= 0 && j < width) {
								if (map_array[i][j] == 'M') mine_count++;
							}
						}
					}
					// устанавливаем это значение
					map_array[y][x] = digit[mine_count];
				}
			}
		}
	}
	// метод создания поля
	void fill_map_with(char c) {
		// подгоняем карту по высоте
		map_array.resize(height);
		for (int i = 0; i < height; i++) {
			// подгоняем по ширине
			map_array[i].resize(width);
			// заполняем символами
			for (int j = 0; j < width; j++) map_array[i][j] = c;
		}
	}
	// метод получения значения по координатам
	char get_char_at(int y, int x) {
		if (y < map_array.size() && x < map_array[y].size()) return map_array[y][x];
	}
	// метод установки значения по координатам
	void set_char(int y, int x, char c) {
		map_array[y][x] = c;
	}

private:
	// вектор векторов значений поля
	// по сути это матрица
	vector < vector<char> > map_array;
};
// фукнция задает позицию курсору по х у
void go_to_x_y(int y, int x) {

	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
// функция скрытия курсора
void hide_cursor(bool hide) {

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 25;
	cci.bVisible = !hide;
	SetConsoleCursorInfo(hStdout, &cci);
}
// функция подготовки окна
void prepare_window(int y, int x) {
	// получаем консоль
	HWND console = GetConsoleWindow();
	RECT r;
	//сохраняет текущие размеры консоли
	GetWindowRect(console, &r); 
	MoveWindow(console, r.left, r.top, x, y, TRUE);
	// скрываем скрол бар
	HWND scroll = GetConsoleWindow();
	ShowScrollBar(scroll, SB_BOTH, FALSE);

	hide_cursor(true);
}
// класс вывода поля
class Renderer {

public:
	// метод задачи параметров цветов в зависимости от символа
	void colorize(char c = ' ') {

		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

		switch (c) {

		case 'M': {
			SetConsoleTextAttribute(h, FOREGROUND_RED | BACKGROUND_INTENSITY);
			break;
		}

		case 'm': {
			SetConsoleTextAttribute(h, 12 | BACKGROUND_GREEN);
			break;
		}

		case 'F': {
			SetConsoleTextAttribute(h, 14);
			break;
		}

		case 'f': {
			SetConsoleTextAttribute(h, 14 | BACKGROUND_RED);
			break;
		}

		case ' ': {
			SetConsoleTextAttribute(h, 8);
			break;
		}

		case  '1': {
			SetConsoleTextAttribute(h, 9);
			break;
		}

		case  '2': {
			SetConsoleTextAttribute(h, 10);
			break;
		}

		case  '3': {
			SetConsoleTextAttribute(h, 12);
			break;
		}

		case  '4': {
			SetConsoleTextAttribute(h, 15);
			break;
		}
		case  '5': {
			SetConsoleTextAttribute(h, 13);
			break;
		}
		case  '6': {
			SetConsoleTextAttribute(h, 11);
			break;
		}
		default:
			SetConsoleTextAttribute(h, int(c) - 48);
			break;
		}
	}
	// метод печати карты
	void print_map(Map map) {

		go_to_x_y(2, 0);
		for (int i = 0; i < map.width + 2; i++) {
			colorize('F');
			cout << "=" << " "; 
		}
		cout << endl;
		// проходимся по полю, и печатаем согласно функции выше
		for (int i = 0; i < map.height; i++) {

			for (int j = 0; j < map.width; j++) {

				char c = map.get_char_at(i, j);

				if (j == 0) {
					colorize('F');
					cout << "|" << " "; 
					colorize(c);

					cout << c;
					colorize(' ');
					cout << " "; 
				}
				else if (j == map.width - 1) {

					colorize(c);
					if (c == 'm') c = 'M';
					cout << c;
					colorize('F');
					cout << " " << "|"; 
				}
				else {

					colorize(c);
					if (c == 'm') c = 'M';
					if (c == 'f') c = 'F';
					cout << c;

					colorize(' ');
					cout << " "; 
				}
				colorize();
			}
			cout << endl;
		}
		go_to_x_y(map.height + 3, 0);
		for (int i = 0; i < map.width + 2; i++) {
			colorize('F');
			cout << "=" << " ";
		}
		cout << endl;
	}
};
// структура лучших рекордов
struct HighScore {

	int beginner_score;
	int inter_score;
	int expert_score;
};
// структура клетки
struct Cell {

	char value;
	int y;
	int x;
};
// структура действия
struct Action {

	string type;
	vector<Cell> cells;
};
// функция чтения рекордов
HighScore read_high_score() {

	HighScore hc;
	ifstream input;
	// открываем файл
	input.open("highscore.txt");
	// пока не конец файла
	if (!input.eof()) {
		// считываем данные
		input >> hc.beginner_score;
		input >> hc.inter_score;
		input >> hc.expert_score;
		// если записаны значения меньше 0
		// то зануляем их
		if (hc.beginner_score < 0) hc.beginner_score = 0;
		if (hc.inter_score < 0) hc.inter_score = 0;
		if (hc.expert_score < 0) hc.expert_score = 0;
	}
	// если файл не читается то зануляем все значения
	else {
		hc.beginner_score = 0;
		hc.inter_score = 0;
		hc.expert_score = 0;
	}
	// закрываем файл
	input.close();
	// возвращаем структуру
	return hc;
}
// класс для автоматической игры
class AutoSolver {

public:
	// метод получение всех скрытых ячеек
	vector<Cell> get_all_hidden_cells(Map map) {
		// вектор ячеек
		vector<Cell> hidden_cells;
		// проходимя по карте как по матрице
		for (int i = 0; i < map.height; i++) {

			for (int j = 0; j < map.width; j++) {
				// если ячейка скрыта
				if (map.get_char_at(i, j) == '?') {
					// иницилизируем ее
					Cell hidden_cell;
					hidden_cell.value = map.get_char_at(i, j);
					hidden_cell.y = i;
					hidden_cell.x = j;
					// добавляем в конец
					hidden_cells.push_back(hidden_cell);
				}
			}
		}
		// возвращаем наш вектор клеток
		return hidden_cells;
	}
	// метод получение всех открытых ячеек
	vector<Cell> get_all_valued_cells(Map map) {
		// создаем вектор клеток
		vector<Cell> valued_cells;
		// проходимся по карте как по матрице
		for (int i = 0; i < map.height; i++) {

			for (int j = 0; j < map.width; j++) {
				// получаем значение
				int value = get_val_of(map.get_char_at(i, j));
				// если оно больше 0
				if (value > 0) {
					// запоминаем клетку
					Cell valued_cell;
					valued_cell.value = map.get_char_at(i, j);
					valued_cell.y = i;
					valued_cell.x = j;
					// добавляем в конец
					valued_cells.push_back(valued_cell);
				}
			}
		}
		// возвращаем вектор клеток
		return valued_cells;
	}
	// метод получения значения
	int get_val_of(char c) {
		// если пробел возвращаем 0
		if (c == ' ') return 0;
		// если символ игры то -1
		if (c == '?' || c == 'F' || c == 'f') return -1;
		// если же число
		// то возвращаем само значение
		return c - '0';
	}
	// метод получения помеченных флагом ячеек вокруг координаты
	vector<Cell> get_flagged_cells(Map map, int y, int x, int &max_size) {
		// иницилизируем вектор
		vector<Cell> flagged_cells;
		max_size = 0;
		// проходимся по матрице
		for (int i = y - 1; i <= y + 1; i++) {

			for (int j = x - 1; j <= x + 1; j++) {

				if (i >= 0 && i < map.height && j >= 0 && j < map.width) {

					if (!(i == y && j == x)) {

						max_size++;
						// если ячейка помечена флагом
						if (map.get_char_at(i, j) == 'F' || map.get_char_at(i, j) == 'f') {
							// иницилизируем структуру ячейки
							Cell flagged;
							flagged.value = 'F';
							flagged.y = i;
							flagged.x = j;
							// добавляем в конец
							flagged_cells.push_back(flagged);
						}
					}
				}
			}
		}
		// возвращаем вектор ячеек
		return flagged_cells;
	}
	// метод получения скрытых ячеек вокруг координаты
	vector<Cell> get_hidden_cells(Map map, int y, int x) {
		// создаем вектор
		vector<Cell> hidden_cells;
		// проходимся по матрице
		for (int i = y - 1; i <= y + 1; i++) {

			for (int j = x - 1; j <= x + 1; j++) {

				if (i >= 0 && i < map.height && j >= 0 && j < map.width) {

					if (!(i == y && j == x)) {

						if (map.get_char_at(i, j) == '?') {
							// создаем переменную ячейки
							Cell hidden;
							hidden.value = '?';
							hidden.y = i;
							hidden.x = j;
							// добавляем в конец
							hidden_cells.push_back(hidden);
						}
					}
				}
			}
		}
		// возвращаем вектор
		return hidden_cells;
	}
};

// класс игравого менеджера
class GameManager
{
public:
	GameManager();
	~GameManager();
	// флаг конца игры
	bool is_game_over = false;
	// карты
	Map true_map, hidden_map, checked_map;
	Renderer renderer;
	// переменные для поля
	int field_width;
	int field_height;
	int mine_num;
	int flag_left;

	HANDLE hStdin;
	DWORD fdwSaveOldMode;
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf;
	int counter = 0;
	// флаг нажатия
	bool clicked = false;
	// флаг выхода
	bool exit = false;
	// флаг перезапуска 
	bool restart = false;
	// флаг начала игры
	bool begin_game = false;
	// строчка уровня сложности
	string level;
	// переменная начала игры
	int start_time;
	// переменная прошедшего времеи
	int elapsed_time;
	// вектор открытых ячеек
	vector<Cell> all_opened_cells;
	// метод иницилизирующий все параметры перед началом игры
	void init_game() {

		srand(time(NULL));
		// запоминаем время 
		start_time = clock();

		flag_left = mine_num;

		restart = false;
		is_game_over = false;
		begin_game = false;
		// очищаем вектор
		all_opened_cells.clear();
		// устанавливаем значения для карт
		true_map.set_size(field_height, field_width);
		hidden_map.set_size(field_height, field_width);
		checked_map.set_size(field_height, field_width);
		// делаем расстановку
		true_map.set_random_map(mine_num);
		// заполняем карту вопросами
		hidden_map.fill_map_with('?');
		// заставляем карту пробелами
		checked_map.fill_map_with(' ');

		hStdin = GetStdHandle(STD_INPUT_HANDLE);
		GetConsoleMode(hStdin, &fdwSaveOldMode);
		fdwMode = ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
		SetConsoleMode(hStdin, fdwMode);
		// прошедшее время
		elapsed_time = (clock() - start_time) / (CLOCKS_PER_SEC);
	}
	// установка кастомного поля
	void set_custom_game(int h, int w, int mn) {
		// установка кастомных значений поля
		field_height = h;
		field_width = w;
		mine_num = mn;
		// переделка консоли под заданные параметры
		prepare_window(h * 20 + 100, w * 20 + 350);
	}
	// установка поля по уровню сложности
	void set_game_by_level(string lv) {
		// уровень сложности
		level = lv;
		// если "новичок"
		if (lv == "Новичок") {
			
			field_height = 15;
			field_width = 20;
			mine_num = 35;
			prepare_window(392, 650);
		}
		// если "средний"
		else if (lv == "Средний") {

			field_height = 20;
			field_width = 30;
			mine_num = 95;
			prepare_window(472, 780);
		}
		// если "эксперт"
		else if (lv == "Эксперт") {

			field_height = 25;
			field_width = 45;
			mine_num = 185;
			prepare_window(555, 1010);
		}
	}
	// функция проверки поля
	void check_way() {
		// выводим карту
		renderer.print_map(hidden_map);
		// переходим в начало поля
		go_to_x_y(field_height + 4, 0);
		renderer.colorize('F');
		// выводим надпись
		cout << "Сканирование...                          ";
		renderer.colorize(); 

		go_to_x_y(field_height + 5, 0);
		cout << "                                            ";
		// иницилизируем нашего бота
		AutoSolver solver;
		// получаем вектор значений всех клеток
		vector<Cell> valued_cells = solver.get_all_valued_cells(hidden_map);
		// проходимся по ним
		for (int i = 0; i < valued_cells.size(); i++) {
			// флаг проверки
			bool checked = false;
			// проходим по всем открытым
			for (int j = 0; j < all_opened_cells.size(); j++) {
				if (all_opened_cells[j].value == valued_cells[i].value)
					if (all_opened_cells[j].y == valued_cells[i].y)
						if (all_opened_cells[j].y == valued_cells[i].y) {
							// если тикущая ячейка уже была открыта
							// ставим флаг true
							checked = true;
							break;
						}
			}
			// если эта ячейка не была открыта
			if (!checked) {

				int y = valued_cells[i].y;
				int x = valued_cells[i].x;
				int val = solver.get_val_of(valued_cells[i].value);

				int max_size;
				// получаем открытые и помеченные ячейки вокруг ячейки
				vector<Cell> hidden = solver.get_hidden_cells(hidden_map, y, x);
				vector<Cell> flagged = solver.get_flagged_cells(hidden_map, y, x, max_size);
				// если ячейка с числом
				if (val > 0 && hidden.size() < 8) {
					// если есть скрытые
					if (hidden.size() > 0) {
						// если значение равно количеству помеченных ячеек или максимальное значение - помеченные равно 1
						if (val == flagged.size() || max_size - flagged.size() == 1) {
							// открываем скрытые ячейки вокруг
							for (int k = 0; k < hidden.size(); k++) open_cell(hidden[k].y, hidden[k].x);
							// перепечатываем карту
							renderer.print_map(hidden_map);
						}
						// очищаем вектора
						hidden.clear();
						flagged.clear();
						// получаем скрытые и помеченные
						hidden = solver.get_hidden_cells(hidden_map, y, x);
						flagged = flagged = solver.get_flagged_cells(hidden_map, y, x, max_size);
						// если значение - помеченные равно скрытым
						if (val - flagged.size() == hidden.size()) {
							go_to_x_y(field_height + 4, 0);
							// помечаем остальные
							for (int k = 0; k < hidden.size(); k++) flag_cell(hidden[k].y, hidden[k].x);
							// перепечатываем поле
							renderer.print_map(hidden_map);
							// продолжаем поиск пути
							check_way();
						}
					}
				}
			}
		}

			go_to_x_y(field_height + 4, 0);
			cout << "               ";
			// выводим время
			elapsed_time = (clock() - start_time) / (CLOCKS_PER_SEC);
			show_ui();
	}
	// функция авто игры
	void auto_play() {
		// запускаем цикл
		while (true) {
			// очщаем консоль
			system("cls");
			// создаем игру
			init_game();
			// выводим меню игры
			show_ui();
			// печатаем карту
			renderer.print_map(hidden_map);
			// запускаем время
			start_time = clock();
			// засыпаем на секунду
			Sleep(1000);
			// создаем бота
			AutoSolver solver;
			// получаем все скрытые поля
			vector<Cell> hidden_cells = solver.get_all_hidden_cells(hidden_map);
			// получаем рандомную ячейку
			int id = rand() % hidden_cells.size();
			// открывем ее
			open_cell(hidden_cells[id].y, hidden_cells[id].x);
			// перепечатываем поле
			renderer.print_map(hidden_map);
			Sleep(10);
			// пока игра не закончена
			while (!is_game_over) {
				// получаем прошедшее время
				elapsed_time = (clock() - start_time) / (CLOCKS_PER_SEC);
				// выводим менб игры
				show_ui();

				ReadConsoleInput(hStdin, &irInBuf, 1, &cNumRead);
				// отслеживаем нажатие клавиш
				switch (irInBuf.EventType) {
				case KEY_EVENT:
					if (irInBuf.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
						exit = true;
						goto end;
					}
				}
				// проверка пути
				check_way();

				go_to_x_y(field_height + 5, 0);
				renderer.colorize('F');
				cout << "Нет никакой возможности выбрать случайную позу...";
				renderer.colorize();
				// получаем все скрытые ячейки
				hidden_cells = solver.get_all_hidden_cells(hidden_map);
				// если они есть
				if (hidden_cells.size() > 0) {
					// получаем  рандомную
					id = rand() % hidden_cells.size();
					// открываем ее
					open_cell(hidden_cells[id].y, hidden_cells[id].x);
					renderer.print_map(hidden_map);
				}
				// проверка конца игры
				// если флаг конца игры фолз и флагов больше не осталось
				if (!is_game_over && flag_left == 0) {
					go_to_x_y(field_height + 4, 0);
					renderer.colorize('2');
					// выводим сообщение о победе бота
					cout << "               БОТ ПОБЕДИЛ                " << endl;
					cout << "                                                       ";
					while (true) {
						if (GetKeyState(VK_ESCAPE) & 0x8000) goto end;
						else if (GetKeyState(VK_RETURN) & 0x8000) goto next;
					}
				}
			}
			// если бот наткнулся на мину, то бот проиграл
			if (is_game_over) {
				game_over();
				renderer.print_map(true_map);
				while (true) {
					if (GetKeyState(VK_ESCAPE) & 0x8000) goto end;
					else if (GetKeyState(VK_RETURN) & 0x8000) goto next;
				}
			}
		next: {}
		}	
		end:
		system("cls");
	}
	// функция игры челоовека
	void hooman_play() {
		// запускаем цикл
		while (true) {
			// создаем игру
			init_game();
			// выводим менб игры
			show_ui();
			// печатаем поле
			renderer.print_map(hidden_map);
			// пока не проиграл
			while (!is_game_over) {
				// получаем прошедшее время
				if (begin_game) elapsed_time = (clock() - start_time) / (CLOCKS_PER_SEC);
				// выводим меню
				show_ui();
				// проверяем ввод пльзователя
				check_input();
				// если был клик
				if (clicked) {
					// перепечатываем карту
					renderer.print_map(hidden_map);
					clicked = false;
					// если не начало игры
					if (!begin_game) {
						// получаем начало игры
						start_time = clock();
						// ставим флаг что игра началась
						begin_game = true;
					}
				}
				// если был перезапуск то переходим в учаток кода next
				if (restart) goto next;
				// если был выход переходим в учаток кода out
				if (exit) goto out;
				// если игрок победил
				if (check_win()) {
					//  записываем новый рекорд
					set_new_high_score(level, elapsed_time);

					renderer.colorize('2');
					go_to_x_y(true_map.height + 4, true_map.width - 6);
					cout << "ХОРОШО ВЫ ПОБЕДИЛИ :((" << endl;
					renderer.colorize('F');
					go_to_x_y(true_map.height + 5, true_map.width - 17);
					cout << "Пожалуйста нажмите ENTER что перезапустить игру";
					go_to_x_y(true_map.height + 6, true_map.width - 12);
					cout << "или нажмите ESC что выйти...";
				}
			}
			// заканчиваем игру
			game_over();
			// если был перезапуск
		check_restart:
			while (true) {
				// проверка ввода
				check_input();
				// если был перезапуск
				if (restart) {
					// и конец игры
					if (is_game_over) system("cls");
					goto next;
				}
				// если был выход
				if (exit) goto out;
			}
			// выход
		out: { if (exit) break; }
			// перезапуск
		next: {}
		}
		system("cls");
	}
	// пометка ячейки флагом
	void flag_cell(int y, int x) {
		// ставим флаг
		if (hidden_map.get_char_at(y, x) != 'F') {
			hidden_map.set_char(y, x, 'F');
			flag_left--;
		}
		// убираем флаг
		else {
			hidden_map.set_char(y, x, '?');
			flag_left++;
		}
	}
	// открываем чейку
	void open_cell(int y, int x) {
		// если ячейка не флаг и не пустая
		if (hidden_map.get_char_at(y, x) != 'F' && hidden_map.get_char_at(y, x) != ' ') {
			clicked = true;
			// если тут мина
			if (true_map.get_char_at(y, x) == 'M') {
				// заканчиваем игру
				is_game_over = true;
				true_map.set_char(y, x, 'm');
			}
			// иначе
			else oil_spills(y, x);
		}
	}

private:
	// устанавливаем новый лучший рекорд
	void set_new_high_score(string level, int score) {
		// открываем файл
		HighScore hc = read_high_score();
		ofstream output("highscore.txt", ios::out | ios::trunc);
		// если новичок
		if (level == "Новичок") {

			if (hc.beginner_score != 0) {
				if (score < hc.beginner_score) hc.beginner_score = score;
			}
			else hc.beginner_score = score;
		}
		// если средний
		else if (level == "Средний") {

			if (hc.inter_score != 0) {
				if (score < hc.inter_score) hc.inter_score = score;
			}
			else hc.inter_score = score;
		}
		// если эксперт
		else if (level == "Эксперт") {

			if (hc.expert_score != 0) {
				if (score < hc.expert_score) hc.expert_score = score;
			}
			else hc.expert_score = score;
		}
		output << hc.beginner_score << " " << hc.inter_score << " " << hc.expert_score;
	}
	// проверка на победу
	bool check_win() {

		bool is_win = true;
		// проходим по полю
		for (int i = 0; i < field_height; i++) {

			for (int j = 0; j < field_width; j++) {
				// если есть мина и она не помечена
				if (true_map.get_char_at(i, j) == 'M') {

					if (hidden_map.get_char_at(i, j) != 'F') {
						// флаг победы не ставим
						is_win = false;
						break;
					}
				}
			}
		}
		// фозвращаем флаг
		return is_win;
	}
	// проверка ввода
	void check_input() {

		int x; int y;

		ReadConsoleInput(hStdin, &irInBuf, 1, &cNumRead);
		
		switch (irInBuf.EventType) {
			// проверка ввод клавиатуры
		case KEY_EVENT:
			// если был нажат ESC
			if (irInBuf.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) exit = true;
			// если был нажат ENTER
			else if (irInBuf.Event.KeyEvent.wVirtualKeyCode == VK_RETURN) {
				Sleep(100);
				if (restart == false) restart = true;
			}
			break;
			// проверка ввода мышки
		case MOUSE_EVENT:

			if (!is_game_over) {
				MOUSE_EVENT_RECORD mer = irInBuf.Event.MouseEvent;

				switch (mer.dwEventFlags) {
				case 0:
					// если была нажата лкм
					if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
						x = mer.dwMousePosition.X;
						y = mer.dwMousePosition.Y;
						// полуение координат
						if (x % 2 == 0) {
							if (x >= 2 && x <= field_width * 2 && y >= 2 && y <= field_height + 2) {
								x = (x - 2) / 2;
								y = y - 3;
								// открываем ячейку
								open_cell(y, x);
							}
						}
					}
					// если была нажата пкм
					else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
						x = mer.dwMousePosition.X;
						y = mer.dwMousePosition.Y;
						// получение координат
						if (x % 2 == 0) {
							if (x >= 2 && x <= field_width * 2 && y >= 2 && y <= field_height + 2) {
								x = (x - 2) / 2;
								y = y - 3;
								clicked = true;
								// помечаем ячейку
								if (hidden_map.get_char_at(y, x) == '?' || hidden_map.get_char_at(y, x) == 'F') flag_cell(y, x);
							}
						}
					}
					break;
				default:
					break;
				}
			}
			break;

		case WINDOW_BUFFER_SIZE_EVENT:
			break;

		case FOCUS_EVENT:
			break;

		case MENU_EVENT:
			break;

		default:
			break;
		}
		FlushConsoleInputBuffer(hStdin);
	}
	// метод вывода игры
	void show_ui() {

		go_to_x_y(0, true_map.width - 6);
		renderer.colorize('3');
		cout << "САПЕР" << endl;
		renderer.colorize('?');
		go_to_x_y(1, true_map.width - 17);

		go_to_x_y(2, true_map.width * 2 + 5);
		renderer.colorize('5');
		if (elapsed_time > 60) {

			int minutes = elapsed_time / 60;
			int seconds = elapsed_time % 60;
			if (minutes < 10) {
				cout << "Затраченное время: 0" << minutes << ":";
			}
			else {
				cout << "Затраченное время: " << minutes << ":";
			}
			if (seconds < 10) {
				cout << "0" << seconds << "    ";
			}
			else {
				cout << seconds << "    ";
			}
		}
		else {
			if (elapsed_time < 10) {
				cout << "Затраченное время: 00:0" << elapsed_time;
			}
			else {
				cout << "Затраченное время: 00:" << elapsed_time;
			}
		}

		go_to_x_y(3, true_map.width * 2 + 5);
		renderer.colorize('2'); cout << "Размер поля: " << field_width << "x" << field_height;
		go_to_x_y(4, true_map.width * 2 + 5);
		renderer.colorize('4'); cout << "Мин: " << true_map.count_this_element('M');
		go_to_x_y(5, true_map.width * 2 + 5);
		renderer.colorize('F'); cout << "Флагов: " << flag_left << "    ";

		go_to_x_y(7, true_map.width * 2 + 5);
		renderer.colorize('6'); cout << "Как играть?";
		go_to_x_y(8, true_map.width * 2 + 5);
		renderer.colorize('4'); cout << " - Левый клик чтобы открыть";
		go_to_x_y(9, true_map.width * 2 + 5);
		renderer.colorize('4'); cout << " - Правый клик чтобы поставить флаг";
		go_to_x_y(10, true_map.width * 2 + 5);
		renderer.colorize('4'); cout << " - Нажмите Enter чтобы перезапустить";
		go_to_x_y(11, true_map.width * 2 + 5);
		renderer.colorize('4'); cout << " - Нажмите ESC чтобы выйти";

		go_to_x_y(13, true_map.width * 2 + 5);
		renderer.colorize('2'); cout << "Примечание: ";
		go_to_x_y(14, true_map.width * 2 + 5);
		renderer.colorize('4'); cout << " - ";
		renderer.colorize('M'); cout << "M";
		renderer.colorize('4'); cout << ": Мина";

		go_to_x_y(15, true_map.width * 2 + 5);
		renderer.colorize('4'); cout << " - ";
		renderer.colorize('F'); cout << "F";
		renderer.colorize('4'); cout << ": Флаг";

		go_to_x_y(16, true_map.width * 2 + 5);
		renderer.colorize('4'); cout << " - ";
		renderer.colorize('f'); cout << "F";
		renderer.colorize('4'); cout << ": Ошибочный флаг";
	}
	// метод конца игры
	void game_over() {
		// проверка расстановки флагов
		for (int i = 0; i < true_map.height; i++) {

			for (int j = 0; j < true_map.width; j++) {

				if (hidden_map.get_char_at(i, j) != 'F') {
					hidden_map.set_char(i, j, true_map.get_char_at(i, j));
				}
				else {
					if (true_map.get_char_at(i, j) != 'M') {
						hidden_map.set_char(i, j, 'f');
					}
				}
			}
		}
		show_ui();
		renderer.print_map(hidden_map);
		renderer.colorize('3');
		go_to_x_y(true_map.height + 4, true_map.width - 14);
		cout << "   БУУМ!! ИГРА ОКОНЧЕНА!! :))" << endl;
		renderer.colorize('F');
		go_to_x_y(true_map.height + 5, true_map.width - 17);
		cout << "Пожалуйста нажмите ENTER чтобы перезапустить игру";
		go_to_x_y(true_map.height + 6, true_map.width - 12);
		cout << "или нажмите ESC чтобы выйти...";
	}
	// метод открытия всех пустых ячеек соедененных с открытой игроком
	void oil_spills(int y, int x) {

		checked_map.set_char(y, x, 'x');
		char c = true_map.get_char_at(y, x);

		if (c == ' ') {

			hidden_map.set_char(y, x, ' ');
			string s = to_string(y) + "-" + to_string(x) + "-v=" + c;

			if (x - 1 >= 0) {

				char tc = true_map.get_char_at(y, x - 1);
				char xc = checked_map.get_char_at(y, x - 1);
				char hc = hidden_map.get_char_at(y, x - 1);

				if (xc != 'x' && hc != 'F' && tc != 'M') oil_spills(y, x - 1);
			}
			if (x + 1 < hidden_map.width) {

				char tc = true_map.get_char_at(y, x + 1);
				char xc = checked_map.get_char_at(y, x + 1);
				char hc = hidden_map.get_char_at(y, x + 1);

				if (xc != 'x' && hc != 'F' && tc != 'M') oil_spills(y, x + 1);
			}
			if (y - 1 >= 0) {

				char tc = true_map.get_char_at(y - 1, x);
				char xc = checked_map.get_char_at(y - 1, x);
				char hc = hidden_map.get_char_at(y - 1, x);

				if (xc != 'x' && hc != 'F' && tc != 'M') oil_spills(y - 1, x);
			}
			if (y + 1 < hidden_map.height) {

				char tc = true_map.get_char_at(y + 1, x);
				char xc = checked_map.get_char_at(y + 1, x);
				char hc = hidden_map.get_char_at(y + 1, x);
				if (xc != 'x' && hc != 'F' && tc != 'M') oil_spills(y + 1, x);
			}
		}
		else hidden_map.set_char(y, x, c);
	}
};
GameManager::GameManager()
{
}
GameManager::~GameManager()
{
}
// класс меню
class Menu {

public:

	Renderer renderer;
	int choice;
	// вектор клавного меню
	vector<string> main_text = { "Играть", "Лучшие рекорды", "Автопрохождение", "Выход" };
	// вектор уровней сложности
	vector<string> level_text = { "Новичок", "Средний", "Эксперт", "Кастом" };

	Menu() {

		choice = 0;
	}
	// функция вывода банера игры
	void show_banner() {

		prepare_window(500, 400);
		go_to_x_y(0, 26 - 5);
		renderer.colorize('3');
		cout << "САПЕР" << endl;
		renderer.colorize('?');
		go_to_x_y(1, 24 - 17);
	}
	// функция вывода рекордов
	void show_high_score() {
		// вывод банера
		show_banner();

		HighScore hc;
		// получение рекордов
		hc = read_high_score();
		// вывод рекордов
		renderer.colorize('F');
		go_to_x_y(3, 0);
		cout << "==================================================" << endl;
		cout << "											" << endl;
		cout << "                    Рекорды:		" << endl;

		if (hc.beginner_score != 0) {
			cout << "	       Новичок: " << hc.beginner_score << endl;
		}
		else {
			cout << "	       Новичок: Нет рекорда" << endl;
		}

		if (hc.inter_score != 0) {
			cout << "	       Средний: " << hc.beginner_score << endl;
		}
		else {
			cout << "	       Средний: Нет рекорда" << endl;
		}

		if (hc.expert_score != 0) {
			cout << "	       Эксперт: " << hc.beginner_score << endl;
		}
		else {
			cout << "	       Эксперт: Нет рекорда" << endl;
		}

		cout << "											" << endl;
		cout << "==================================================";
		renderer.colorize();
	}

	void show_main() {
		// вывод банера
		show_banner();
		// вектор текста меню
		vector<string> text = main_text;
		// флаги клавиш
		bool gone_up = false;
		bool gone_down = false;
		bool entered = false;
		bool esc_ed = false;
		// флаги типа игры
		bool choice_level = false;
		bool choice_level_bot = false;
		// запускаем цикл
		while (true) {
			// если была нажата стрелка вверх
			if ((GetKeyState(VK_UP) & 1) != gone_up) {
				choice--;
				gone_up = !gone_up;
			}
			// если была нажата стрелка вниз
			else if ((GetKeyState(VK_DOWN) & 1) != gone_down) {
				choice++;
				gone_down = !gone_down;
			}
			// был нажат enter
			else if ((GetKeyState(VK_RETURN) & 1) != entered) {
				entered = !entered;
				// если было меню сложности для игры пользователя
				if (choice_level) {

					GameManager game_manager;
					// устанавливаем сложность по строке
					if (choice < 3) {
						game_manager.set_game_by_level(level_text[choice]);
					}
					// иначе сами задаем данные игры
					else {
						int h, w, mn;
						hide_cursor(false);
						renderer.colorize('6');
						go_to_x_y(9, 24 - 17);
						cout << "Введите ширину поля (> 15): "; cin >> w;
						go_to_x_y(10, 24 - 17);
						cout << "Введите высоту поля (> 15): "; cin >> h;
						go_to_x_y(11, 24 - 17);
						cout << "Введите количество мин (должно быть~" << (int)(w*h*0.16) << "): "; cin >> mn;
						renderer.colorize();
						hide_cursor(true);
						game_manager.set_custom_game(h, w, mn);
					}
					system("cls");
					// запускаем игру человеком
					game_manager.hooman_play();
					choice = 0;
					text = main_text;
					system("cls");
					choice_level = false;
				}
				// если была выбрана игра ботом
				else if (choice_level_bot) {
					GameManager game_manager;
					// устанавливаем уровень по строке
					if (choice < 3) {
						game_manager.set_game_by_level(level_text[choice]);
					}
					// или задаем вручную
					else {
						int h, w, mn;
						hide_cursor(false);
						renderer.colorize('6');
						go_to_x_y(9, 24 - 17);
						cout << "Введите ширину поля (> 15): "; cin >> w;
						go_to_x_y(10, 24 - 17);
						cout << "Введите высоту поля (> 15): "; cin >> h;
						go_to_x_y(11, 24 - 17);
						cout << "Введите количество мин (должно быть~" << (int)(w * h * 0.16) << "): "; cin >> mn;
						renderer.colorize();
						hide_cursor(true);
						game_manager.set_custom_game(h, w, mn);
					}
					system("cls");
					game_manager.auto_play();
					choice = 0;
					text = main_text;
					system("cls");
					choice_level_bot = false;
				}
				else {
					// если была выбрана игра человеком в главном меню
					if (choice == 0) {
						// ставим флаг
						system("cls");
						choice_level = true;
						// задаем новый текст меню
						text = level_text;
					}
					// если выбрали таблицу рекордов
					else if (choice == 1) {
						system("cls");
						while (true) {
							show_high_score();
							if (GetKeyState(VK_ESCAPE) & 0x8000) break;
						}
						system("cls");
					}
					// если была выбрана игра ботом
					else if (choice == 2) {
						// ставим флаг
						system("cls");
						choice_level_bot = true;
						// задаем новый текст меню
						text = level_text;						
					}
					// если был выбран выход
					else if (choice == 3) {
						goto end;
					}
				}
			}
			// если был нажат esc
			else if ((GetKeyState(VK_ESCAPE) & 1) != esc_ed) {
				esc_ed = !esc_ed;
				// задаем главный текст меню
				text = main_text;
				// убираем флаги
				if (choice_level) {
					system("cls");
					choice_level = false;
				}
				if (choice_level_bot) {
					system("cls");
					choice_level = false;
				}
			}

			if (choice < 0) {
				choice = text.size() - 1;
			}
			else if (choice > text.size() - 1) {
				choice = 0;
			}
			// вывод банера
			show_banner();
			// вывод текста
			for (int i = 0; i < text.size(); i++) {
				renderer.colorize('2');
				go_to_x_y(i * 2 + 3, 24 - text[i].length() / 2);
				if (choice == i) renderer.colorize('f');
				cout << text[i];
				renderer.colorize(' ');
			}
			// ловим значения ввода
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		}
	end: {}
	}
};

int main() {
	setlocale(0, "");
	Menu menu;
	menu.show_main();
	return 0;
}