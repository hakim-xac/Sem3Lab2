#pragma once

#include <list>								
#include <vector>								
#include <iterator>		
#include <numeric>		
#include <functional>		
#include <algorithm>
#include <limits>
#include <random>
#include <ctime>						
#include <iostream>						
#include "enums.h"						

namespace LAB2 {

	template <typename Type>
	class MyList
	{
	private:
		std::list<Type> lst;

	public:

		MyList() : lst(100) {};									// По умолчанию 100

		/*
		* Задаем итераторы
		*/
		auto begin()	{ return lst.begin();	}				
		auto end()		{ return lst.end();		}
		auto cbegin()	{ return lst.cbegin();	}
		auto cend()		{ return lst.cend();	}
		auto rbegin()	{ return lst.rbegin();	}
		auto rend()		{ return lst.rend();	}
		auto crbegin()	{ return lst.crbegin(); }
		auto crend()	{ return lst.crend();	}


		size_t  getSizeList() const { return lst.size(); }	// Возвращает размер списка


		void resize(size_t newSize)
		{
			/*
			*	Устанавливает новый размер списка
			*/
			lst.resize(newSize);
		}


		void clear()
		{
			/*
			*	Очищает список
			*/
			size_t maxSize{ lst.size() };
			lst.clear();
			lst.resize(maxSize);
		}


		void createRandomList()
		{
			/*
			*	Создает список со случайными значениями в диапазоне [0, max(type<int>)) <-(псевдокод)
			*/
			srand(static_cast<unsigned int>(time(0)));
			std::for_each(lst.begin(), lst.end(), [](int& item) {
				item = rand() % std::numeric_limits<int>::max();
			});
		}


		void shuffle()
		{
			/*
			*	Перемешивает список
			*/
			std::vector<Type> tmp(lst.size());
			std::copy(lst.begin(), lst.end(), tmp.begin());
			std::shuffle(tmp.begin(), tmp.end(), std::mt19937(std::random_device()()));
			std::copy(tmp.begin(), tmp.end(), lst.begin());
		}

		template <typename Iter>
		size_t directMergeSort(
			Iter begin
			, Iter end
			, TypePredicat typePredicat = TypePredicat::less
		)
		{
			/*
			*	Алгоритм сортировки
			* begin -	итератор начала списка
			* end	-	итератор конца списка
			* typePredicat -	предикат, по умолчанию TypePredicat::less (по оператору "<" )
			*/
			std::function<bool(Type, Type)> predicat;
			switch (typePredicat) {
			case TypePredicat::less:
				predicat = [](Type lhs, Type rhs) { return lhs < rhs;  };
				break;
			case TypePredicat::greater:
				predicat = [](Type lhs, Type rhs) { return lhs > rhs;  };
				break;
			}

			auto distance { std::distance(begin, end) };
			if (distance < 2)  return 0;

			auto middle{ std::next(begin, distance / 2) };


			size_t countsCompareAndMove{};
			countsCompareAndMove += directMergeSort(begin, middle, typePredicat);
			countsCompareAndMove += directMergeSort(middle, end,  typePredicat);

			std::vector<typename Iter::value_type> array;
			size_t counts{};
			std::tie(array, counts) = mergeSort(begin, middle, end, predicat);

			std::move(array.cbegin(), array.cend(), begin);

			return countsCompareAndMove + counts;
		}


		template <typename Iter, typename Comp>
		auto mergeSort(
			const Iter begin
			, const Iter middle
			, const Iter end
			, Comp predicat
		) -> std::pair<std::vector<typename Iter::value_type>, size_t>
		{
			/// <summary>
			/// Алгоритм слияния по итерируемых объектов в диапазоне [begin middle) и [middle, end)
			/// </summary>
			/// <typeparam name="Iter"> Тип итератора </typeparam>
			/// <typeparam name="Comp"> Тип предиката </typeparam>
			/// <param name="begin"> Итератор на начало списка </param>
			/// <param name="middle"> Итератор на середину списка </param>
			/// <param name="end"> Итератор на конец списка</param>
			/// <param name="predicat"> предикат </param>
			/// <returns>
			/// пара из вектора и числа сравнений(и перемещений)
			/// </returns>
			std::vector<typename Iter::value_type> array;

			Iter left{ begin }, right{ middle };
			size_t counts{};
			while (left != middle && right != end)
			{
				array.push_back((predicat(*left, *right)) ? *left++ : *right++ );
				++counts;
			}

			array.insert(array.end(), left, middle);
			array.insert(array.end(), right, end);

			return { std::move(array), counts };
		}


		template <typename Iter>
		Type sum(Iter begin, Iter end)
		{
			/// <summary>
			/// Суммирует все элементы
			/// </summary>
			/// <typeparam name="Iter"></typeparam>
			/// <param name="begin"></param>
			/// <param name="end"></param>
			/// <returns></returns>
			return std::accumulate(begin, end, Type(), [](Type a, Type b) {
				return a + b;
				});
		}

	};

}
