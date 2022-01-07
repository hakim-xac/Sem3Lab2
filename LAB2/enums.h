#pragma once
namespace LAB2 {
	enum class Keys {
		Exit = 48									// Key 0, �����
		, CreateRandomList = 49						// Key 2, ������� ������ � ��������� �������
		, AscendingList = 50						// Key 1, ������������� ������ �� �����������
		, DesciningList = 51 						// Key 2, ������������� ������ �� ��������
		, ShuffleList = 52							// Key 3, ���������� ������
		, PrintList = 53							// Key 4, ����������� ������
		, ClearList = 54							// Key 5, �������� ������
		, ResizeList = 57							// Key 9, �������� ������
		, 
	};

	enum class SortingStatus {
		SortedAscending, SortedDescending, ShuffleSorted, RandomSorted, NotStatus
	};

	enum class TypePredicat { less, greater };
}




