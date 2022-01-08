#pragma once
#include "Interface.h"

namespace LAB2 {
	template <typename TypeList>
	class ListInterface : public Interface<TypeList>
	{
		/// <summary>
		/// ����������� ����� ����������
		/// </summary>

		ListInterface() = delete;	// ��������� ��������� ����� � ������ ����������
	public:


		ListInterface(TypeList&& lst)	:	Interface<TypeList>(lst) {}


		void showPrintList()
		{
			/// <summary>
			/// �������� ������ ���� �� �� �� ���� � ����������� ���� ����
			/// </summary>
			if (!this->getFlagClearArray()) {

				this->addToStatusBar("����� ������");

				int lengthColumn{ (this->getMaxTableWidth() - 10) / this->getMaxTableColumns() };
				printList(std::string(lengthColumn, ' '));

			}
			else {
				this->addToStatusBar("������ ��� �� ��������!");
			}
		}


		void printList(const std::string&& defaultString)
		{
			/// <summary>
			/// ����������� ����� ������, �� ������ ����� ������ �� ��������� defaultString
			/// </summary>
			/// <param name="string">������ ������</param>
			std::string result{};
			for (auto it{ this->lst.begin() }, ite{ this->lst.end() }; it != ite; ++it) {

				std::string tmp{ defaultString };
				std::string num{ std::to_string(*it) };

				size_t len{ static_cast<size_t>(std::distance(this->lst.begin(), it)) };
				if ((len + 1) % this->getMaxTableColumns() != 0) {
					tmp.replace(tmp.size() - 1, 1, "|");
				}
				tmp.replace((tmp.length() - num.length()) / 2, num.length(), num);
				result += tmp;

				if ((len + 1) % this->getMaxTableColumns() == 0) {
					this->addToStatusBar(this->generatingStrings(result), false);
					this->addToStatusBar(this->delimiter('-'), false);
					result.clear();
				}
			}
			if (!result.empty()) this->addToStatusBar(this->generatingStrings(result));
		}


		void showGeneratedRandom()
		{
			/// <summary>
			/// ������� ���������� � �������, ��������� ���������� �������
			/// </summary>
			this->lst.createRandomList();

			this->setFlagClearArray(false);
			this->setActiveStatus(LAB2::SortingStatus::RandomSorted);
			this->addToStatusBar("������ ������� �������� ���������� �������!");
		}


		void showAscendingList()
		{
			/// <summary>
			/// ������� ���������� � �������, ���������� �� �����������
			/// </summary>
			if (this->getFlagClearArray()) {
				this->addToStatusBar("���������� ��������� ������!");
				return;
			}

			auto oldHashSum{ this->lst.sum(this->lst.begin(), this->lst.end()) };

			auto sum{ this->lst.directMergeSort(this->lst.begin(), this->lst.end()) };

			auto newHashSum{ this->lst.sum(this->lst.begin(), this->lst.end()) };

			this->setActiveStatus(LAB2::SortingStatus::SortedAscending);
			this->addToStatusBar("������ ������� ������������ � ������� �����������!");
			this->addToStatusBar(this->generatingStrings("����������� ����� �� ����������:",	std::to_string(oldHashSum)), false);
			this->addToStatusBar(this->generatingStrings("����������� ����� ����� ����������:", std::to_string(newHashSum)), false);
			this->addToStatusBar(this->generatingStrings("���������� ���������:", std::to_string(sum)), false);
			this->addToStatusBar(this->generatingStrings("���������� ���������:", std::to_string(sum)), false);

		}


		void showDescendingList()
		{
			/// <summary>
			/// ������� ���������� � �������, ���������� �� ��������
			/// </summary>
			if (this->getFlagClearArray()) {
				this->addToStatusBar("���������� ��������� ������!");
				return;
			}

			auto oldHashSum{ this->lst.sum(this->lst.begin(), this->lst.end()) };

			auto sum{ this->lst.directMergeSort(this->lst.begin(), this->lst.end(), TypePredicat::greater) };

			auto newHashSum{ this->lst.sum(this->lst.begin(), this->lst.end()) };

			this->setActiveStatus(LAB2::SortingStatus::SortedDescending);
			this->addToStatusBar("������ ������� ������������ � ������� ��������!");
			this->addToStatusBar(this->generatingStrings("����������� ����� �� ����������:", std::to_string(oldHashSum)), false);
			this->addToStatusBar(this->generatingStrings("����������� ����� ����� ����������:", std::to_string(newHashSum)), false);
			this->addToStatusBar(this->generatingStrings("���������� ���������:", std::to_string(sum)), false);
			this->addToStatusBar(this->generatingStrings("���������� ���������:", std::to_string(sum)), false);
		}


		void showShuffleList()
		{
			/// <summary>
			/// ������� ���������� � �������, ������������� ������
			/// </summary>
			if (this->getFlagClearArray()) {
				this->addToStatusBar("���������� ��������� ������!");
				return;
			}
			this->lst.shuffle();
			this->setActiveStatus(LAB2::SortingStatus::ShuffleSorted);
			this->addToStatusBar("������ ������� ���������!");
		}


		void showClearList()
		{
			/// <summary>
			/// ������� ���������� � �������, ������� ������
			/// </summary>
			if (this->getFlagClearArray()) {
				this->addToStatusBar("������� ������, ������ ��� ����!");
				return;
			}
			this->lst.clear();
			this->setFlagClearArray(true);
			this->setActiveStatus(LAB2::SortingStatus::NotStatus);
			this->addToStatusBar("������ ������� ������!");
		}


		void showResizeList()
		{
			/// <summary>
			/// ������� ���������� � �������, ��������� �������
			/// </summary>
			auto newSize{ this->lst.getSizeList() + 100};
			if (newSize > 500) newSize = 100;
			this->lst.resize(newSize);
			if(!this->getFlagClearArray()) showClearList();
			this->addToStatusBar("������ ������� �������!");
		}
	};
}

