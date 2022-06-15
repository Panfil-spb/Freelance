#include <iostream>
#include <locale>
#include <windows.h>
#include <fstream>
#include <stddef.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;
// функция вывод надписи "морской бой"
int ZapisIroka()
{
    // берем символ под номером 254 из таблицы ASCII
    char k = 254;
    // вывод надписи
    printf("\t%c   %c %c%c%c %c%c%c %c%c%c %c %c %c%c%c %c  %c\n"
        , k, k, k, k, k, k, k, k, k, k, k, k, k, k, k, k, k, k);
    printf("\t%c%c %c%c %c %c %c %c %c   %c %c %c %c %c %c%c\n"
        , k, k, k, k, k, k, k, k, k, k, k, k, k, k, k, k);
    
    printf("\t%c %c %c %c %c %c%c%c %c   %c%c  %c %c %c%c %c\n"
        , k, k, k, k, k, k, k, k, k, k, k, k, k, k, k, k);

    printf("\t%c   %c %c%c%c %c   %c%c%c %c %c %c%c%c %c  %c\n\n"
        , k, k, k, k, k, k, k, k, k, k, k, k, k, k, k, k);
    // вызов паузы
    Sleep(1000);
    printf("\t\t%c%c%c %c%c%c %c  %c\n", k, k, k, k, k, k, k, k);

    printf("\t\t%c   %c %c %c  %c\n", k, k, k, k, k);
    
    printf("\t\t%c%c%c %c %c %c %c%c\n", k, k, k, k, k, k, k, k);
    
    printf("\t\t%c %c %c %c %c%c %c\n", k, k, k, k, k, k, k);
    
    printf("\t\t%c%c%c %c%c%c %c  %c", k, k, k, k, k, k, k, k);
    // вызов паузы
    Sleep(3000);
    // очистка экрана
    system("cls");
    // объявление переменной имени
    string Name;
    setlocale(0, "");
    // запрос имени
    printf("Введите ваше имя: ");
    cin >> Name;
    // объявляем переменную файла для записи
    ofstream fout;
    // открытие файла
    fout.open("last_players.txt", ofstream::app);
    // если файл не удалось открыть
    if (!fout.is_open())
    {
        // вывод уведомления об ошибке
        cout << "Не удалось записать игрока";
        // вывод паузы
        Sleep(1500);
        return 2;
    }
    // иначе 
    else
    {
        // записываем имя в файл
        fout << Name << endl;
        // закрываем файл
        fout.close();
    }
    return 0;
}
// функция вывод интерфейса
int Interfaces(bool* Winner, bool* Control,
    bool* GameStatus, bool* Popadanie, bool* Ext, bool* End)
{
    // присваивание переменным их начальное значение
    *Winner = false;
    *Control = true;
    *GameStatus = true;
    *Popadanie = true;
    *Ext = false;
    int i = 1;
    char k;
    // запрашиваем действия до тех пор пока "i" не равен "d"
    do
    {
        // выполнение действий в зависимости от значения переменной "i"
        switch (i)
        {
            // если значение равно 1
        case 1:
            // выполняем действия пока "i" равна "1"
            do
            {
                // очищаем консоль
                system("cls");
                // вывод меню
                printf("   |   ВВЕРХ<W> |\n");
                printf("   |   ВНИЗ<S>  |\n");
                printf("   | ВЫБРАТЬ<D> |\n\n");
                printf("    М   Е   Н   Ю   \n\n");
                printf("           | ИГРАТЬ<====\n\n");
                printf("   |   ИГРОКИ   |\n\n");
                printf("   |   ОБ ИГРЕ  |\n\n");
                printf("   |  В Ы Х О Д |\n\n");
                // запрос дейсвия
#pragma warning(disable : 4996)
                fflush(stdin);
                k = getch();
                // если введена "s" то
                if (k == 's')
                {
                    // "i" становиться 2
                    i = 2;
                }
                // если введена "w" то
                if (k == 'w')
                {
                    // "i" становиться 4
                    i = 4;
                }
                // если введена "d" то
                if (k == 'd')
                {
                    // "i" становиться 5
                    i = 5;
                }

            } while (i == 1);
            break;
        // если "i" равна 2
        case 2:
            // выполняем действия пока "i" равна "2"
            do
            {
                // очистка экрана
                system("cls");
                // вывод меню
                printf("   |   ВВЕРХ<W> |\n");
                printf("   |   ВНИЗ<S>  |\n");
                printf("   | ВЫБРАТЬ<D> |\n\n");
                printf("    М   Е   Н   Ю   \n\n");
                printf("   |    ИГРАТЬ  |\n\n");
                printf("           | ИГРОКИ<====\n\n");
                printf("   |   ОБ ИГРЕ  |\n\n");
                printf("   |  В Ы Х О Д |\n\n");
                // запрос ввода переменной
#pragma warning(disable : 4996)
                fflush(stdin);
                k = getch();
                // если введена "s" то
                if (k == 's')
                {
                    // "i" становиться 3
                    i = 3;
                    break;
                }
                // если введена "w" то
                if (k == 'w')
                {
                    // "i" становиться 1
                    i = 1;
                }
                // если введена "d" то
                if (k == 'd')
                {
                    // очистка экрана
                    system("cls");
                    // объявление переменной файла
                    ifstream fin;
                    // открытие файла на чтение
                    fin.open("last_players.txt");
                    // если файл не открыля
                    if (!fin.is_open())
                    {
                        // вывод сообщения об ошибке
                        cout << "Прошлые игроки не доступны";
                        return 8;
                    }
                    // иначе
                    else
                    {
                        // обявление переменной
                        string Str;
                        // пока не дошли до конца файла
                        while (!fin.eof())
                        {
                            // читаем строку
                            getline(fin, Str);
                            // выводим считаную строку
                            cout << Str << endl;
                        }
                        // закрываем файл
                        fin.close();
                    }
                    printf("|НАЗАД<A>|\n");
                    // запрашивать ввод пока не будет ввден "а"
                    do
                    {
                        k = getc(stdin);
                    } while (k != 'a');
                }
            } while (i == 2);
            break;
            // если "i" равна 3
        case 3:
            // выполняем действия пока "i" равна "3"
            do
            {
                // очистка экрана
                system("cls");
                // вывод меню
                printf("   |   ВВЕРХ<W> |\n");
                printf("   |   ВНИЗ<S>  |\n");
                printf("   | ВЫБРАТЬ<D> |\n\n");
                printf("    М   Е   Н   Ю   \n\n");
                printf("   |   ИГРАТЬ   |\n\n");
                printf("   |   ИГРОКИ   |\n\n");
                printf("           | ОБ ИГРЕ<====\n\n");
                printf("   |  В Ы Х О Д |\n\n");
                // запрос выбора
#pragma warning(disable : 4996)
                fflush(stdin);
                k = getch();
                // если введена "w" то
                if (k == 'w')
                {
                    // "i" становиться 1
                    i = 2;
                }
                // если введена "s" то
                if (k == 's')
                {
                    // "i" становиться 4
                    i = 4;
                }
                // если введена "d" то
                if (k == 'd')
                {
                    // очистка экрана
                    system("cls");
                    // вывод информации об игре
                    printf("В игру морской бой играют два человека, которые по очереди называют координаты кораблей на карте противника.\n");
                    printf("Если координаты заняты, то корабль или его часть топят, и пойманный имеет право сделать еще один ход.\n");
                    printf("Победитель - тот, кто первым потопит все 10 кораблей противника.\n");
                    printf("Проигравший имеет право попросить у соперника изучить игровое поле после окончания игры.\n");
                    printf("\n\n|НАЗАД<A>|\n");
                    // пока не будет введен "а"
                    do
                    {
                        // запрос ввода
                        k = getc(stdin);
                    } while (k != 'a');
                }
            } while (i == 3);
            break;
            // если "i" равна 4
        case 4:
            do
            {
                // очистка экрана
                system("cls");
                // вывод меню
                printf("   |   ВВЕРХ<W> |\n");
                printf("   |   ВНИЗ<S>  |\n");
                printf("   | ВЫБРАТЬ<D> |\n\n");
                printf("    М   Е   Н   Ю   \n\n");
                printf("   |   ИГРАТЬ   |\n\n");
                printf("   |   ИГРОКИ   |\n\n");
                printf("   |  ОБ ИГРЕ   |\n\n");
                printf("           | В Ы Х О Д <====\n\n");
                // запрос ввода
#pragma warning(disable : 4996)
                fflush(stdin);
                k = getch();
                // если введена "w" то
                if (k == 'w')
                {
                    // "i" становиться 3
                    i = 3;
                }
                // если введена "s" то
                if (k == 's')
                {
                    // "i" становиться 1
                    i = 1;
                }
                // если введена "d" то
                if (k == 'd')
                {
                    // очистка экрана
                    system("cls");
                    // присваиваем переменной конца игры значение тру
                    *End = true;
                    return 0;
                }
            } while (i == 4);
            break;
        // если введен пункт не из меню переходим в начало цикла
        default:
            break;
        }
    } while (i != 5);
    return 0;
}
// функция атаки игрока
int AttackPlayer(char Fake[10][10], char Real[10][10],
    bool* GameStatus, bool* Popadanie, bool* Ext)
{
    // объявление переменных
    int i;
    int j;
    char d;
    char I;
    char J;
    // выполняем цикл пока не будут введены корректные координаты ячейки игрока
    do
    {
        do
        {
            // запролс координат точек
            printf("Введите точку поля в формате (столбец);(строчка)\n");
            cin >> J;
            cin >> d;
            cin >> I;
            // если введен end
            if ((int(J) == int('e')) && (int(I) == int('d')) && (int(d) == int('n')))
            {
                // то присваиваем конец игры переменным отвечающим за ее состояние
                *GameStatus = false;
                *Popadanie = false;
                *Ext = true;
                // выходим из функции
                return 0;
            }
        } while ((J > 57) || (J < 48) || (I > 57)
            || (I < 48) || ((d != '#') && (d != ';')));
        // так как мы вводили символы то превращаем наши символы в числа
        j = (int)(J - '0');
        i = (int)(I - '0');
       
    } while ((i < 0) || (i > 9) || (j < 0) || (j > 9) || (Real[i][j] == 'X')
        || ((Fake[i][j] == '0') && (d != '#')));
    // если попадание пришлось по кораблю
    if (Real[i][j] == 'K')
    {
        // то ставим метки на полях что корабль ранен
        Fake[i][j] = 'X';
        Real[i][j] = 'X';
    }
    // иначе ставим что попадание пришлось мимо
    else
    {
        Fake[i][j] = '0';
        // ставим метку что промахнулись
        *Popadanie = false;
    }
    return 0;
}
// функция атаки компьютера
int AttackBot(char MyField[10][10], bool* Popadanie)
{
    // объявление переменных
    int i;
    int j;
    // установка работы функции рандома
    srand(time(0));
    // генерируем координаты пока не попадем в ячейку в которую не стреляли
    do
    {
        i = 0 + (rand() % 10);
        j = 0 + (rand() % 10);
    } while (MyField[i][j] == '0' || MyField[i][j] == 'X');
    // если попали по кораблю
    if (MyField[i][j] == 'K')
    {
        // ставим метку на поле что корабль ранен
        MyField[i][j] = 'X';
    }
    // иначе 
    else
    {
        // ставим метку что сюда уже стреляли
        MyField[i][j] = '0';
        // ставим метку что промахнулись
        *Popadanie = false;
    }
    // выход из функции
    return 0;
}
// функция проверки поля компьютера
int CheckBotField(char Real[10][10], char Fake[10][10],
    bool* Winner, bool* GameStatus, bool* Popadanie)
{
    int i;
    int j;
    int i0;
    int j0;
    int Counter = 0;
    // ходим по полю
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            // проверяем потоплен корабль или нет
            if ((Real[i - 1][j] != 'K') && (Real[i + 1][j] != 'K')
                && (Real[i + 1][j] != 'X') && (Real[i - 1][j] != 'X'))
            {
                // елси потоплен то ходим по ячейкам и заполняем их метками что туда стреляли
                if ((Real[i][j] == 'X') && (Real[i][j + 1] == 'X')
                    && (Real[i][j + 2] == 'X') && (Real[i][j + 3] == 'X'))
                {
                    i0 = i - 1;
                    j0 = j - 1;
                    
                    for (i0 = i - 1; i0 < i + 2; i0++)
                    {
                        for (j0 = j - 1; j0 < j + 5; j0++)
                        {
                            if ((i0 >= 0) && (i0 < 10) && (j0 >= 0)
                                && (j0 < 10) && (Real[i0][j0] != 'X'))
                            {
                                Fake[i0][j0] = '0';
                            }
                        }
                    }
                }
                // елси потоплен то ходим по ячейкам и заполняем их метками что туда стреляли
                if ((Real[i][j - 1] != 'X') && (Real[i][j - 1] != 'K') && (Real[i][j] == 'X')
                    && (Real[i][j + 1] == 'X') && (Real[i][j + 2] == 'X')
                    && (Real[i][j + 3] != 'K') && (Real[i][j + 3] != 'X'))
                {
                    i0 = i - 1;
                    j0 = j - 1;
                    for (i0 = i - 1; i0 < i + 2; i0++)
                    {
                        for (j0 = j - 1; j0 < j + 4; j0++)
                        {
                            if ((i0 >= 0) && (i0 < 10) && (j0 >= 0)
                                && (j0 < 10) && (Real[i0][j0] != 'X'))
                            {
                                Fake[i0][j0] = '0';
                            }
                        }
                    }

                }
                // елси потоплен то ходим по ячейкам и заполняем их метками что туда стреляли
                if ((Real[i][j - 1] != 'X') && (Real[i][j - 1] != 'K') && (Real[i][j] == 'X')
                    && (Real[i][j + 1] == 'X') && (Real[i][j + 2] != 'X')
                    && (Real[i][j + 2] != 'K'))
                {
                    i0 = i - 1;
                    j0 = j - 1;
                    for (i0 = i - 1; i0 < i + 2; i0++)
                    {
                        for (j0 = j - 1; j0 < j + 3; j0++)
                        {
                            if ((i0 >= 0) && (i0 < 10) && (j0 >= 0)
                                && (j0 < 10) && (Real[i0][j0] != 'X'))
                            {
                                Fake[i0][j0] = '0';
                            }
                        }
                    }
                }
                // елси потоплен то ходим по ячейкам и заполняем их метками что туда стреляли
                if ((Real[i][j - 1] != 'X') && (Real[i][j - 1] != 'K') && (Real[i][j] == 'X')
                    && (Real[i][j + 1] != 'K') && (Real[i][j + 1] != 'X'))
                {
                    i0 = i - 1;
                    j0 = j - 1;
                    for (i0 = i - 1; i0 < i + 2; i0++)
                    {
                        for (j0 = j - 1; j0 < j + 2; j0++)
                        {
                            if ((i0 >= 0) && (i0 < 10) && (j0 >= 0)
                                && (j0 < 10) && (Real[i0][j0] != 'X'))
                            {
                                Fake[i0][j0] = '0';
                            }
                        }
                    }
                }
            }

        }
    }
    // ходим по полю
    for (j = 0; j < 10; j++)
    {
        for (i = 0; i < 10; i++)
        {
            // проверяем потоплен корабль или нет
            if ((Real[i][j - 1] != 'K') && (Real[i][j + 1] != 'K'))
            {
                // елси потоплен то ходим по ячейкам и заполняем их метками что туда стреляли
                if ((Real[i][j] == 'X') && (Real[i + 1][j] == 'X')
                    && (Real[i + 2][j] == 'X') && (Real[i + 3][j] == 'X'))
                {
                    i0 = i - 1;
                    j0 = j - 1;
                    for (i0 = i - 1; i0 < i + 5; i0++)
                    {
                        for (j0 = j - 1; j0 < j + 2; j0++)
                        {
                            if ((i0 >= 0) && (i0 < 10) && (j0 >= 0)
                                && (j0 < 10) && (Real[i0][j0] != 'X'))
                            {
                                Fake[i0][j0] = '0';
                            }
                        }
                    }
                }
                // елси потоплен то ходим по ячейкам и заполняем их метками что туда стреляли
                if ((Real[i - 1][j] != 'X') && (Real[i - 1][j] != 'K')
                    && (Real[i][j] == 'X') && (Real[i + 1][j] == 'X')
                    && (Real[i + 2][j] == 'X') && (Real[i + 3][j] != 'K')
                    && (Real[i + 3][j] != 'X'))
                {
                    i0 = i - 1;
                    j0 = j - 1;
                    for (i0 = i - 1; i0 < i + 4; i0++)
                    {
                        for (j0 = j - 1; j0 < j + 2; j0++)
                        {
                            if ((i0 >= 0) && (i0 < 10) && (j0 >= 0)
                                && (j0 < 10) && (Real[i0][j0] != 'X'))
                            {
                                Fake[i0][j0] = '0';
                            }
                        }
                    }

                }
                // елси потоплен то ходим по ячейкам и заполняем их метками что туда стреляли
                if ((Real[i - 1][j] != 'X') && (Real[i - 1][j] != 'K')
                    && (Real[i][j] == 'X') && (Real[i + 1][j] == 'X')
                    && (Real[i + 2][j] != 'X') && (Real[i + 2][j] != 'K'))
                {
                    i0 = i - 1;
                    j0 = j - 1;
                    for (i0 = i - 1; i0 < i + 3; i0++)
                    {
                        for (j0 = j - 1; j0 < j + 2; j0++)
                        {
                            if ((i0 >= 0) && (i0 < 10) && (j0 >= 0)
                                && (j0 < 10) && (Real[i0][j0] != 'X'))
                            {
                                Fake[i0][j0] = '0';
                            }
                        }
                    }
                }

            }
        }
    }
    // считаем очки по поданиям по кораблям
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (Real[i][j] == 'X')
            {
                Counter++;
            }
        }
    }
    // если очков от 20 и больше
    if (Counter >= 20)
    {
        // то ставим пометку победы человека и конца игры
        *Winner = true;
        *GameStatus = false;
        *Popadanie = false;

    }
    return 0;
}
// функция проверки поля игрока
int CheckPlayerField(char MyField[10][10],
    bool* Winner, bool* GameStatus, bool* Popadanie)
{
    // объявление переменных
    int i;
    int j;
    int i0;
    int j0;
    int Counter = 0;
    // ходим по полю
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            // проверка потопленности корабля
            if ((MyField[i - 1][j] != 'K') && (MyField[i + 1][j] != 'K')
                && (MyField[i + 1][j] != 'X') && (MyField[i - 1][j] != 'X'))
            {
                // если корабль потоплен
                if ((MyField[i][j] == 'X') && (MyField[i][j + 1] == 'X')
                    && (MyField[i][j + 2] == 'X') && (MyField[i][j + 3] == 'X'))
                {
                    // ходим по полю и заполняем что вокруг стрелять нельзя
                    i0 = i - 1;
                    j0 = j - 1;
                    for (i0 = i - 1; i0 < i + 2; i0++)
                    {
                        for (j0 = j - 1; j0 < j + 5; j0++)
                        {
                            if ((i0 >= 0) && (i0 < 10) && (j0 >= 0)
                                && (j0 < 10) && (MyField[i0][j0] != 'X'))
                            {
                                MyField[i0][j0] = '0';
                            }
                        }
                    }
                }
                // если корабль потоплен
                if ((MyField[i][j - 1] != 'X') && (MyField[i][j - 1] != 'K')
                    && (MyField[i][j] == 'X') && (MyField[i][j + 1] == 'X')
                    && (MyField[i][j + 2] == 'X') && (MyField[i][j + 3] != 'K')
                    && (MyField[i][j + 3] != 'X'))
                {
                    // ходим по полю и заполняем что вокруг стрелять нельзя
                    i0 = i - 1;
                    j0 = j - 1;
                    for (i0 = i - 1; i0 < i + 2; i0++)
                    {
                        for (j0 = j - 1; j0 < j + 4; j0++)
                        {
                            if ((i0 >= 0) && (i0 < 10) && (j0 >= 0)
                                && (j0 < 10) && (MyField[i0][j0] != 'X'))
                            {
                                MyField[i0][j0] = '0';
                            }
                        }
                    }

                }
                // если корабль потоплен
                if ((MyField[i][j - 1] != 'X') && (MyField[i][j - 1] != 'K')
                    && (MyField[i][j] == 'X') && (MyField[i][j + 1] == 'X')
                    && (MyField[i][j + 2] != 'X') && (MyField[i][j + 2] != 'K'))
                {
                    // ходим по полю и заполняем что вокруг стрелять нельзя
                    i0 = i - 1;
                    j0 = j - 1;
                    for (i0 = i - 1; i0 < i + 2; i0++)
                    {
                        for (j0 = j - 1; j0 < j + 3; j0++)
                        {
                            if ((i0 >= 0) && (i0 < 10) && (j0 >= 0)
                                && (j0 < 10) && (MyField[i0][j0] != 'X'))
                            {
                                MyField[i0][j0] = '0';
                            }
                        }
                    }
                }
                // если корабль потоплен
                if ((MyField[i][j - 1] != 'X') && (MyField[i][j - 1] != 'K')
                    && (MyField[i][j] == 'X') && (MyField[i][j + 1] != 'K')
                    && (MyField[i][j + 1] != 'X'))
                {
                    // ходим по полю и заполняем что вокруг стрелять нельзя
                    i0 = i - 1;
                    j0 = j - 1;
                    for (i0 = i - 1; i0 < i + 2; i0++)
                    {
                        for (j0 = j - 1; j0 < j + 2; j0++)
                        {
                            if ((i0 >= 0) && (i0 < 10) && (j0 >= 0)
                                && (j0 < 10) && (MyField[i0][j0] != 'X'))
                            {
                                MyField[i0][j0] = '0';
                            }
                        }
                    }
                }
            }

        }
    }
    // ходим по полю
    for (j = 0; j < 10; j++)
    {
        for (i = 0; i < 10; i++)
        {
            // проверка потопленности корабля
            if ((MyField[i][j - 1] != 'K') && (MyField[i][j + 1] != 'K'))
            {
                // если корабль потоплен
                if ((MyField[i][j] == 'X') && (MyField[i + 1][j] == 'X')
                    && (MyField[i + 2][j] == 'X')
                    && (MyField[i + 3][j] == 'X'))
                {
                    // ходим по полю и заполняем что вокруг стрелять нельзя
                    i0 = i - 1;
                    j0 = j - 1;
                    for (i0 = i - 1; i0 < i + 5; i0++)
                    {
                        for (j0 = j - 1; j0 < j + 2; j0++)
                        {
                            if ((i0 >= 0) && (i0 < 10) && (j0 >= 0)
                                && (j0 < 10) && (MyField[i0][j0] != 'X'))
                            {
                                MyField[i0][j0] = '0';
                            }
                        }
                    }
                }
                // если корабль потоплен
                if ((MyField[i - 1][j] != 'X') && (MyField[i - 1][j] != 'K')
                    && (MyField[i][j] == 'X') && (MyField[i + 1][j] == 'X')
                    && (MyField[i + 2][j] == 'X') && (MyField[i + 3][j] != 'K')
                    && (MyField[i + 3][j] != 'X'))
                {
                    // ходим по полю и заполняем что вокруг стрелять нельзя
                    i0 = i - 1;
                    j0 = j - 1;
                    for (i0 = i - 1; i0 < i + 4; i0++)
                    {
                        for (j0 = j - 1; j0 < j + 2; j0++)
                        {
                            if ((i0 >= 0) && (i0 < 10) && (j0 >= 0)
                                && (j0 < 10) && (MyField[i0][j0] != 'X'))
                            {
                                MyField[i0][j0] = '0';
                            }
                        }
                    }

                }
                // если корабль потоплен
                if ((MyField[i - 1][j] != 'X') && (MyField[i - 1][j] != 'K')
                    && (MyField[i][j] == 'X') && (MyField[i + 1][j] == 'X')
                    && (MyField[i + 2][j] != 'X') && (MyField[i + 2][j] != 'K'))
                {
                    // ходим по полю и заполняем что вокруг стрелять нельзя
                    i0 = i - 1;
                    j0 = j - 1;
                    for (i0 = i - 1; i0 < i + 3; i0++)
                    {
                        for (j0 = j - 1; j0 < j + 2; j0++)
                        {
                            if ((i0 >= 0) && (i0 < 10) && (j0 >= 0)
                                && (j0 < 10) && (MyField[i0][j0] != 'X'))
                            {
                                MyField[i0][j0] = '0';
                            }
                        }
                    }
                }

            }
        }
    }
    // подсчет очков
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (MyField[i][j] == 'X')
            {
                Counter++;
            }
        }
    }
    // если очков от 20 и больше
    if (Counter >= 20)
    {
        // то ставим пометку победы человека и конца игры
        *Winner = false;
        *GameStatus = false;
        *Popadanie = false;
    }
    // выход из функции
    return 0;
}
// функция отрисовки полей
int Draw(char MyField[10][10], char Fake[10][10])
{
    // объявление переменных
    int i;
    int j;
    int n = 0;
    printf("#|0|1|2|3|4|5|6|7|8|9| ВАШЕ ПОЛЕ\n");
    // вывод поля игрока
    for (i = 0; i < 10; i++)
    {
        printf("%d", n);
        for (j = 0; j < 10; j++)
        {
            if (j == 9)
            {
                printf("|%c|", MyField[i][j]);
            }
            else
            {
                printf("|%c", MyField[i][j]);
            }
        }
        n++;
        printf("\n");
    }
    printf("\n\n");
    n = 0;
    // вывод поля компьютера
    printf("#|0|1|2|3|4|5|6|7|8|9| ВРАЖЕСКОЕ ПОЛЕ");
    printf("   ЕСЛИ ВЫ ХОТИТЕ ПОКИНУТЬ ИГРУ ВВЕДИТЕ end\n");
    // вывод поля противника
    for (i = 0; i < 10; i++)
    {
        printf("%d", n);
        for (j = 0; j < 10; j++)
        {
            if (j == 9)
            {
                printf("|%c|", Fake[i][j]);
            }
            else
            {
                printf("|%c", Fake[i][j]);
            }
        }
        n++;
        printf("\n");
    }
    return 0;
}
// функция заполнения полей
int Setup(char MyField[10][10], char Fake[10][10],
    char Real[10][10])
{
    // установка для рандома
    srand(time(0));
    // объявление переменных
    int i;
    int j;
    int k;
    int z;
    int p = 4;
    int a;
    // ходим по полю игрока и заполняем его пустыми элементами
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            MyField[i][j] = '*';
        }
    }
    // ходим по полю противника и заполняем его пустыми элементами
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            Fake[i][j] = '*';
        }
    }
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            Real[i][j] = '*';
        }
    }
    // пока p больше 0
    while (p > 0)
    {
        switch (p)
        {
        // ставим четырех палубник
        case 4:
            // координаты первой точки корабля
            i = 0 + (rand() % 9);
            j = 0 + (rand() % 9);
            // отвечающая за горизонталь или вертикаль расстановки
            k = 1 + (rand() % 2);
            switch (k)
            {
                // горизонталь
            case 1:
                z = j - p;
                // если z меньше 0
                if (z < 0)
                {
                    z = j + p;
                    // то продолжаем корабль вправо
                    while (j < z)
                    {
                        MyField[i][j] = 'K';
                        j++;
                    }
                }
                // иначе
                else
                {
                    z = j - p;
                    // продолжаем корабль влево
                    while (j > z)
                    {
                        MyField[i][j] = 'K';
                        j--;
                    }
                }

                break;
            // вертикаль
            default:
                z = i - p;
                // z меньше нуля
                if (z < 0)
                {
                    z = i + p;
                    // то продожаем корабль вниз
                    while (i < z)
                    {
                        MyField[i][j] = 'K';
                        i++;
                    }
                }
                // иначе
                else
                {
                    z = i - p;
                    // продолжем корабль вверх
                    while (i > z)
                    {
                        MyField[i][j] = 'K';
                        i--;
                    }
                }
                break;
            }
            // переход к трехпалубникам
            p--;
            break;
        // ставим трехпалубник
        case 3:
            // пока не поставим два трехпалубника
            for (a = 0; a < 2; a++)
            {
                // запрашиваем координаты пока они не будут корректны
                do
                {
                    // координаты первой точки корабля
                    i = 0 + (rand() % 9);
                    j = 0 + (rand() % 9);
                } while ((MyField[i][j] == 'K') || (MyField[i + 1][j] == 'K')
                    || (MyField[i - 1][j] == 'K') || (MyField[i][j - 1] == 'K')
                    || (MyField[i][j + 1] == 'K') || (MyField[i + 1][j + 1] == 'K')
                    || (MyField[i + 1][j - 1] == 'K') || (MyField[i - 1][j + 1] == 'K')
                    || (MyField[i - 1][j - 1] == 'K'));
                // выбираем вертикаль или горизонталь
                k = 1 + (rand() % 2);
                switch (k)
                {
                    // горизонталь
                case 1:
                    z = j - p;
                    // то продолжаем корабль вправо
                    if (z < 0)
                    {
                        // если корабль не накладывается на другие то
                        if ((MyField[i + 1][j + 2] != 'K') && (MyField[i + 1][j + 3] != 'K')
                            && (MyField[i][j + 3] != 'K') && (MyField[i][j + 2] != 'K')
                            && (MyField[i - 1][j + 3] != 'K') && (MyField[i - 1][j + 2] != 'K'))
                        {
                            
                            z = j + p;
                            // продолжаем корабль враво
                            while (j < z)
                            {
                                MyField[i][j] = 'K';
                                j++;
                            }
                        }
                    }
                    else
                    {
                        // если корабль не накладывается на другие то
                        if ((MyField[i][j - 2] != 'K') && (MyField[i][j - 3] != 'K')
                            && (MyField[i - 1][j - 2] != 'K') && (MyField[i - 1][j - 3] != 'K')
                            && (MyField[i + 1][j - 2] != 'K') && (MyField[i + 1][j - 3] != 'K'))
                        {
                            z = j - p;
                            // продолжаем корабль влево
                            while (j > z)
                            {
                                MyField[i][j] = 'K';
                                j--;
                            }
                        }
                        else
                        {
                            a--;
                        }
                    }
                    break;
                default:
                    z = i - p;
                    if (z < 0)
                    {
                        // если корабль не накладывается на другие то
                        if ((MyField[i + 2][j + 1] != 'K') && (MyField[i + 3][j + 1] != 'K')
                            && (MyField[i + 3][j] != 'K') && (MyField[i + 2][j] != 'K')
                            && (MyField[i + 2][j - 1] != 'K') && (MyField[i + 3][j - 1] != 'K'))
                        {
                            z = i + p;
                            while (i < z)
                            {
                                MyField[i][j] = 'K';
                                i++;
                            }
                        }
                    }
                    else
                    {
                        // если корабль не накладывается на другие то
                        if ((MyField[i - 2][j - 1] != 'K') && (MyField[i - 3][j - 1] != 'K')
                            && (MyField[i - 3][j] != 'K') && (MyField[i - 2][j] != 'K')
                            && (MyField[i - 2][j + 1] != 'K') && (MyField[i - 3][j + 1] != 'K'))
                        {
                            z = i - p;
                            while (i > z)
                            {
                                MyField[i][j] = 'K';
                                i--;
                            }
                        }
                        else
                        {
                            a--;
                        }
                    }
                    break;
                }
            }
            p--;
            break;
        case 2:
            // пока не занесем 3 корабля 2палубника
            for (a = 0; a < 3; a++)
            {
                do
                {
                    i = 0 + (rand() % 9);
                    j = 0 + (rand() % 9);
                } while ((MyField[i][j] == 'K') || (MyField[i + 1][j] == 'K') || (MyField[i - 1][j] == 'K')
                    || (MyField[i][j - 1] == 'K') || (MyField[i][j + 1] == 'K')
                    || (MyField[i + 1][j + 1] == 'K') || (MyField[i + 1][j - 1] == 'K')
                    || (MyField[i - 1][j + 1] == 'K') || (MyField[i - 1][j - 1] == 'K'));
                k = 1 + (rand() % 2);
                switch (k)
                {
                case 1:
                    z = j - p;
                    if (z < 0)
                    {
                        // если корабль не накладывается на другие то
                        if ((MyField[i + 2][j + 1] != 'K') && (MyField[i + 2][j] != 'K')
                            && (MyField[i + 2][j - 1] != 'K'))
                        {
                            z = i + p;
                            while (i < z)
                            {
                                MyField[i][j] = 'K';
                                i++;
                            }
                        }
                    }
                    else
                    {
                        // если корабль не накладывается на другие то
                        if ((MyField[i][j - 2] != 'K') && (MyField[i - 1][j - 2] != 'K')
                            && (MyField[i + 1][j - 2] != 'K'))
                        {
                            z = j - p;
                            while (j > z)
                            {
                                MyField[i][j] = 'K';
                                j--;
                            }
                        }
                        else
                        {
                            a--;
                        }
                    }
                    break;
                default:
                    z = i - p;
                    if (z < 0)
                    {
                        // если корабль не накладывается на другие то
                        if ((MyField[i + 2][j + 1] != 'K') && (MyField[i + 2][j] != 'K')
                            && (MyField[i + 2][j - 1] != 'K'))
                        {
                            z = i + p;
                            while (i < z)
                            {
                                MyField[i][j] = 'K';
                                i++;
                            }
                        }
                    }
                    else
                    {
                        // если корабль не накладывается на другие то
                        if ((MyField[i - 2][j - 1] != 'K') && (MyField[i - 2][j] != 'K')
                            && (MyField[i - 2][j + 1] != 'K'))
                        {
                            z = i - p;
                            while (i > z)
                            {
                                MyField[i][j] = 'K';
                                i--;
                            }
                        }
                        else
                        {
                            a--;
                        }
                    }
                    break;
                }
            }
            p--;
            break;
        case 1:
            // пока не занесем четыре корабля однопалубника
            for (a = 0; a < 4; a++)
            {
                do
                {
                    // координаты первой точки корабля
                    i = 0 + (rand() % 9);
                    j = 0 + (rand() % 9);
                } while ((MyField[i][j] == 'K') || (MyField[i + 1][j] == 'K')
                    || (MyField[i - 1][j] == 'K') || (MyField[i][j - 1] == 'K')
                    || (MyField[i][j + 1] == 'K') || (MyField[i + 1][j + 1] == 'K')
                    || (MyField[i + 1][j - 1] == 'K') || (MyField[i - 1][j + 1] == 'K')
                    || (MyField[i - 1][j - 1] == 'K'));
                MyField[i][j] = 'K';
            }
            p--;
            break;
        default:
            break;
        }
    }
    p = 4;
    while (p > 0)
    {
        switch (p)
        {
        case 4:
            i = 0 + (rand() % 9);
            j = 0 + (rand() % 9);
            k = 1 + (rand() % 2);
            switch (k)
            {
            case 1:
                z = j - p;
                if (z < 0)
                {
                    z = j + p;
                    while (j < z)
                    {
                        Real[i][j] = 'K';
                        j++;
                    }
                }
                else
                {
                    z = j - p;
                    while (j > z)
                    {
                        Real[i][j] = 'K';
                        j--;
                    }
                }

                break;
            default:
                z = i - p;
                if (z < 0) {
                    z = i + p;
                    while (i < z)
                    {
                        Real[i][j] = 'K';
                        i++;
                    }
                }
                else
                {
                    z = i - p;
                    while (i > z)
                    {
                        Real[i][j] = 'K';
                        i--;
                    }
                }
                break;
            }
            p--;
            break;
        case 3:
            for (a = 0; a < 2; a++)
            {
                do
                {
                    i = 0 + (rand() % 9);
                    j = 0 + (rand() % 9);
                } while ((Real[i][j] == 'K') || (Real[i + 1][j] == 'K')
                    || (Real[i - 1][j] == 'K') || (Real[i][j - 1] == 'K')
                    || (Real[i][j + 1] == 'K') || (Real[i + 1][j + 1] == 'K')
                    || (Real[i + 1][j - 1] == 'K') || (Real[i - 1][j + 1] == 'K')
                    || (Real[i - 1][j - 1] == 'K'));
                k = 1 + (rand() % 2);
                switch (k)
                {
                case 1:
                    z = j - p;
                    if (z < 0)
                    {
                        // если корабль не накладывается на другие то
                        if ((Real[i + 1][j + 2] != 'K') && (Real[i + 1][j + 3] != 'K')
                            && (Real[i][j + 3] != 'K') && (Real[i][j + 2] != 'K')
                            && (Real[i - 1][j + 3] != 'K') && (Real[i - 1][j + 2] != 'K'))
                        {
                            z = j + p;
                            while (j < z)
                            {
                                Real[i][j] = 'K';
                                j++;
                            }
                        }
                    }
                    else
                    {
                        // если корабль не накладывается на другие то
                        if ((Real[i][j - 2] != 'K') && (Real[i][j - 3] != 'K')
                            && (Real[i - 1][j - 2] != 'K') && (Real[i - 1][j - 3] != 'K')
                            && (Real[i + 1][j - 2] != 'K') && (Real[i + 1][j - 3] != 'K'))
                        {
                            z = j - p;
                            while (j > z)
                            {
                                Real[i][j] = 'K';
                                j--;
                            }
                        }
                        else
                        {
                            a--;
                        }
                    }
                    break;
                default:
                    z = i - p;
                    if (z < 0)
                    {
                        // если корабль не накладывается на другие то
                        if ((Real[i + 2][j + 1] != 'K') && (Real[i + 3][j + 1] != 'K')
                            && (Real[i + 3][j] != 'K') && (Real[i + 2][j] != 'K')
                            && (Real[i + 2][j - 1] != 'K') && (Real[i + 3][j - 1] != 'K'))
                        {
                            z = i + p;
                            while (i < z)
                            {
                                Real[i][j] = 'K';
                                i++;
                            }
                        }
                    }
                    else
                    {
                        // если корабль не накладывается на другие то
                        if ((Real[i - 2][j - 1] != 'K') && (Real[i - 3][j - 1] != 'K')
                            && (Real[i - 3][j] != 'K') && (Real[i - 2][j] != 'K')
                            && (Real[i - 2][j + 1] != 'K') && (Real[i - 3][j + 1] != 'K'))
                        {
                            z = i - p;
                            while (i > z)
                            {
                                Real[i][j] = 'K';
                                i--;
                            }
                        }
                        else
                        {
                            a--;
                        }
                    }
                    break;
                }
            }
            p--;
            break;
        case 2:
            for (a = 0; a < 3; a++)
            {
                do
                {
                    i = 0 + (rand() % 9);
                    j = 0 + (rand() % 9);
                } while ((Real[i][j] == 'K') || (Real[i + 1][j] == 'K')
                    || (Real[i - 1][j] == 'K') || (Real[i][j - 1] == 'K')
                    || (Real[i][j + 1] == 'K') || (Real[i + 1][j + 1] == 'K')
                    || (Real[i + 1][j - 1] == 'K') || (Real[i - 1][j + 1] == 'K')
                    || (Real[i - 1][j - 1] == 'K'));
                k = 1 + (rand() % 2);
                switch (k)
                {
                case 1:
                    z = j - p;
                    if (z < 0)
                    {
                        // если корабль не накладывается на другие то
                        if ((Real[i + 2][j + 1] != 'K') && (Real[i + 2][j] != 'K')
                            && (Real[i + 2][j - 1] != 'K'))
                        {
                            z = i + p;
                            while (i < z)
                            {
                                Real[i][j] = 'K';
                                i++;
                            }
                        }
                    }
                    else
                    {
                        // если корабль не накладывается на другие то
                        if ((Real[i][j - 2] != 'K') && (Real[i - 1][j - 2] != 'K')
                            && (Real[i + 1][j - 2] != 'K'))
                        {
                            z = j - p;
                            while (j > z)
                            {
                                Real[i][j] = 'K';
                                j--;
                            }
                        }
                        else
                        {
                            a--;
                        }
                    }
                    break;
                default:
                    z = i - p;
                    if (z < 0)
                    {
                        // если корабль не накладывается на другие то
                        if ((Real[i + 2][j + 1] != 'K') && (Real[i + 2][j] != 'K')
                            && (Real[i + 2][j - 1] != 'K'))
                        {
                            z = i + p;
                            while (i < z)
                            {
                                Real[i][j] = 'K';
                                i++;
                            }
                        }
                    }
                    else
                    {
                        // если корабль не накладывается на другие то
                        if ((Real[i - 2][j - 1] != 'K') && (Real[i - 2][j] != 'K')
                            && (Real[i - 2][j + 1] != 'K'))
                        {
                            z = i - p;
                            while (i > z)
                            {
                                Real[i][j] = 'K';
                                i--;
                            }
                        }
                        else
                        {
                            a--;
                        }
                    }
                    break;
                }
            }
            p--;
            break;
        case 1:
            for (a = 0; a < 4; a++)
            {
                do
                {
                    i = 0 + (rand() % 10);
                    j = 0 + (rand() % 10);
                } while ((Real[i][j] == 'K') || (Real[i + 1][j] == 'K')
                    || (Real[i - 1][j] == 'K') || (Real[i][j - 1] == 'K')
                    || (Real[i][j + 1] == 'K') || (Real[i + 1][j + 1] == 'K')
                    || (Real[i + 1][j - 1] == 'K') || (Real[i - 1][j + 1] == 'K')
                    || (Real[i - 1][j - 1] == 'K'));
                Real[i][j] = 'K';
            }
            p--;
            break;
        default:
            break;
        }
    }
    return 0;
}
// функция добивки корабля игрока
int ProverkaPodrankoff(char MyField[10][10], bool* Winner,
    bool* GameStatus, bool* Popadanie, bool* Control)
{
    // объявление переменных
    int i;
    int j;
    int i0;
    int j0;
    // ходим по массиву
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if ((MyField[i][j] == 'X') && (MyField[i][j + 1] == 'X')
                && (MyField[i][j + 2] != '0'))
            {
                j0 = j;
                j += 2;
                while (MyField[i][j] == 'K')
                {
                    MyField[i][j] = 'X';
                    j++;
                }
                j = j0;
            }
            if ((MyField[i][j] == 'X') && (MyField[i + 1][j] == 'X')
                && (MyField[i + 2][j] != '0'))
            {
                i0 = i;
                i += 2;
                while (MyField[i][j] == 'K')
                {
                    MyField[i][j] = 'X';
                    i++;
                }
                i = i0;
            }
        }
    }
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if ((MyField[i][j] == 'X') && ((MyField[i - 1][j] == 'K')
                || (MyField[i + 1][j] == 'K') || (MyField[i][j - 1] == 'K')
                || (MyField[i][j + 1] == 'K')))
            {
                i0 = i;
                j0 = j;
                if ((MyField[i - 1][j] != '0') && (MyField[i - 1][j] != 'X')
                    && ((i - 1) >= 0))
                {
                    if (MyField[i - 1][j] == 'K')
                    {
                        i0 = i;
                        i--;
                        while ((MyField[i][j] == 'K') && (i >= 0))
                        {
                            MyField[i][j] = 'X';
                            Sleep(1000);
                            i--;
                        }
                        if (i < 0)
                        {
                            i = i0 + 1;
                            while ((MyField[i][j] == 'K') && (i < 10))
                            {
                                MyField[i][j] = 'X';
                                Sleep(1000);
                                i++;
                            }
                        }
                        else
                        {
                            if (MyField[i][j] != '0')
                            {
                                MyField[i][j] = '0';
                                *Popadanie = false;
                                *Control = false;
                            }
                            break;
                        }

                    }
                    else
                    {
                        MyField[i - 1][j] = '0';
                        *Popadanie = false;
                        *Control = false;
                        break;
                    }
                }
                if ((MyField[i][j - 1] != '0') && (MyField[i][j - 1] != 'X')
                    && ((j - 1 >= 0)))
                {
                    if (MyField[i][j - 1] == 'K')
                    {
                        j0 = j;
                        j--;
                        while ((MyField[i][j] == 'K') && (j >= 0))
                        {
                            MyField[i][j] = 'X';
                            Sleep(1000);
                            j--;
                        }
                        if (j < 0)
                        {
                            j = j0 + 1;
                            while ((MyField[i][j] == 'K') && (j < 10))
                            {
                                MyField[i][j] = 'X';
                                Sleep(1000);
                                j++;
                            }
                        }
                        else
                        {
                            if (MyField[i][j] != '0')
                            {
                                MyField[i][j] = '0';
                                *Popadanie = false;
                                *Control = false;
                            }
                            break;
                        }

                    }
                    else
                    {
                        MyField[i][j - 1] = '0';
                        *Popadanie = false;
                        *Control = false;
                        break;
                    }
                }
                if ((MyField[i + 1][j] != '0') && (MyField[i + 1][j] != 'X')
                    && ((i + 1) < 10))
                {
                    if (MyField[i + 1][j] == 'K')
                    {
                        i++;
                        while ((MyField[i][j] == 'K') && (i < 10))
                        {
                            MyField[i][j] = 'X';
                            Sleep(1000);
                            i++;
                        }
                        if (i > 9)
                        {
                            i = i0 - 1;
                            while (MyField[i][j] == 'K')
                            {
                                MyField[i][j] = 'X';
                                Sleep(1000);
                                i--;
                            }
                        }
                        else
                        {
                            if (MyField[i][j] != '0')
                            {
                                MyField[i][j] = '0';
                                *Popadanie = false;
                                *Control = false;
                            }
                            break;
                        }

                    }
                    else
                    {
                        MyField[i + 1][j] = '0';
                        *Popadanie = false;
                        *Control = false;
                        break;
                    }
                }
                if ((MyField[i][j + 1] != '0') && (MyField[i][j + 1] != 'X')
                    && ((j + 1) < 10))
                {
                    if (MyField[i][j + 1] == 'K')
                    {
                        j++;
                        while ((MyField[i][j] == 'K') && (i < 10))
                        {
                            MyField[i][j] = 'X';
                            Sleep(1000);
                            j++;
                        }
                        if (j > 9)
                        {
                            j = j0 - 1;
                            while (MyField[i][j] == 'K')
                            {
                                MyField[i][j] = 'X';
                                Sleep(1000);
                                j--;
                            }
                        }
                        else
                        {
                            if (MyField[i][j] != '0')
                            {
                                MyField[i][j] = '0';
                                *Popadanie = false;
                                *Control = false;
                            }
                            break;
                        }

                    }
                    else
                    {
                        MyField[i][j + 1] = '0';
                        *Popadanie = false;
                        *Control = false;
                        break;
                    }
                }
            }
        }
    }
    return 0;
}

int main()
{
    // установка цвета
    system("color 0E");
    int Counter = 0;
    int i;
    int j;
    // установка для рандома
    srand(time(0));
    // объявление полей для взаимодействия 
    char PlayerField[10][10];
    char FakeField[10][10];
    char InvisibleField[10][10];
    // объявление флажков
    bool Winner = false;
    bool Control = true;
    bool GameStatus = true;
    bool Popadanie = true;
    bool Ext = false;
    bool End = false;
    // запись игрока в файл
    ZapisIroka();
    // подключение русского языца
    setlocale(0, "");
    do
    {
        
        Counter = 0;
        // вывод меню
        Interfaces(&Winner, &Control, &GameStatus, &Popadanie, &Ext, &End);
        // если был выбран пункт выхода из игры то
        if (End)
        {
            // завершаем игру
            return 0;
        }
        // пока количество ячеек кораблей меньше 40
        while (Counter < 40)
        {
            // очистка экрана
            system("cls");
            Counter = 0;
            // расстановка кораблей
            Setup(PlayerField, FakeField, InvisibleField);
            // подсчет кораблей
            for (i = 0; i < 10; i++)
            {
                for (j = 0; j < 10; j++)
                {
                    if (PlayerField[i][j] == 'K')
                    {
                        Counter++;
                    }
                }
            }
            // подсчет кораблей
            for (i = 0; i < 10; i++)
            {
                for (j = 0; j < 10; j++)
                {
                    if (InvisibleField[i][j] == 'K')
                    {
                        Counter++;
                    }
                }
            }
        }
        // очистка экрана
        system("cls");
        // отрисовка кораблей
        Draw(PlayerField, FakeField);
        // пока игра не законыена
        while (GameStatus == true)
        {
            // установка флажков
            Popadanie = true;
            Control = true;
            // пока есть попадание
            while (Popadanie == true)
            {
                // очистка экрана
                system("cls");
                // вырисовка
                Draw(PlayerField, FakeField);
                // атака игрока
                AttackPlayer(FakeField, InvisibleField, &GameStatus, &Popadanie, &Ext);
                // проверка поля
                CheckBotField(InvisibleField, FakeField, &Winner, &GameStatus, &Popadanie);
                // очистка экрана
                system("cls");
                // вырисовка полей
                Draw(PlayerField, FakeField);
            }
            // флаг попадани
            Popadanie = true;
            // пока идет игра и есть попадание 
            while ((Popadanie == true) && (Ext == false)
                && (GameStatus == true))
            {
                // проверка на добивку
                ProverkaPodrankoff(PlayerField, &Winner, &GameStatus, &Popadanie, &Control);
                // проверка поля 
                CheckPlayerField(PlayerField, &Winner, &GameStatus, &Popadanie);
                // очистка экрана
                system("cls");
                // отрисовка
                Draw(PlayerField, FakeField);
                // если корабль не был добит то
                if (Control == true)
                {
                    Sleep(1000);
                    // атака бота
                    AttackBot(PlayerField, &Popadanie);
                    // отрисовка
                    Draw(PlayerField, FakeField);
                    // проверка поля игрока
                    CheckPlayerField(PlayerField, &Winner, &GameStatus, &Popadanie);
                    // отрисовка
                    Draw(PlayerField, FakeField);
                }
            }
        }
        // очистка экрана
        system("cls");
        if (Winner == true)
        {
            // объявление переменной файла
            ofstream fout;
            // открываем файл
            fout.open("last_players.txt", ofstream::app);
            // если не удалось открыть файл
            if (!fout.is_open())
            {

                cout << "Не удалось записать результат игрока";
                // вызов паузы
                Sleep(10000);
                // конец работы программы
                return 0;
            }
            // иначе записываем в файл
            else
            {
                // игрок победил
                fout << "\t won" << endl;
                // закрываем файл
                fout.close();
                
            }
            for (i = 0; i < 30; i++)
            {
                printf("ВЫ ПОБЕДИЛИ!!! ВЫ ПОБЕДИЛИ!!! ВЫ ПОБЕДИЛИ!!!");
                printf("ВЫ ПОБЕДИЛИ!!! ВЫ ПОБЕДИЛИ!!! ВЫ ПОБЕДИЛИ!!!");
            }
        }
        // иначе
        else
        {
            // открываем файл для записи
            ofstream fout;
            fout.open("last_players.txt", ofstream::app);
            // если не открылся
            if (!fout.is_open())
            {
                cout << "Не удалось записать результат игрока";
                // вызов паузы
                Sleep(10000);
                return 0;
            }
            // иначе
            else
            {
                // запись того что проиграл
                fout << "\t lose" << endl;
                // закрываем файл
                fout.close();
                
            }
            // вывод сообщения о проигрыше
            for (i = 0; i < 30; i++)
            {
                printf("ВЫ ПРОИГРАЛИ!! ВЫ ПРОИГРАЛИ!! ВЫ ПРОИГРАЛИ!!");
                printf("ВЫ ПРОИГРАЛИ!! ВЫ ПРОИГРАЛИ!! ВЫ ПРОИГРАЛИ!!");
            }
        }
        // пауза
        Sleep(1000);
    } while (!End);
    // конец программы
    return 0;
}