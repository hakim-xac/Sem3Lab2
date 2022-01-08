#include <iostream>
#include "MyList.h"                 // Подключаем заголовок, где находится реализация методов класса, работы программы
#include "ListInterface.h"          // Подключаем заголовок, где находится реализация методов интерфейса для работы с классом MyList
#include "enums.h"                  // Подключаем заголовок, содержащий все перечисления





int main()
{
    using namespace LAB2;                           // Подключаем пространство имен нашей программы

    setlocale(LC_ALL, "Russian");                   // Задаем локаль
    Keys key{ Keys::Exit };                         // Задаем по умолчанию команду выхода

    ListInterface<LAB2::MyList<int>> window{ MyList<int>() };   // Задаем интерфейс

    /* Запускаем бесконечный цикл ожидая ввод команды от пользователя  */
    while(true)
    {
        system("cls");
        window.showHeader();                // Вывод заголовка
        window.showStatusList();            // Вывод информации о списке
        window.showStatusBar();             // Вывод "всплывающих сообщений"
        window.showMenu();                  // Вывод меню
        key = static_cast<Keys>(std::cin.get());                            // Принимаем один символ
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем остальной буфер
        switch (key)
        {
        case Keys::Exit:                    // 0
            exit(0);                        // Выход из цикла
            break;  
        case Keys::CreateRandomList:        // 1
            window.showGeneratedRandom();   // Заполняем список случайными значениями
            break;
        case Keys::AscendingList:           // 2
            window.showAscendingList();     // Сортируем список по убыванию
            break;
        case Keys::DesciningList:           // 3
            window.showDescendingList();    // Сортируем списрк по возрастанию
            break;
        case Keys::ShuffleList:             // 4
            window.showShuffleList();       // Перемешиваем список
            break;
        case Keys::PrintList:               // 5
            window.showPrintList();         // Вывод списка на экран
            break;
        case Keys::ClearList:               // 6
            window.showClearList();         // Очищаем список
            break;
        case Keys::ResizeList:              // 9
            window.showResizeList();        // Изменяем размер списка и очищаем его
            break;  
        default:
            window.addToStatusBar("Введена не верная команда!");            // любая клавиша отсутствующая в перечислении Keys
            break;
        }
    }

}

