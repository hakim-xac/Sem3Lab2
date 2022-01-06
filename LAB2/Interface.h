#pragma once
#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <map>
#include "enums.h"
#include "MyList.h"

namespace LAB2 {

	template <typename TypeList>
	class Interface
	{
		std::ostream& out			{ std::cout };
		int maxTableWidth			{ 90 };
		int maxTableColumns			{ 5 };
		bool flagClearArray			{ true };
		SortingStatus activeStatus	{ SortingStatus::NotStatus };
		std::queue <std::string> bufferForStatusBar	{};

		const std::map <LAB2::SortingStatus, std::string> mapActiveStatus	{
			{ LAB2::SortingStatus::SortedAscending,     "По возрастанию" },
			{ LAB2::SortingStatus::SortedDescending,    "По убыванию" },
			{ LAB2::SortingStatus::ShuffleSorted,       "Перемешан" },
			{ LAB2::SortingStatus::RandomSorted,        "Случайно" },
			{ LAB2::SortingStatus::NotStatus,           "Не сортирован" } 
		};
		TypeList lst;
		Interface() = delete;
	public:


		Interface(TypeList& lst) :	lst(lst) {}
		Interface(TypeList&& lst) : lst(lst) {}


		void addInStatusBar(const std::string& part)
		{
			bufferForStatusBar.emplace(delimiter());
			bufferForStatusBar.emplace(delimiter(' '));
			bufferForStatusBar.emplace(generatingStrings(part));
			bufferForStatusBar.emplace(delimiter(' '));
			bufferForStatusBar.emplace(delimiter());
		}


		void addInStatusBar(const std::string&& part)
		{
			bufferForStatusBar.emplace(delimiter());
			bufferForStatusBar.emplace(delimiter(' '));
			bufferForStatusBar.emplace(generatingStrings(part));
			bufferForStatusBar.emplace(delimiter(' '));
			bufferForStatusBar.emplace(delimiter());
		}


		void showHeader()
		{
			std::string header{ generatingStrings("Лабораторная работа № 2", "Быстрые методы сортировки последовательностей.") };
			std::string header2{ generatingStrings("Группа ПБ-11", "Хакимов А.C.") };

			std::string hr{ delimiter() };

			out << hr;
			out << header;
			out << delimiter('-');
			out << header2;
			out << hr;
		}


		void showMenu()
		{
			std::string hr{ delimiter() };

			out << hr;
			out << delimiter(' ');
			out << generatingStrings("Нажмите на клавишу и нажмите ВВОД");
			out << delimiter('_');
			out << generatingStrings("( 1 )", "Генерация случайного массива", '.');
			out << generatingStrings("( 2 )", "Отсортировать список по возрастанию", '.');
			out << generatingStrings("( 3 )", "Отсортировать список по убыванию", '.');
			out << generatingStrings("( 4 )", "Перемешать список", '.');
			out << generatingStrings("( 5 )", "Распечатать список на экран", '.');
			out << generatingStrings("( 6 )", "Очистить список", '.');
			out << generatingStrings("( 0 )", "Выход", '.');
			out << hr;
		}


		void showStatusBar()
		{
			if (!bufferForStatusBar.empty()) {
				std::string hr{ delimiter(' ')};

				out << hr;

				while (!bufferForStatusBar.empty())
				{
					out << bufferForStatusBar.front();
					bufferForStatusBar.pop();
				}

				out << hr;

			}
		}


		void showStatusList()
		{
			out << generatingStrings("Статус Списка:", flagClearArray ? "ПУСТОЙ" : "ЗАПОЛНЕН");
			out << delimiter('-');
			out << generatingStrings("количество элементов списка:", std::to_string(lst.getSizeList()));
			out << delimiter('-');
			out << generatingStrings("Статус сортировки списка:", mapActiveStatus.at(activeStatus));
			out << delimiter();
		}


		void showGeneratedRandom()
		{
			lst.createRandomList();
			
			flagClearArray = false;
			activeStatus = LAB2::SortingStatus::RandomSorted;
			addInStatusBar("Список успешно заполнен случайными числами!");
		}


		const std::string delimiter(char del = '=')
		{
			std::string result(maxTableWidth, del);
			result.at(0) = '#';	result[result.size() - 2] = '#'; result.back() = '\n';
			return result;
		}


		void showPrintList()
		{
			if (!flagClearArray) {

				addInStatusBar("Вывод списка");

				int lengthColumn{ (maxTableWidth - 10) / maxTableColumns };
				printList(std::string(lengthColumn, ' '));

			}
			else {
				addInStatusBar("Список ещё не заполнен!");
			}
		}

		void printList(const std::string&& defaultString)
		{
			std::string result{};
			for (auto it{ lst.begin() }, ite{ lst.end() }; it != ite; ++it) {

				std::string tmp{ defaultString };
				std::string num{ std::to_string(*it) };

				size_t len{ static_cast<size_t>(std::distance(lst.begin(), it)) };
				if ((len + 1) % maxTableColumns != 0) {
					tmp.replace(tmp.size() - 1, 1, "|");
				}
				tmp.replace((tmp.length() - num.length()) / 2, num.length(), num);
				result += tmp;

				if ((len + 1) % maxTableColumns == 0) {
					bufferForStatusBar.emplace(generatingStrings(result));
					bufferForStatusBar.emplace(delimiter('-'));
					result.clear();
				}
			}
			if (!result.empty()) bufferForStatusBar.emplace(generatingStrings(result));
		}


		std::string generatingStrings(const std::string& str, char del = ' ')
		{
			try {
				if (str.empty()) throw std::exception("Dont empty string! -> LAB2::MyList::generatingStrings(const std::string& str)");
				int parity{ str.length() % 2 == 0 };
				size_t middleSize{ maxTableWidth > (str.length() + 2) ? (maxTableWidth - str.length() - 2) / 2 : 0 };

				std::string middle(middleSize - parity, del);
				std::string result{ "#" + middle + str + (parity ? " " : "") + middle + "#\n" };

				return result;
			}
			catch (const std::exception& ex) {
				std::cout << ex.what();
				return std::string();
			}
		}


		std::string generatingStrings(const std::string&& str, char del = ' ')
		{
			try {
				if (str.empty()) throw std::exception("Dont empty string! -> LAB2::MyList::generatingStrings(const std::string& str)");
				int parity{ str.length() % 2 == 0 };
				size_t middleSize{ maxTableWidth > (str.length() + 2) ? (maxTableWidth - str.length() - 2) / 2 : 0 };

				std::string middle(middleSize - parity, del);
				std::string result{ "#" + middle + str + (parity ? " " : "") + middle + "#\n" };

				return result;
			}
			catch (const std::exception& ex) {
				std::cout << ex.what();
				return std::string();
			}
		}


		std::string generatingStrings(const std::string& str, const std::string& str2, char del = ' ')
		{
			try {
				size_t len{ str.length() + str2.length() + 11 };
				size_t middleSize{ maxTableWidth > len ? maxTableWidth - len : 11 };

				std::string middle(middleSize, del);
				std::string result{ "#    " + str + middle + str2 + "    #\n" };

				return result;
			}
			catch (const std::exception& ex) {
				std::cout << ex.what();
				return std::string();
			}
		}


		std::string generatingStrings(const std::string&& str, const std::string&& str2, char del = ' ')
		{
			try {
				size_t len{ str.length() + str2.length() + 11 };
				size_t middleSize{ maxTableWidth > len ? maxTableWidth - len : 11 };

				std::string middle(middleSize, del);
				std::string result{ "#    " + str + middle + str2 + "    #\n" };

				return result;
			}
			catch (const std::exception& ex) {
				std::cout << ex.what();
				return std::string();
			}
		}

		void showAscendingList() 
		{
			if (flagClearArray) {
				addInStatusBar("Необходимо заполнить список!");
				return;
			}
			lst.directMergeSort(lst.begin(), lst.end());
			activeStatus = LAB2::SortingStatus::SortedAscending;
			addInStatusBar("Список успешно отсортирован в порядке возрастания!");
		}

		void showDescendingList() 
		{
			if (flagClearArray) {
				addInStatusBar("Необходимо заполнить список!");
				return;
			}
			lst.directMergeSort(lst.begin(), lst.end(), TypePredicat::greater);
			activeStatus = LAB2::SortingStatus::SortedDescending;
			addInStatusBar("Список успешно отсортирован в порядке убывания!");
		}

		void showShuffleList() 
		{
			if (flagClearArray) {
				addInStatusBar("Необходимо заполнить список!");
				return;
			}
			lst.shuffle();
			activeStatus = LAB2::SortingStatus::ShuffleSorted;
			addInStatusBar("Список успешно перемешан!");
		}


		void showClearList()
		{
			if (flagClearArray) {
				addInStatusBar("Очищать нечего, список ещё пуст!");
				return;
			}
			lst.clear();
			flagClearArray = true;
			activeStatus = LAB2::SortingStatus::NotStatus;
			addInStatusBar("Список успешно очищен!");
		}
	};
}

