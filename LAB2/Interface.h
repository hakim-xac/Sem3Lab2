#pragma once
#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <map>
#include "enums.h"
namespace LAB2 {
	class Interface
	{
		static std::ostream &out;
		static constexpr int maxTableWidth			{ 90 };
		static constexpr int maxTableColumns		{ 5 };
		static bool flagClearArray;
		static SortingStatus activeStatus;
		static std::queue <std::string> bufferForStatusBar;
		static const std::map <LAB2::SortingStatus, std::string> mapActiveStatus;
		static void clearList();
	public:
		static void addInStatusBar(const std::string& part);
		static void addInStatusBar(const std::string&& part);
		static void showHeader();
		static void showMenu();
		static void showStatusBar();
		static void showStatusList();
		static void showGeneratedRandom();

		static const std::string delimiter(char del = '=');

		static void printList(std::list<int>::const_iterator begin, std::list<int>::const_iterator end);   ///todo

		static std::string generatingStrings(const std::string& str, char del = ' ');
		static std::string generatingStrings(const std::string&& str, char del = ' ');
		static std::string generatingStrings(const std::string& str, const std::string& str2, char del = ' ');
		static std::string generatingStrings(const std::string&& str, const std::string&& str2, char del = ' ');
	};
}

