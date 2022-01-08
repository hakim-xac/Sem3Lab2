#pragma once
#include <string>
#include <queue>
#include <map>
#include "enums.h"
#include "MyList.h"

namespace LAB2 {

	template <typename TypeList>
	class Interface
	{
	/// <summary>
	/// ������� ����� ����������
	/// </summary>
	/// <typeparam name="TypeList">��� "MyList"</typeparam>
	private:
		std::ostream& out			{ std::cout };								// ����� ������
		int maxTableWidth			{ 90 };										// ������ ��������� ������
		int maxTableColumns			{ 5 };										// ���������� ������� ��� ������ ������
		std::queue <std::string> bufferForStatusBar	{};							// ������� ��� ������ ����

		const std::map <LAB2::SortingStatus, std::string> mapActiveStatus	{
			///
			/// ����������� enum class SortingStatus � ������������������� ���
			///
			{ LAB2::SortingStatus::SortedAscending,     "�� �����������" },
			{ LAB2::SortingStatus::SortedDescending,    "�� ��������" },
			{ LAB2::SortingStatus::ShuffleSorted,       "���������" },
			{ LAB2::SortingStatus::RandomSorted,        "��������" },
			{ LAB2::SortingStatus::NotStatus,           "�� ����������" } 
		};

		Interface() = delete;													// ��������� ��������� ������ �����

	protected:


		TypeList lst;
		bool flagClearArray{ true };
		SortingStatus activeStatus	{ SortingStatus::NotStatus };


	public:


		Interface(TypeList& lst) :	lst(lst) {}
		Interface(TypeList&& lst) : lst(lst) {}

		/// <summary>
		/// ������� ��������� �����
		/// </summary>
		auto getMaxTableWidth()		const				{	return maxTableWidth;		}
		auto getMaxTableColumns()	const				{	return maxTableColumns;		}
		bool getFlagClearArray()	const				{	return flagClearArray;		}
		auto getActiveStatus()		const				{	return activeStatus;		}

		/// <summary>
		/// ������� ��������� �����
		/// </summary>
		void setFlagClearArray(bool flag)				{	flagClearArray = flag;		}
		void setActiveStatus(SortingStatus newStatus)	{	activeStatus = newStatus;	}


		void addToStatusBar(const std::string& str, bool isFormated=true)
		{
			/// <summary>
			/// ��������� lvalue ������ � ���������� � � ������� ������ ����
			/// </summary>
			/// 
			/// <param name="isFormated">������������� ������ �� ���������?</param>
			/// 
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
			/// <summary>
			/// ��������� rvalue ������ � ���������� � � ������� ������ ����
			/// </summary>
			/// 
			/// <param name="isFormated">������������� ������ �� ���������?</param>
			/// 
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
			/// <summary>
			/// ������� ���������
			/// </summary>
			std::string header{ generatingStrings("������������ ������ � 2", "������� ������ ���������� �������������������.") };
			std::string header2{ generatingStrings("������ ��-11", "������� �.C.") };

			std::string hr{ delimiter() };

			out << hr;
			out << header;
			out << delimiter('-');
			out << header2;
			out << hr;
		}


		constexpr void showMenu()
		{
			/// <summary>
			/// ������� ����
			/// </summary>
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
			/// <summary>
			/// ������� ������ ���
			/// </summary>
			std::string hr{ delimiter(' ')};

			out << hr;

			while (!bufferForStatusBar.empty())
			{
				out << bufferForStatusBar.front();
				bufferForStatusBar.pop();
			}			

			out << hr;
			
		}


		void showStatusList()
		{
			/// <summary>
			/// ������� ��������� ���������� � ������
			/// </summary>
			out << generatingStrings("������ ������:", getFlagClearArray() ? "������" : "��������");
			out << delimiter('-');
			out << generatingStrings("���������� ��������� ������:", std::to_string(lst.getSizeList()));
			out << delimiter('-');
			out << generatingStrings("������ ���������� ������:", mapActiveStatus.at(getActiveStatus()));
			out << delimiter();
		}



		const std::string delimiter(char del = '=') const
		{
			/// <summary>
			/// ������ ������ �����������, ����� ����������� ��� ������
			/// </summary>
			/// <param name="del"> ������ �����������</param>
			/// <returns></returns>
			std::string result(maxTableWidth, del);
			result.at(0) = '#';	result[result.size() - 2] = '#'; result.back() = '\n';
			return result;
		}


		const std::string generatingStrings(const std::string& str, char del = ' ') const
		{
			/// <summary>
			/// ���������� ������������� ������ � ������� str �� ������
			/// ��������� lvalue ������
			/// </summary>
			/// <param name="del">��������� "�������" ���� ��������</param>
			
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
			/// <summary>
			/// ���������� ������������� ������ � ������� str �� ������
			/// ��������� rvalue ������
			/// </summary>
			/// <param name="del">��������� "�������" ���� ��������</param>
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
			/// <summary>
			/// ���������� ������������� ������ � ������� str ����� �� ���� � str2 ������ �� ����
			/// ��������� lvalue ������
			/// </summary>
			/// <param name="del">��������� "�������" ���� ��������</param>
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
			/// <summary>
			/// ���������� ������������� ������ � ������� str ����� �� ���� � str2 ������ �� ����
			/// ��������� rvalue ������
			/// </summary>
			/// <param name="del">��������� "�������" ���� ��������</param>
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

