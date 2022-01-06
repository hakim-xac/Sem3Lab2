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
			{ LAB2::SortingStatus::SortedAscending,     "�� �����������" },
			{ LAB2::SortingStatus::SortedDescending,    "�� ��������" },
			{ LAB2::SortingStatus::ShuffleSorted,       "���������" },
			{ LAB2::SortingStatus::RandomSorted,        "��������" },
			{ LAB2::SortingStatus::NotStatus,           "�� ����������" } 
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
			std::string header{ generatingStrings("������������ ������ � 2", "������� ������ ���������� �������������������.") };
			std::string header2{ generatingStrings("������ ��-11", "������� �.C.") };

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
			out << generatingStrings("������� �� ������� � ������� ����");
			out << delimiter('_');
			out << generatingStrings("( 1 )", "��������� ���������� �������", '.');
			out << generatingStrings("( 2 )", "������������� ������ �� �����������", '.');
			out << generatingStrings("( 3 )", "������������� ������ �� ��������", '.');
			out << generatingStrings("( 4 )", "���������� ������", '.');
			out << generatingStrings("( 5 )", "����������� ������ �� �����", '.');
			out << generatingStrings("( 6 )", "�������� ������", '.');
			out << generatingStrings("( 0 )", "�����", '.');
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
			out << generatingStrings("������ ������:", flagClearArray ? "������" : "��������");
			out << delimiter('-');
			out << generatingStrings("���������� ��������� ������:", std::to_string(lst.getSizeList()));
			out << delimiter('-');
			out << generatingStrings("������ ���������� ������:", mapActiveStatus.at(activeStatus));
			out << delimiter();
		}


		void showGeneratedRandom()
		{
			lst.createRandomList();
			
			flagClearArray = false;
			activeStatus = LAB2::SortingStatus::RandomSorted;
			addInStatusBar("������ ������� �������� ���������� �������!");
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

				addInStatusBar("����� ������");

				int lengthColumn{ (maxTableWidth - 10) / maxTableColumns };
				printList(std::string(lengthColumn, ' '));

			}
			else {
				addInStatusBar("������ ��� �� ��������!");
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
				addInStatusBar("���������� ��������� ������!");
				return;
			}
			lst.directMergeSort(lst.begin(), lst.end());
			activeStatus = LAB2::SortingStatus::SortedAscending;
			addInStatusBar("������ ������� ������������ � ������� �����������!");
		}

		void showDescendingList() 
		{
			if (flagClearArray) {
				addInStatusBar("���������� ��������� ������!");
				return;
			}
			lst.directMergeSort(lst.begin(), lst.end(), TypePredicat::greater);
			activeStatus = LAB2::SortingStatus::SortedDescending;
			addInStatusBar("������ ������� ������������ � ������� ��������!");
		}

		void showShuffleList() 
		{
			if (flagClearArray) {
				addInStatusBar("���������� ��������� ������!");
				return;
			}
			lst.shuffle();
			activeStatus = LAB2::SortingStatus::ShuffleSorted;
			addInStatusBar("������ ������� ���������!");
		}


		void showClearList()
		{
			if (flagClearArray) {
				addInStatusBar("������� ������, ������ ��� ����!");
				return;
			}
			lst.clear();
			flagClearArray = true;
			activeStatus = LAB2::SortingStatus::NotStatus;
			addInStatusBar("������ ������� ������!");
		}
	};
}

