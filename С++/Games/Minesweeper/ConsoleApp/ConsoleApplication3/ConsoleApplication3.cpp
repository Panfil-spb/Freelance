// ������������ ����������
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

// ������������ ������������ ����
using namespace std;

// ����� �����
class Map {
public:
	// ���������� ������ � ������
	int width, height;
	// ����� ��������� �������
	void set_size(int h, int w) {
		height = h;
		width = w;
	}
	// ����� �������� ��������� ��������
	int count_this_element(char ele) {
		int c = 0;
		// ���������� ��� �� �������
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				char ch = map_array[i][j];
				if (ch == 'm') ch = 'M';
				if (ch == ele) c++;
			}
		}
		// ���������� ����������
		return c;
	}
	// ����� ��������� ��� �� ����
	void lay_mine_field(int mine_number) {

		fill_map_with(' ');

		int total_cells = width * height;
		if (mine_number > total_cells) mine_number = total_cells;

		map_array.resize(height);

		int mine_count = 0;
		boolean re_gen = false;

	generate_mine:
		// ����������� ����
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
		// ��� ��� �� ����������� ���� � ������� �������
		// � ���������� ��� ������ ������� ���������� 
		if (mine_count < mine_number) {
			re_gen = true;
			// ��������� ����� � ���������
			goto generate_mine;
		}
	}
	// ����� ��������� ��������� �����
	void set_random_map(int mine_num) {
		// ���������� ����
		lay_mine_field(mine_num);
		char digit[] = { ' ','1','2','3','4','5','6' };
		// ���������� �� �����������
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				// ���� � ���������� �� ����
				if (map_array[y][x] != 'M') {
					int mine_count = 0;
					// ���������� ������ ���������� � ������� ���������� ���
					for (int i = y - 1; i <= y + 1; i++) {
						for (int j = x - 1; j <= x + 1; j++) {
							if (i >= 0 && i < height && j >= 0 && j < width) {
								if (map_array[i][j] == 'M') mine_count++;
							}
						}
					}
					// ������������� ��� ��������
					map_array[y][x] = digit[mine_count];
				}
			}
		}
	}
	// ����� �������� ����
	void fill_map_with(char c) {
		// ��������� ����� �� ������
		map_array.resize(height);
		for (int i = 0; i < height; i++) {
			// ��������� �� ������
			map_array[i].resize(width);
			// ��������� ���������
			for (int j = 0; j < width; j++) map_array[i][j] = c;
		}
	}
	// ����� ��������� �������� �� �����������
	char get_char_at(int y, int x) {
		if (y < map_array.size() && x < map_array[y].size()) return map_array[y][x];
	}
	// ����� ��������� �������� �� �����������
	void set_char(int y, int x, char c) {
		map_array[y][x] = c;
	}

private:
	// ������ �������� �������� ����
	// �� ���� ��� �������
	vector < vector<char> > map_array;
};
// ������� ������ ������� ������� �� � �
void go_to_x_y(int y, int x) {

	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
// ������� ������� �������
void hide_cursor(bool hide) {

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 25;
	cci.bVisible = !hide;
	SetConsoleCursorInfo(hStdout, &cci);
}
// ������� ���������� ����
void prepare_window(int y, int x) {
	// �������� �������
	HWND console = GetConsoleWindow();
	RECT r;
	//��������� ������� ������� �������
	GetWindowRect(console, &r); 
	MoveWindow(console, r.left, r.top, x, y, TRUE);
	// �������� ����� ���
	HWND scroll = GetConsoleWindow();
	ShowScrollBar(scroll, SB_BOTH, FALSE);

	hide_cursor(true);
}
// ����� ������ ����
class Renderer {

public:
	// ����� ������ ���������� ������ � ����������� �� �������
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
	// ����� ������ �����
	void print_map(Map map) {

		go_to_x_y(2, 0);
		for (int i = 0; i < map.width + 2; i++) {
			colorize('F');
			cout << "=" << " "; 
		}
		cout << endl;
		// ���������� �� ����, � �������� �������� ������� ����
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
// ��������� ������ ��������
struct HighScore {

	int beginner_score;
	int inter_score;
	int expert_score;
};
// ��������� ������
struct Cell {

	char value;
	int y;
	int x;
};
// ��������� ��������
struct Action {

	string type;
	vector<Cell> cells;
};
// ������� ������ ��������
HighScore read_high_score() {

	HighScore hc;
	ifstream input;
	// ��������� ����
	input.open("highscore.txt");
	// ���� �� ����� �����
	if (!input.eof()) {
		// ��������� ������
		input >> hc.beginner_score;
		input >> hc.inter_score;
		input >> hc.expert_score;
		// ���� �������� �������� ������ 0
		// �� �������� ��
		if (hc.beginner_score < 0) hc.beginner_score = 0;
		if (hc.inter_score < 0) hc.inter_score = 0;
		if (hc.expert_score < 0) hc.expert_score = 0;
	}
	// ���� ���� �� �������� �� �������� ��� ��������
	else {
		hc.beginner_score = 0;
		hc.inter_score = 0;
		hc.expert_score = 0;
	}
	// ��������� ����
	input.close();
	// ���������� ���������
	return hc;
}
// ����� ��� �������������� ����
class AutoSolver {

public:
	// ����� ��������� ���� ������� �����
	vector<Cell> get_all_hidden_cells(Map map) {
		// ������ �����
		vector<Cell> hidden_cells;
		// ��������� �� ����� ��� �� �������
		for (int i = 0; i < map.height; i++) {

			for (int j = 0; j < map.width; j++) {
				// ���� ������ ������
				if (map.get_char_at(i, j) == '?') {
					// ������������� ��
					Cell hidden_cell;
					hidden_cell.value = map.get_char_at(i, j);
					hidden_cell.y = i;
					hidden_cell.x = j;
					// ��������� � �����
					hidden_cells.push_back(hidden_cell);
				}
			}
		}
		// ���������� ��� ������ ������
		return hidden_cells;
	}
	// ����� ��������� ���� �������� �����
	vector<Cell> get_all_valued_cells(Map map) {
		// ������� ������ ������
		vector<Cell> valued_cells;
		// ���������� �� ����� ��� �� �������
		for (int i = 0; i < map.height; i++) {

			for (int j = 0; j < map.width; j++) {
				// �������� ��������
				int value = get_val_of(map.get_char_at(i, j));
				// ���� ��� ������ 0
				if (value > 0) {
					// ���������� ������
					Cell valued_cell;
					valued_cell.value = map.get_char_at(i, j);
					valued_cell.y = i;
					valued_cell.x = j;
					// ��������� � �����
					valued_cells.push_back(valued_cell);
				}
			}
		}
		// ���������� ������ ������
		return valued_cells;
	}
	// ����� ��������� ��������
	int get_val_of(char c) {
		// ���� ������ ���������� 0
		if (c == ' ') return 0;
		// ���� ������ ���� �� -1
		if (c == '?' || c == 'F' || c == 'f') return -1;
		// ���� �� �����
		// �� ���������� ���� ��������
		return c - '0';
	}
	// ����� ��������� ���������� ������ ����� ������ ����������
	vector<Cell> get_flagged_cells(Map map, int y, int x, int &max_size) {
		// ������������� ������
		vector<Cell> flagged_cells;
		max_size = 0;
		// ���������� �� �������
		for (int i = y - 1; i <= y + 1; i++) {

			for (int j = x - 1; j <= x + 1; j++) {

				if (i >= 0 && i < map.height && j >= 0 && j < map.width) {

					if (!(i == y && j == x)) {

						max_size++;
						// ���� ������ �������� ������
						if (map.get_char_at(i, j) == 'F' || map.get_char_at(i, j) == 'f') {
							// ������������� ��������� ������
							Cell flagged;
							flagged.value = 'F';
							flagged.y = i;
							flagged.x = j;
							// ��������� � �����
							flagged_cells.push_back(flagged);
						}
					}
				}
			}
		}
		// ���������� ������ �����
		return flagged_cells;
	}
	// ����� ��������� ������� ����� ������ ����������
	vector<Cell> get_hidden_cells(Map map, int y, int x) {
		// ������� ������
		vector<Cell> hidden_cells;
		// ���������� �� �������
		for (int i = y - 1; i <= y + 1; i++) {

			for (int j = x - 1; j <= x + 1; j++) {

				if (i >= 0 && i < map.height && j >= 0 && j < map.width) {

					if (!(i == y && j == x)) {

						if (map.get_char_at(i, j) == '?') {
							// ������� ���������� ������
							Cell hidden;
							hidden.value = '?';
							hidden.y = i;
							hidden.x = j;
							// ��������� � �����
							hidden_cells.push_back(hidden);
						}
					}
				}
			}
		}
		// ���������� ������
		return hidden_cells;
	}
};

// ����� �������� ���������
class GameManager
{
public:
	GameManager();
	~GameManager();
	// ���� ����� ����
	bool is_game_over = false;
	// �����
	Map true_map, hidden_map, checked_map;
	Renderer renderer;
	// ���������� ��� ����
	int field_width;
	int field_height;
	int mine_num;
	int flag_left;

	HANDLE hStdin;
	DWORD fdwSaveOldMode;
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf;
	int counter = 0;
	// ���� �������
	bool clicked = false;
	// ���� ������
	bool exit = false;
	// ���� ����������� 
	bool restart = false;
	// ���� ������ ����
	bool begin_game = false;
	// ������� ������ ���������
	string level;
	// ���������� ������ ����
	int start_time;
	// ���������� ���������� ������
	int elapsed_time;
	// ������ �������� �����
	vector<Cell> all_opened_cells;
	// ����� ��������������� ��� ��������� ����� ������� ����
	void init_game() {

		srand(time(NULL));
		// ���������� ����� 
		start_time = clock();

		flag_left = mine_num;

		restart = false;
		is_game_over = false;
		begin_game = false;
		// ������� ������
		all_opened_cells.clear();
		// ������������� �������� ��� ����
		true_map.set_size(field_height, field_width);
		hidden_map.set_size(field_height, field_width);
		checked_map.set_size(field_height, field_width);
		// ������ �����������
		true_map.set_random_map(mine_num);
		// ��������� ����� ���������
		hidden_map.fill_map_with('?');
		// ���������� ����� ���������
		checked_map.fill_map_with(' ');

		hStdin = GetStdHandle(STD_INPUT_HANDLE);
		GetConsoleMode(hStdin, &fdwSaveOldMode);
		fdwMode = ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
		SetConsoleMode(hStdin, fdwMode);
		// ��������� �����
		elapsed_time = (clock() - start_time) / (CLOCKS_PER_SEC);
	}
	// ��������� ���������� ����
	void set_custom_game(int h, int w, int mn) {
		// ��������� ��������� �������� ����
		field_height = h;
		field_width = w;
		mine_num = mn;
		// ��������� ������� ��� �������� ���������
		prepare_window(h * 20 + 100, w * 20 + 350);
	}
	// ��������� ���� �� ������ ���������
	void set_game_by_level(string lv) {
		// ������� ���������
		level = lv;
		// ���� "�������"
		if (lv == "�������") {
			
			field_height = 15;
			field_width = 20;
			mine_num = 35;
			prepare_window(392, 650);
		}
		// ���� "�������"
		else if (lv == "�������") {

			field_height = 20;
			field_width = 30;
			mine_num = 95;
			prepare_window(472, 780);
		}
		// ���� "�������"
		else if (lv == "�������") {

			field_height = 25;
			field_width = 45;
			mine_num = 185;
			prepare_window(555, 1010);
		}
	}
	// ������� �������� ����
	void check_way() {
		// ������� �����
		renderer.print_map(hidden_map);
		// ��������� � ������ ����
		go_to_x_y(field_height + 4, 0);
		renderer.colorize('F');
		// ������� �������
		cout << "������������...                          ";
		renderer.colorize(); 

		go_to_x_y(field_height + 5, 0);
		cout << "                                            ";
		// ������������� ������ ����
		AutoSolver solver;
		// �������� ������ �������� ���� ������
		vector<Cell> valued_cells = solver.get_all_valued_cells(hidden_map);
		// ���������� �� ���
		for (int i = 0; i < valued_cells.size(); i++) {
			// ���� ��������
			bool checked = false;
			// �������� �� ���� ��������
			for (int j = 0; j < all_opened_cells.size(); j++) {
				if (all_opened_cells[j].value == valued_cells[i].value)
					if (all_opened_cells[j].y == valued_cells[i].y)
						if (all_opened_cells[j].y == valued_cells[i].y) {
							// ���� ������� ������ ��� ���� �������
							// ������ ���� true
							checked = true;
							break;
						}
			}
			// ���� ��� ������ �� ���� �������
			if (!checked) {

				int y = valued_cells[i].y;
				int x = valued_cells[i].x;
				int val = solver.get_val_of(valued_cells[i].value);

				int max_size;
				// �������� �������� � ���������� ������ ������ ������
				vector<Cell> hidden = solver.get_hidden_cells(hidden_map, y, x);
				vector<Cell> flagged = solver.get_flagged_cells(hidden_map, y, x, max_size);
				// ���� ������ � ������
				if (val > 0 && hidden.size() < 8) {
					// ���� ���� �������
					if (hidden.size() > 0) {
						// ���� �������� ����� ���������� ���������� ����� ��� ������������ �������� - ���������� ����� 1
						if (val == flagged.size() || max_size - flagged.size() == 1) {
							// ��������� ������� ������ ������
							for (int k = 0; k < hidden.size(); k++) open_cell(hidden[k].y, hidden[k].x);
							// �������������� �����
							renderer.print_map(hidden_map);
						}
						// ������� �������
						hidden.clear();
						flagged.clear();
						// �������� ������� � ����������
						hidden = solver.get_hidden_cells(hidden_map, y, x);
						flagged = flagged = solver.get_flagged_cells(hidden_map, y, x, max_size);
						// ���� �������� - ���������� ����� �������
						if (val - flagged.size() == hidden.size()) {
							go_to_x_y(field_height + 4, 0);
							// �������� ���������
							for (int k = 0; k < hidden.size(); k++) flag_cell(hidden[k].y, hidden[k].x);
							// �������������� ����
							renderer.print_map(hidden_map);
							// ���������� ����� ����
							check_way();
						}
					}
				}
			}
		}

			go_to_x_y(field_height + 4, 0);
			cout << "               ";
			// ������� �����
			elapsed_time = (clock() - start_time) / (CLOCKS_PER_SEC);
			show_ui();
	}
	// ������� ���� ����
	void auto_play() {
		// ��������� ����
		while (true) {
			// ������ �������
			system("cls");
			// ������� ����
			init_game();
			// ������� ���� ����
			show_ui();
			// �������� �����
			renderer.print_map(hidden_map);
			// ��������� �����
			start_time = clock();
			// �������� �� �������
			Sleep(1000);
			// ������� ����
			AutoSolver solver;
			// �������� ��� ������� ����
			vector<Cell> hidden_cells = solver.get_all_hidden_cells(hidden_map);
			// �������� ��������� ������
			int id = rand() % hidden_cells.size();
			// �������� ��
			open_cell(hidden_cells[id].y, hidden_cells[id].x);
			// �������������� ����
			renderer.print_map(hidden_map);
			Sleep(10);
			// ���� ���� �� ���������
			while (!is_game_over) {
				// �������� ��������� �����
				elapsed_time = (clock() - start_time) / (CLOCKS_PER_SEC);
				// ������� ���� ����
				show_ui();

				ReadConsoleInput(hStdin, &irInBuf, 1, &cNumRead);
				// ����������� ������� ������
				switch (irInBuf.EventType) {
				case KEY_EVENT:
					if (irInBuf.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
						exit = true;
						goto end;
					}
				}
				// �������� ����
				check_way();

				go_to_x_y(field_height + 5, 0);
				renderer.colorize('F');
				cout << "��� ������� ����������� ������� ��������� ����...";
				renderer.colorize();
				// �������� ��� ������� ������
				hidden_cells = solver.get_all_hidden_cells(hidden_map);
				// ���� ��� ����
				if (hidden_cells.size() > 0) {
					// ��������  ���������
					id = rand() % hidden_cells.size();
					// ��������� ��
					open_cell(hidden_cells[id].y, hidden_cells[id].x);
					renderer.print_map(hidden_map);
				}
				// �������� ����� ����
				// ���� ���� ����� ���� ���� � ������ ������ �� ��������
				if (!is_game_over && flag_left == 0) {
					go_to_x_y(field_height + 4, 0);
					renderer.colorize('2');
					// ������� ��������� � ������ ����
					cout << "               ��� �������                " << endl;
					cout << "                                                       ";
					while (true) {
						if (GetKeyState(VK_ESCAPE) & 0x8000) goto end;
						else if (GetKeyState(VK_RETURN) & 0x8000) goto next;
					}
				}
			}
			// ���� ��� ��������� �� ����, �� ��� ��������
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
	// ������� ���� ���������
	void hooman_play() {
		// ��������� ����
		while (true) {
			// ������� ����
			init_game();
			// ������� ���� ����
			show_ui();
			// �������� ����
			renderer.print_map(hidden_map);
			// ���� �� ��������
			while (!is_game_over) {
				// �������� ��������� �����
				if (begin_game) elapsed_time = (clock() - start_time) / (CLOCKS_PER_SEC);
				// ������� ����
				show_ui();
				// ��������� ���� �����������
				check_input();
				// ���� ��� ����
				if (clicked) {
					// �������������� �����
					renderer.print_map(hidden_map);
					clicked = false;
					// ���� �� ������ ����
					if (!begin_game) {
						// �������� ������ ����
						start_time = clock();
						// ������ ���� ��� ���� ��������
						begin_game = true;
					}
				}
				// ���� ��� ���������� �� ��������� � ������ ���� next
				if (restart) goto next;
				// ���� ��� ����� ��������� � ������ ���� out
				if (exit) goto out;
				// ���� ����� �������
				if (check_win()) {
					//  ���������� ����� ������
					set_new_high_score(level, elapsed_time);

					renderer.colorize('2');
					go_to_x_y(true_map.height + 4, true_map.width - 6);
					cout << "������ �� �������� :((" << endl;
					renderer.colorize('F');
					go_to_x_y(true_map.height + 5, true_map.width - 17);
					cout << "���������� ������� ENTER ��� ������������� ����";
					go_to_x_y(true_map.height + 6, true_map.width - 12);
					cout << "��� ������� ESC ��� �����...";
				}
			}
			// ����������� ����
			game_over();
			// ���� ��� ����������
		check_restart:
			while (true) {
				// �������� �����
				check_input();
				// ���� ��� ����������
				if (restart) {
					// � ����� ����
					if (is_game_over) system("cls");
					goto next;
				}
				// ���� ��� �����
				if (exit) goto out;
			}
			// �����
		out: { if (exit) break; }
			// ����������
		next: {}
		}
		system("cls");
	}
	// ������� ������ ������
	void flag_cell(int y, int x) {
		// ������ ����
		if (hidden_map.get_char_at(y, x) != 'F') {
			hidden_map.set_char(y, x, 'F');
			flag_left--;
		}
		// ������� ����
		else {
			hidden_map.set_char(y, x, '?');
			flag_left++;
		}
	}
	// ��������� �����
	void open_cell(int y, int x) {
		// ���� ������ �� ���� � �� ������
		if (hidden_map.get_char_at(y, x) != 'F' && hidden_map.get_char_at(y, x) != ' ') {
			clicked = true;
			// ���� ��� ����
			if (true_map.get_char_at(y, x) == 'M') {
				// ����������� ����
				is_game_over = true;
				true_map.set_char(y, x, 'm');
			}
			// �����
			else oil_spills(y, x);
		}
	}

private:
	// ������������� ����� ������ ������
	void set_new_high_score(string level, int score) {
		// ��������� ����
		HighScore hc = read_high_score();
		ofstream output("highscore.txt", ios::out | ios::trunc);
		// ���� �������
		if (level == "�������") {

			if (hc.beginner_score != 0) {
				if (score < hc.beginner_score) hc.beginner_score = score;
			}
			else hc.beginner_score = score;
		}
		// ���� �������
		else if (level == "�������") {

			if (hc.inter_score != 0) {
				if (score < hc.inter_score) hc.inter_score = score;
			}
			else hc.inter_score = score;
		}
		// ���� �������
		else if (level == "�������") {

			if (hc.expert_score != 0) {
				if (score < hc.expert_score) hc.expert_score = score;
			}
			else hc.expert_score = score;
		}
		output << hc.beginner_score << " " << hc.inter_score << " " << hc.expert_score;
	}
	// �������� �� ������
	bool check_win() {

		bool is_win = true;
		// �������� �� ����
		for (int i = 0; i < field_height; i++) {

			for (int j = 0; j < field_width; j++) {
				// ���� ���� ���� � ��� �� ��������
				if (true_map.get_char_at(i, j) == 'M') {

					if (hidden_map.get_char_at(i, j) != 'F') {
						// ���� ������ �� ������
						is_win = false;
						break;
					}
				}
			}
		}
		// ���������� ����
		return is_win;
	}
	// �������� �����
	void check_input() {

		int x; int y;

		ReadConsoleInput(hStdin, &irInBuf, 1, &cNumRead);
		
		switch (irInBuf.EventType) {
			// �������� ���� ����������
		case KEY_EVENT:
			// ���� ��� ����� ESC
			if (irInBuf.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) exit = true;
			// ���� ��� ����� ENTER
			else if (irInBuf.Event.KeyEvent.wVirtualKeyCode == VK_RETURN) {
				Sleep(100);
				if (restart == false) restart = true;
			}
			break;
			// �������� ����� �����
		case MOUSE_EVENT:

			if (!is_game_over) {
				MOUSE_EVENT_RECORD mer = irInBuf.Event.MouseEvent;

				switch (mer.dwEventFlags) {
				case 0:
					// ���� ���� ������ ���
					if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
						x = mer.dwMousePosition.X;
						y = mer.dwMousePosition.Y;
						// �������� ���������
						if (x % 2 == 0) {
							if (x >= 2 && x <= field_width * 2 && y >= 2 && y <= field_height + 2) {
								x = (x - 2) / 2;
								y = y - 3;
								// ��������� ������
								open_cell(y, x);
							}
						}
					}
					// ���� ���� ������ ���
					else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
						x = mer.dwMousePosition.X;
						y = mer.dwMousePosition.Y;
						// ��������� ���������
						if (x % 2 == 0) {
							if (x >= 2 && x <= field_width * 2 && y >= 2 && y <= field_height + 2) {
								x = (x - 2) / 2;
								y = y - 3;
								clicked = true;
								// �������� ������
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
	// ����� ������ ����
	void show_ui() {

		go_to_x_y(0, true_map.width - 6);
		renderer.colorize('3');
		cout << "�����" << endl;
		renderer.colorize('?');
		go_to_x_y(1, true_map.width - 17);

		go_to_x_y(2, true_map.width * 2 + 5);
		renderer.colorize('5');
		if (elapsed_time > 60) {

			int minutes = elapsed_time / 60;
			int seconds = elapsed_time % 60;
			if (minutes < 10) {
				cout << "����������� �����: 0" << minutes << ":";
			}
			else {
				cout << "����������� �����: " << minutes << ":";
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
				cout << "����������� �����: 00:0" << elapsed_time;
			}
			else {
				cout << "����������� �����: 00:" << elapsed_time;
			}
		}

		go_to_x_y(3, true_map.width * 2 + 5);
		renderer.colorize('2'); cout << "������ ����: " << field_width << "x" << field_height;
		go_to_x_y(4, true_map.width * 2 + 5);
		renderer.colorize('4'); cout << "���: " << true_map.count_this_element('M');
		go_to_x_y(5, true_map.width * 2 + 5);
		renderer.colorize('F'); cout << "������: " << flag_left << "    ";

		go_to_x_y(7, true_map.width * 2 + 5);
		renderer.colorize('6'); cout << "��� ������?";
		go_to_x_y(8, true_map.width * 2 + 5);
		renderer.colorize('4'); cout << " - ����� ���� ����� �������";
		go_to_x_y(9, true_map.width * 2 + 5);
		renderer.colorize('4'); cout << " - ������ ���� ����� ��������� ����";
		go_to_x_y(10, true_map.width * 2 + 5);
		renderer.colorize('4'); cout << " - ������� Enter ����� �������������";
		go_to_x_y(11, true_map.width * 2 + 5);
		renderer.colorize('4'); cout << " - ������� ESC ����� �����";

		go_to_x_y(13, true_map.width * 2 + 5);
		renderer.colorize('2'); cout << "����������: ";
		go_to_x_y(14, true_map.width * 2 + 5);
		renderer.colorize('4'); cout << " - ";
		renderer.colorize('M'); cout << "M";
		renderer.colorize('4'); cout << ": ����";

		go_to_x_y(15, true_map.width * 2 + 5);
		renderer.colorize('4'); cout << " - ";
		renderer.colorize('F'); cout << "F";
		renderer.colorize('4'); cout << ": ����";

		go_to_x_y(16, true_map.width * 2 + 5);
		renderer.colorize('4'); cout << " - ";
		renderer.colorize('f'); cout << "F";
		renderer.colorize('4'); cout << ": ��������� ����";
	}
	// ����� ����� ����
	void game_over() {
		// �������� ����������� ������
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
		cout << "   ����!! ���� ��������!! :))" << endl;
		renderer.colorize('F');
		go_to_x_y(true_map.height + 5, true_map.width - 17);
		cout << "���������� ������� ENTER ����� ������������� ����";
		go_to_x_y(true_map.height + 6, true_map.width - 12);
		cout << "��� ������� ESC ����� �����...";
	}
	// ����� �������� ���� ������ ����� ����������� � �������� �������
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
// ����� ����
class Menu {

public:

	Renderer renderer;
	int choice;
	// ������ �������� ����
	vector<string> main_text = { "������", "������ �������", "���������������", "�����" };
	// ������ ������� ���������
	vector<string> level_text = { "�������", "�������", "�������", "������" };

	Menu() {

		choice = 0;
	}
	// ������� ������ ������ ����
	void show_banner() {

		prepare_window(500, 400);
		go_to_x_y(0, 26 - 5);
		renderer.colorize('3');
		cout << "�����" << endl;
		renderer.colorize('?');
		go_to_x_y(1, 24 - 17);
	}
	// ������� ������ ��������
	void show_high_score() {
		// ����� ������
		show_banner();

		HighScore hc;
		// ��������� ��������
		hc = read_high_score();
		// ����� ��������
		renderer.colorize('F');
		go_to_x_y(3, 0);
		cout << "==================================================" << endl;
		cout << "											" << endl;
		cout << "                    �������:		" << endl;

		if (hc.beginner_score != 0) {
			cout << "	       �������: " << hc.beginner_score << endl;
		}
		else {
			cout << "	       �������: ��� �������" << endl;
		}

		if (hc.inter_score != 0) {
			cout << "	       �������: " << hc.beginner_score << endl;
		}
		else {
			cout << "	       �������: ��� �������" << endl;
		}

		if (hc.expert_score != 0) {
			cout << "	       �������: " << hc.beginner_score << endl;
		}
		else {
			cout << "	       �������: ��� �������" << endl;
		}

		cout << "											" << endl;
		cout << "==================================================";
		renderer.colorize();
	}

	void show_main() {
		// ����� ������
		show_banner();
		// ������ ������ ����
		vector<string> text = main_text;
		// ����� ������
		bool gone_up = false;
		bool gone_down = false;
		bool entered = false;
		bool esc_ed = false;
		// ����� ���� ����
		bool choice_level = false;
		bool choice_level_bot = false;
		// ��������� ����
		while (true) {
			// ���� ���� ������ ������� �����
			if ((GetKeyState(VK_UP) & 1) != gone_up) {
				choice--;
				gone_up = !gone_up;
			}
			// ���� ���� ������ ������� ����
			else if ((GetKeyState(VK_DOWN) & 1) != gone_down) {
				choice++;
				gone_down = !gone_down;
			}
			// ��� ����� enter
			else if ((GetKeyState(VK_RETURN) & 1) != entered) {
				entered = !entered;
				// ���� ���� ���� ��������� ��� ���� ������������
				if (choice_level) {

					GameManager game_manager;
					// ������������� ��������� �� ������
					if (choice < 3) {
						game_manager.set_game_by_level(level_text[choice]);
					}
					// ����� ���� ������ ������ ����
					else {
						int h, w, mn;
						hide_cursor(false);
						renderer.colorize('6');
						go_to_x_y(9, 24 - 17);
						cout << "������� ������ ���� (> 15): "; cin >> w;
						go_to_x_y(10, 24 - 17);
						cout << "������� ������ ���� (> 15): "; cin >> h;
						go_to_x_y(11, 24 - 17);
						cout << "������� ���������� ��� (������ ����~" << (int)(w*h*0.16) << "): "; cin >> mn;
						renderer.colorize();
						hide_cursor(true);
						game_manager.set_custom_game(h, w, mn);
					}
					system("cls");
					// ��������� ���� ���������
					game_manager.hooman_play();
					choice = 0;
					text = main_text;
					system("cls");
					choice_level = false;
				}
				// ���� ���� ������� ���� �����
				else if (choice_level_bot) {
					GameManager game_manager;
					// ������������� ������� �� ������
					if (choice < 3) {
						game_manager.set_game_by_level(level_text[choice]);
					}
					// ��� ������ �������
					else {
						int h, w, mn;
						hide_cursor(false);
						renderer.colorize('6');
						go_to_x_y(9, 24 - 17);
						cout << "������� ������ ���� (> 15): "; cin >> w;
						go_to_x_y(10, 24 - 17);
						cout << "������� ������ ���� (> 15): "; cin >> h;
						go_to_x_y(11, 24 - 17);
						cout << "������� ���������� ��� (������ ����~" << (int)(w * h * 0.16) << "): "; cin >> mn;
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
					// ���� ���� ������� ���� ��������� � ������� ����
					if (choice == 0) {
						// ������ ����
						system("cls");
						choice_level = true;
						// ������ ����� ����� ����
						text = level_text;
					}
					// ���� ������� ������� ��������
					else if (choice == 1) {
						system("cls");
						while (true) {
							show_high_score();
							if (GetKeyState(VK_ESCAPE) & 0x8000) break;
						}
						system("cls");
					}
					// ���� ���� ������� ���� �����
					else if (choice == 2) {
						// ������ ����
						system("cls");
						choice_level_bot = true;
						// ������ ����� ����� ����
						text = level_text;						
					}
					// ���� ��� ������ �����
					else if (choice == 3) {
						goto end;
					}
				}
			}
			// ���� ��� ����� esc
			else if ((GetKeyState(VK_ESCAPE) & 1) != esc_ed) {
				esc_ed = !esc_ed;
				// ������ ������� ����� ����
				text = main_text;
				// ������� �����
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
			// ����� ������
			show_banner();
			// ����� ������
			for (int i = 0; i < text.size(); i++) {
				renderer.colorize('2');
				go_to_x_y(i * 2 + 3, 24 - text[i].length() / 2);
				if (choice == i) renderer.colorize('f');
				cout << text[i];
				renderer.colorize(' ');
			}
			// ����� �������� �����
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