#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;


// переменная для неопределенного типа данных
template<typename T>
// класс стека
class MyStack
{
private:
    // структура элемента
    struct Cell {
        // значение элемента
        T value;
        // указатель на следующий
        Cell* next;
    };
    // объявление начала списка
    Cell* begin = NULL;
    // вывод стека
    void output(Cell* a)
    {
        if (a == NULL) return;
        output(a->next);
        cout << a->value << " ";
    }

public:

    // добавление элемента
    void push_back(T item)
    {
        // объявляем новый элемент
        Cell* c;
        // если стек пуст
        if (begin == NULL)
        {
            // выделяем память для нового элеемнта
            c = new Cell;
            // запоминаем переменную
            c->value = item;
            // зануляем указатель
            c->next = NULL;
            // делаем его первым элементом
            begin = c;
            return;
        }
        else
        {
            // переходим в начало стека
            c = begin;
            // переходим в конец
            while (c->next != NULL)
            {
                c = c->next;
            }
            // выделяем память для следующего
            c->next = new Cell;
            // переходим к новому
            c = c->next;
            // запоминаем значение
            c->value = item;
            // зануляем указатель
            c->next = NULL;
            return;
        }

        

    }
    // функция возвращения последнего элемента
    T back()
    {
        // запоминаем начало стека
        Cell* c = begin;
        // переходим в конец стека
        while (c->next != NULL)
        {
            c = c->next;
        }
        // возвращаем значение
        return c->value;
    }

    // удаление последнего элемента
    void pop_back()
    {
        // если в стеке один элемент
        if (begin->next == NULL)
        {
            // зануляем указатель на начало стека
            begin = NULL;
            return;
        }
        // запоминаем начало стека
        Cell* c = begin;
        // переходим к предпоследнему элементу
        while (c->next != NULL)
        {
            // если элемент предпоследний 
            if (c->next->next == NULL)
            {
                // зануляем указатель на следующий
                c->next = NULL;
                break;
            }
            c = c->next;  
        }
        return;

    }
    // добавление элемента в начало стека
    void push(T item)
    {
        // объявляем новый элемент и выделяем память под него 
        Cell* c = new Cell();
        // запоминаем элемент
        c->value = item;
        // указатель указывает на начало стека
        c->next = begin;
        // начало стека теперь новый элемент
        begin = c;
    }

    // удаление первого элемент
    void pop()
    {
        Cell* a;
        if (begin != NULL)
        {
            a = begin;
            begin = a->next;
            
        }
    }

    // функция на проверку пустоты стека
    int empty()
    {
        return (begin == NULL);
    }
    // функция вывода стека
    void show()
    {
        output(begin);
    }

};

//в этой функции рассмотрим все возможные операции, что могут встретиться в строке
bool operation(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

//данная функция будет возвращать приоритет поступившей операции
int prioritet(char op) {
    if (op < 0) return 3;
    else {
        if (op == '+' || op == '-')return 1;
        else if (op == '*' || op == '/')return 2;
        else if (op == '^')return 4;
        else return -1;
    }
}

//следующая функция описывает принцип работы каждого оператора
void action(MyStack<long> &value, char op) {
    if (op < 0) {                            //для унарных операций
        long unitar = value.back();
        value.pop_back();
        if (-op == '-')value.push_back(-unitar);
    }
    else {                               //для бинарных операций
        long res;
        long right = value.back();
        value.pop_back();
        long left = value.back();
        value.pop_back();
        if (op == '+')
        {
            res = left + right;
            value.push_back(res);
        }
        else if (op == '-')
        {
            res = left - right;
            value.push_back(res);
        }
        else if (op == '*')
        {
            res = left * right;
            value.push_back(res);
        }
        else if (op == '/')
        {
            res = left / right;
            value.push_back(res);
        }
        else if (op == '^')
        {
            res = pow(left, right);
            value.push_back(res);
        }
    }
}

long calculus(string& formula) {
    bool unary = true;        //создадим булевскую переменную, для распределения операторов на унарные и бинарные
    MyStack<long>value;        //заведем массив для целых чисел
    MyStack<char>op;           //и соответственно для самых операторов
    for (int i = 0; i < formula.size(); i++) {
        if (formula[i] == '(') {    //если текущий элемент — открывающая скобка, то положим её в стек
            op.push_back('(');
            unary = true;
        }
        else if (formula[i] == ')') {
            while (op.back() != '(') {  //если закрывающая скобка - выполняем все операции, находящиеся внутри этой скобки
                action(value, op.back());
                op.pop_back();
            }
            op.pop_back();
            unary = false;
        }
        else if (operation(formula[i])) { //если данный элемент строки является одни из выше перечисленных операндов,то
            char zn = formula[i];
            if (unary == true)zn = -zn; //придает отрицательное значение, для распознавания функции унарности оператора 
            while (!op.empty() && prioritet(op.back()) >= prioritet(zn)) {
                action(value, op.back());   //выполняем сами алгебраические вычисления, где все уже операции упорядочены  
                op.pop_back();              //в одном из стеков по строгому убыванию приоритета, если двигаться от вершины
            }
            op.push_back(zn);
            unary = true;
        }
        else {
            string number;      //заведем строку для найденных числовых операндов
            while (i < formula.size() && isdigit(formula[i]))number += formula[i++];//распознаем их с помощью библиотечной функции строк
            i--;
            value.push_back(atol(number.c_str()));//поместим в наш стек с числовыми выражениями
            unary = false;
        }
    }
    while (!op.empty()) {     //выполним еще не использованные операции в стеке 
        action(value, op.back());
        op.pop_back();
    }
    return value.back(); //получим на выходе значение выражения
}

int main() {
    string formula; //введем две строки: сам многочлен/числовое выражение и по необходимости значение переменной 
    cin >> formula;
    cout << calculus(formula);  //выведем ответ
    return 0;
}