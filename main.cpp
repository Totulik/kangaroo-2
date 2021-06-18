#include <iostream>
#include <cstdlib>
#include <cctype> //Библиотека для функция isalpha и isdigit

using namespace std;

struct matrix { //Структура, в которой есть кунгуру и ловушка
    bool trap = false;
    bool kangaroo = false;
};

void addTrap(matrix** field, int size) {
    int column = -1, line = -1;
    string columnStr, lineStr;
    bool err = false;
    int runner = 0;

    while (column < 1 || column > size || err == true) {
        cout << "Введите Х координату" << endl;
        err = false;
        runner = 0;
        cin >> columnStr; //Пользователь вводит не число, а число в виде строки, чтоб ее проверять
        while (err == false && runner < columnStr.length()) { //Пока err != false и пока бегунок не станет равным длине строки
            if (isalpha(columnStr[runner])) //Проверяем есть ли буква в строке columnStr поэлементно. Если встретили - выходим из этого while
                err = true;
            else runner++; //Иначе прибаляем бегунок и идем обратно в цикл, чтоб проверить следующий элемент строки columnStr
        }
        if (err == true)
            cout << "Х не может содержать буквы" << endl; //Если флаг из строки 25 равен тру, то есть если есть ошибка, то выводим это сообщение
        else { //Иначе
            column = stoi(columnStr); //s to i - string to int (переводим строку в число)

            if (column > size || column < 1) { //Проверка уже числа на диапазон
                cout << "X должен быть в пределах от 1 до 5" << endl;
            }
        }
    }

    while (line < 1 || line > size) { //То же самое
        cout << "Введите Y координату" << endl;
        err = false;
        runner = 0;
        cin >> lineStr;
        while (err == false && runner < lineStr.length()) {
            if (isalpha(lineStr[runner])) //Проверяем есть ли буква в строке поэлементно. Если встретили - выходим из этого while
                err = true;
            else runner++;
        }
        if (err == true)
            cout << "Y не может содержать буквы" << endl;
        else {
            line = stoi(lineStr); //s to i - string to int

            if (line > size || line < 1) {
                cout << "Y должен быть в пределах от 1 до 5" << endl;
            }
        }
    }

    if (column == 1 && line == 5) {
        cout << "Нельзя ставить ловушку в финишную точку" << endl;
        addTrap(field, size);
    } else
        field[line-1][column-1].trap = true;
}

int jumping(matrix** field, int size) {
    int line = -1;
    int column = -1;

    for (int i = 0; i < size; i++) //Бегаем по массиву и ищем где стоит кенгуру
        for (int j = 0; j < size; j++)
            if (field[i][j].kangaroo == true) { // Если нашли его, то сохранем его координаты
                line = i;
                column = j;
            }
    if (line == 4 && column == 1) {
        field[line][column].kangaroo = false;
        column--;
        field[line][column].kangaroo = true;
    } else {
        for (int i = 0; i < (rand() % 2 + 1); i++) { //Рандомайзер. Через одну или на следующую клетку
            //Движение по спирали
            if ((line == 2) && (column == 2)) { //Если его координаты равны этим числам то...
                field[line][column].kangaroo = false; //Убираем его из этой клетки
                column--; //Меняем координату
                field[line][column].kangaroo = true; //Ставим его в новую, измененную ранее, координату
            } else { //Если не в той координате, то проверяем другие координаты и так далее...

                if ((line == 2) && (column == 1)) {
                    field[line][column].kangaroo = false;
                    line--;
                    field[line][column].kangaroo = true;
                } else {

                    if ((column >= 1) && (column <= 2) && (line == 1)) {
                        field[line][column].kangaroo = false;
                        column++;
                        field[line][column].kangaroo = true;
                    } else {

                        if ((column == 3) && (line >= 1) && (line <= 2)) {
                            field[line][column].kangaroo = false;
                            line++;
                            field[line][column].kangaroo = true;
                        } else {

                            if ((column <= 3) && (column >= 1) && (line == 3)) {
                                field[line][column].kangaroo = false;
                                column--;
                                field[line][column].kangaroo = true;
                            } else {

                                if ((column == 0) && (line <= 3) && (line >= 1)) {
                                    field[line][column].kangaroo = false;
                                    line--;
                                    field[line][column].kangaroo = true;
                                } else {

                                    if ((column >= 0) && (column <= 3) && (line == 0)) {
                                        field[line][column].kangaroo = false;
                                        column++;
                                        field[line][column].kangaroo = true;
                                    } else {

                                        if ((column == 4) && (line >= 0) && (line <= 3)) {
                                            field[line][column].kangaroo = false;
                                            line++;
                                            field[line][column].kangaroo = true;
                                        } else {
                                            if ((line == 4) && (column >= 0) && (column <= 4)) {
                                                field[line][column].kangaroo = false;
                                                column--;
                                                field[line][column].kangaroo = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (line == 4 && column == 0)
        //Функция возвращает 2, если кенгуру выйграл
        return 2;

    if (field[line][column].trap == true)
        //Функция возвращает 1, если кенгуру попал в ловушку
        return 1;

    //Иначе, если он никуда не попал - функция возвращает 0
    return 0;
}

int main() {
    int size = 5;

    matrix** field = new matrix*[size]; //Объявляем массив размера 5
    for(int i = 0; i < size; i++) {
        field[i] = new matrix[size];
    }
    int gameChoice = 1;
    int gameScoreKangaroo = 0;
    int gameScoreHunter = 0;

    while (gameChoice == 1) {

        cout << endl << endl << "----------------------------------Новая игра началась----------------------------------" << endl;

        field[2][2].kangaroo = true; //Ставим кенгуру в центр
        int flag = 0;
        int trapCount = 0;

        while (flag == 0) { //Пока флаг равен нулю заходим сюда
            string trapChoice = "0";
            int trapChoiceInt = stoi(trapChoice); //Изначально переменная выбора постановки ловушки = 0
            int runner = 0; //бегунок
            bool err = false; //Флаг ошибки для проверки на букву (есть буква - переменная гдето в коде изменится на true)
            if (trapCount < 3) { //Если ловушек меньше 3 то идем сюда
                cout << "Если хотите добавить ловушку введите 1, иначе - 2. Вы добавили " << trapCount
                     << ". Всего добавить можно только 3 ловушки" << endl;
                while (err == true || (trapChoiceInt != 2 && trapChoiceInt != 1) ) { //Пока есть ошибка, либо пока выбор не равен 1 или 2 мы заходим сюда
                    cin >> trapChoice; //Вводим выбор, но не как число, а как строку, тк trapChoice у нас string (для проверки)
                    err = false; //Обнуляем переменную ошибки перед общей проверкой
                    while (err == false && runner < trapChoice.length()) { //Если в строке есть буква то err становится равной true и тогда мы выйдем из этого while
                        if (isalpha(trapChoice[runner])) //тут та же херня с бегунком, типа проверяем поэлементно введенную строку на наличие букв
                            err = true;
                        else runner++;
                    }
                        if (err == false) { //Если в строке не было букв, то переводим строку в число и проверяем на 1 или 2
                            trapChoiceInt = stoi(trapChoice); //Теперь мы точно знаем что в введенной строке trapChoice нет букв, поэтому спокойно переводим ее в int
                            if ((trapChoiceInt != 2 && trapChoiceInt != 1)) { //И сравниваем этот int с 1 или с 2
                                cout << "Если хотите добавить ловушку введите 1, иначе - 2. Вы добавили " << trapCount
                                     << ". Всего добавить можно только 3 ловушки" << endl;
                            }
                        } else { //Если были буквы в строке, то выводим это сообщение и начинаем заново
                            cout << "Если хотите добавить ловушку введите 1, иначе - 2. Вы добавили " << trapCount
                                 << ". Всего добавить можно только 3 ловушки" << endl;
                        }
                }
                if (trapChoiceInt == 1) { //Если 1, то запускаем процедуру добаления ловушки
                    addTrap(field, size);
                    trapCount++; //прибавляем количество ловушек
                }
            }

            flag = jumping(field, size); //Флагу присвоится значение, которое возвратит функция. Этот флаг влияет на большой цикл while из 178 строки

            cout << "-----------Карта ловушек-----------" << endl;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++)
                    cout << field[i][j].trap << "\t";
                cout << endl;
            }

            cout << endl << "-----------Карта кенгуру-----------" << endl;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++)
                    cout << field[i][j].kangaroo << "\t";
                cout << endl;
            }
        }
        if (flag == 1) {
            cout << "Игра окончена. Кенгуру попал в ловушку" << endl;
            gameScoreHunter++;
        }
        else {
            cout << "Игра окончена. Кенгуру выйграл" << endl;
            gameScoreKangaroo++;
        }
        cout << "Итоговый счет: " << endl;
        cout << "Кенгуру: " << gameScoreKangaroo << " Охотник: " << gameScoreHunter << endl;
        cout << "Если хотите продолжить игру - введите 1, иначе - любой символ кроме 1" << endl;
        cin >> gameChoice;

        if (gameChoice == 1) { //Если захотели продолжить игру, то удаляем все ловушки и кенгуру с поля
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    field[i][j].kangaroo = false;
                    field[i][j].trap = false;
                }
            }
        }
    }
    cout << "Игра окончена. До новых встреч!" << endl;
}