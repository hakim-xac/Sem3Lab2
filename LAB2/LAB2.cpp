#include <iostream>
#include "MyApp.h"                                                  // Подключаем заголовок, где находится реализация методов класса, работы программы
#include "Interface.h"                                                  // Подключаем заголовок, где находится реализация методов класса, работы программы
#include "enums.h"                                                  // Подключаем заголовок, содержащий все перечисления
/*
* Инициализируем статические переменные
*/
LAB2::SortingStatus LAB2::Interface::activeStatus{ LAB2::SortingStatus::NotStatus };
int LAB2::MyApp::sizeList{ 100 };    // Первичный размер массива


/* Инициализация побочных статических переменных */
/* Пользователю менять их нельзя, иначе UB */
std::list<int> LAB2::MyApp::lst(LAB2::MyApp::sizeList); //-   
bool LAB2::Interface::flagClearArray{ true }; //-                                                          
std::queue<std::string> LAB2::Interface::bufferForStatusBar{};//-
std::ostream& LAB2::Interface::out{ std::cout };//-

const std::map <LAB2::SortingStatus, std::string> LAB2::Interface::mapActiveStatus{ //-
    {LAB2::SortingStatus::SortedAscending, "По возрастанию"},
    {LAB2::SortingStatus::SortedDescending, "По убыванию"},
    {LAB2::SortingStatus::ShuffleSorted, "Перемешан"},
    {LAB2::SortingStatus::RandomSorted, "Случайно"},
    {LAB2::SortingStatus::NotStatus, "Не сортирован"}
};



int main()
{
    using namespace LAB2;                           // Подключаем пространство имен нашей программы

    setlocale(LC_ALL, "Russian");                   // Задаем локаль
    Keys key{ Keys::Exit };

    /* Запускаем бесконечный цикл ожидая ввод команды от пользователя  */
    do {
        system("cls");
        Interface::showHeader();
        Interface::showStatusList();
        Interface::showStatusBar();
        Interface::showMenu();
        key = static_cast<Keys>(std::cin.get());
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (key)
        {
        case Keys::Exit:
            exit(0);
            break;
        default:
            Interface::addInStatusBar("Введена не верная команда! ");   // любая клавиша отсутствующая в перечислении Keys
            break;
        }
    } while (key != Keys::Exit);                    // 0

}

