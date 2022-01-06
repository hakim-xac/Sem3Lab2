#include <iostream>
#include "MyList.h"                                                  // Подключаем заголовок, где находится реализация методов класса, работы программы
#include "ListInterface.h"                                                  // Подключаем заголовок, где находится реализация методов класса, работы программы
#include "enums.h"                                                  // Подключаем заголовок, содержащий все перечисления





int main()
{
    using namespace LAB2;                           // Подключаем пространство имен нашей программы

    setlocale(LC_ALL, "Russian");                   // Задаем локаль
    Keys key{ Keys::Exit };

    ListInterface<LAB2::MyList<int>> window{ MyList<int>() };

    /* Запускаем бесконечный цикл ожидая ввод команды от пользователя  */
    do {
        system("cls");
        window.showHeader();
        window.showStatusList();
        window.showStatusBar();
        window.showMenu();
        key = static_cast<Keys>(std::cin.get());
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (key)
        {
        case Keys::Exit:
            exit(0);
            break;  
        case Keys::CreateRandomList:
            window.showGeneratedRandom();
            break;
        case Keys::AscendingList:
            window.showAscendingList();
            break;
        case Keys::DesciningList:
            window.showDescendingList();
            break;
        case Keys::ShuffleList:
            window.showShuffleList();
            break;
        case Keys::PrintList:
            window.showPrintList();
            break;
        case Keys::ClearList:
            window.showClearList();
            break;  
        default:
            window.addToStatusBar("Введена не верная команда!");   // любая клавиша отсутствующая в перечислении Keys
            break;
        }
    } while (key != Keys::Exit);                    // 0

}

