#pragma once
#include "Interface.h"

namespace LAB2 {
	template <typename TypeList>
	class ListInterface : public Interface<TypeList>
	{
		/// <summary>
		/// Производный класс интерфейса
		/// </summary>

		ListInterface() = delete;	// Запрещаем создавать класс с пустым параметром
	public:


		ListInterface(TypeList&& lst)	:	Interface<TypeList>(lst) {}


		void showPrintList()
		{
			/// <summary>
			/// Печатает список если не он не пуст и информирует если пуст
			/// </summary>
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
			/// <summary>
			/// Форматирует вывод списка, за основу берет строку из параметра defaultString
			/// </summary>
			/// <param name="string">шаблон строки</param>
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
			/// выводит информацию о событии, генерация случайными числами
			/// </summary>
			this->lst.createRandomList();

			this->setFlagClearArray(false);
			this->setActiveStatus(LAB2::SortingStatus::RandomSorted);
			this->addToStatusBar("Список успешно заполнен случайными числами!");
		}


		void showAscendingList()
		{
			/// <summary>
			/// выводит информацию о событии, Сортировка по возрастанию
			/// </summary>
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
			/// <summary>
			/// выводит информацию о событии, Сортировка по убыванию
			/// </summary>
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
			/// <summary>
			/// выводит информацию о событии, перемешивании списка
			/// </summary>
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
			/// <summary>
			/// выводит информацию о событии, очистка списка
			/// </summary>
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
			/// <summary>
			/// выводит информацию о событии, изменение размера
			/// </summary>
			auto newSize{ this->lst.getSizeList() + 100};
			if (newSize > 500) newSize = 100;
			this->lst.resize(newSize);
			if(!this->getFlagClearArray()) showClearList();
			this->addToStatusBar("Список успешно Изменен!");
		}
	};
}

