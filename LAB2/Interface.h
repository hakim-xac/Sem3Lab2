#pragma once
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
	private:
		std::ostream& out			{ std::cout };
		int maxTableWidth			{ 90 };
		int maxTableColumns			{ 5 };
		std::queue <std::string> bufferForStatusBar	{};

		const std::map <LAB2::SortingStatus, std::string> mapActiveStatus	{
			{ LAB2::SortingStatus::SortedAscending,     "По возрастанию" },
			{ LAB2::SortingStatus::SortedDescending,    "По убыванию" },
			{ LAB2::SortingStatus::ShuffleSorted,       "Перемешан" },
			{ LAB2::SortingStatus::RandomSorted,        "Случайно" },
			{ LAB2::SortingStatus::NotStatus,           "Не сортирован" } 
		};

		Interface() = delete;

	protected:


		TypeList lst;
		bool flagClearArray{ true };
		SortingStatus activeStatus	{ SortingStatus::NotStatus };


	public:


		Interface(TypeList& lst) :	lst(lst) {}
		Interface(TypeList&& lst) : lst(lst) {}


		auto getMaxTableWidth()		const				{	return maxTableWidth;		}
		auto getMaxTableColumns()	const				{	return maxTableColumns;		}
		bool getFlagClearArray()	const				{	return flagClearArray;		}
		auto getActiveStatus()		const				{	return activeStatus;		}

		void setFlagClearArray(bool flag)				{	flagClearArray = flag;		}
		void setActiveStatus(SortingStatus newStatus)	{	activeStatus = newStatus;	}


		auto addToStatusBar(const std::string& str, bool isFormated=true)
		{
			if (!isFormated) {
				bufferForStatusBar.emplace(str);
				return;
			}

			bufferForStatusBar.emplace(delimiter());
			bufferForStatusBar.emplace(delimiter(' '));
			bufferForStatusBar.emplace(generatingStrings(str));
			bufferForStatusBar.emplace(delimiter(' '));
			bufferForStatusBar.emplace(delimiter());
		}


		auto addToStatusBar(const std::string&& str, bool isFormated=true)
		{
			if (!isFormated) {
				bufferForStatusBar.emplace(str);
				return;
			}

			bufferForStatusBar.emplace(delimiter());
			bufferForStatusBar.emplace(delimiter(' '));
			bufferForStatusBar.emplace(generatingStrings(str));
			bufferForStatusBar.emplace(delimiter(' '));
			bufferForStatusBar.emplace(delimiter());
		}


		constexpr void showHeader() 
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


		constexpr void showMenu()
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
			out << generatingStrings("Статус Списка:", getFlagClearArray() ? "ПУСТОЙ" : "ЗАПОЛНЕН");
			out << delimiter('-');
			out << generatingStrings("количество элементов списка:", std::to_string(lst.getSizeList()));
			out << delimiter('-');
			out << generatingStrings("Статус сортировки списка:", mapActiveStatus.at(getActiveStatus()));
			out << delimiter();
		}



		const std::string delimiter(char del = '=') const
		{
			std::string result(maxTableWidth, del);
			result.at(0) = '#';	result[result.size() - 2] = '#'; result.back() = '\n';
			return result;
		}


		const std::string generatingStrings(const std::string& str, char del = ' ') const
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


		const std::string generatingStrings(const std::string&& str, char del = ' ') const
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


		const std::string generatingStrings(const std::string& str, const std::string& str2, char del = ' ') const 
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


		const std::string generatingStrings(const std::string&& str, const std::string&& str2, char del = ' ') const
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


	};
}

