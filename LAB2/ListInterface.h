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

				this->addToStatusBar("Вывод списка");

				int lengthColumn{ (this->getMaxTableWidth() - 10) / this->getMaxTableColumns() };
				printList(std::string(lengthColumn, ' '));

			}
			else {
				this->addToStatusBar("Список ещё не заполнен!");
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
			this->addToStatusBar("Список успешно заполнен случайными числами!");
		}


		void showAscendingList()
		{
			if (this->getFlagClearArray()) {
				this->addToStatusBar("Необходимо заполнить список!");
				return;
			}

			auto oldHashSum{ this->lst.sum(this->lst.begin(), this->lst.end()) };

			auto sum{ this->lst.directMergeSort(this->lst.begin(), this->lst.end()) };

			auto newHashSum{ this->lst.sum(this->lst.begin(), this->lst.end()) };

			this->setActiveStatus(LAB2::SortingStatus::SortedAscending);
			this->addToStatusBar("Список успешно отсортирован в порядке возрастания!");
			this->addToStatusBar(this->generatingStrings("Контрольная сумма до сортировки:",	std::to_string(oldHashSum)), false);
			this->addToStatusBar(this->generatingStrings("Контрольная сумма после сортировки:", std::to_string(newHashSum)), false);
			this->addToStatusBar(this->generatingStrings("Количество сравнений:", std::to_string(sum)), false);
			this->addToStatusBar(this->generatingStrings("Количество пересылок:", std::to_string(sum)), false);

		}


		void showDescendingList()
		{
			if (this->getFlagClearArray()) {
				this->addToStatusBar("Необходимо заполнить список!");
				return;
			}

			auto oldHashSum{ this->lst.sum(this->lst.begin(), this->lst.end()) };

			auto sum{ this->lst.directMergeSort(this->lst.begin(), this->lst.end(), TypePredicat::greater) };

			auto newHashSum{ this->lst.sum(this->lst.begin(), this->lst.end()) };

			this->setActiveStatus(LAB2::SortingStatus::SortedDescending);
			this->addToStatusBar("Список успешно отсортирован в порядке убывания!");
			this->addToStatusBar(this->generatingStrings("Контрольная сумма до сортировки:", std::to_string(oldHashSum)), false);
			this->addToStatusBar(this->generatingStrings("Контрольная сумма после сортировки:", std::to_string(newHashSum)), false);
			this->addToStatusBar(this->generatingStrings("Количество сравнений:", std::to_string(sum)), false);
			this->addToStatusBar(this->generatingStrings("Количество пересылок:", std::to_string(sum)), false);
		}


		void showShuffleList()
		{
			if (this->getFlagClearArray()) {
				this->addToStatusBar("Необходимо заполнить список!");
				return;
			}
			this->lst.shuffle();
			this->setActiveStatus(LAB2::SortingStatus::ShuffleSorted);
			this->addToStatusBar("Список успешно перемешан!");
		}


		void showClearList()
		{
			if (this->getFlagClearArray()) {
				this->addToStatusBar("Очищать нечего, список ещё пуст!");
				return;
			}
			this->lst.clear();
			this->setFlagClearArray(true);
			this->setActiveStatus(LAB2::SortingStatus::NotStatus);
			this->addToStatusBar("Список успешно очищен!");
		}


		void showResizeList()
		{
			auto newSize{ this->lst.getSizeList() + 100};
			if (newSize > 500) newSize = 100;
			this->lst.resize(newSize);
			if(!this->getFlagClearArray()) showClearList();
			this->addToStatusBar("Список успешно Изменен!");
		}
	};
}

