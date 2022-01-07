#pragma once
#include "Interface.h"

namespace LAB2 {
	template <typename TypeList>
	class ListInterface : public Interface<TypeList>
	{
		ListInterface() = delete;
	public:


		ListInterface(TypeList&& lst)	:	Interface<TypeList>(lst) {}


		void showPrintList()
		{
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
			this->lst.createRandomList();

			this->setFlagClearArray(false);
			this->setActiveStatus(LAB2::SortingStatus::RandomSorted);
			this->addToStatusBar("������ ������� �������� ���������� �������!");
		}


		void showAscendingList()
		{
			if (this->getFlagClearArray()) {
				this->addToStatusBar("���������� ��������� ������!");
				return;
			}
			this->lst.directMergeSort(this->lst.begin(), this->lst.end());
			this->setActiveStatus(LAB2::SortingStatus::SortedAscending);
			this->addToStatusBar("������ ������� ������������ � ������� �����������!");
		}


		void showDescendingList()
		{
			if (this->getFlagClearArray()) {
				this->addToStatusBar("���������� ��������� ������!");
				return;
			}
			this->lst.directMergeSort(this->lst.begin(), this->lst.end(), TypePredicat::greater);
			this->setActiveStatus(LAB2::SortingStatus::SortedDescending);
			this->addToStatusBar("������ ������� ������������ � ������� ��������!");
		}


		void showShuffleList()
		{
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
			auto newSize{ this->lst.getSizeList() + 100};
			if (newSize > 500) newSize = 100;
			this->lst.resize(newSize);
			showClearList();
			this->addToStatusBar("������ ������� �������!");
		}
	};
}

