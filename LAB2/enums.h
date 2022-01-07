#pragma once
namespace LAB2 {
	enum class Keys {
		Exit = 48									// Key 0, Выход
		, CreateRandomList = 49						// Key 2, Создать список в случайном порядке
		, AscendingList = 50						// Key 1, Отсортировать список по возрастанию
		, DesciningList = 51 						// Key 2, Отсортировать список по убыванию
		, ShuffleList = 52							// Key 3, Перемешать список
		, PrintList = 53							// Key 4, Распечатать список
		, ClearList = 54							// Key 5, Очистить список
		, ResizeList = 57							// Key 9, Изменить размер
		, 
	};

	enum class SortingStatus {
		SortedAscending, SortedDescending, ShuffleSorted, RandomSorted, NotStatus
	};

	enum class TypePredicat { less, greater };
}




