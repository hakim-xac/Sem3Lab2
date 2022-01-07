#pragma once

#include <list>								
#include <iterator>		
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

		MyList() : lst(100) {};


		auto begin()	{ return lst.begin();	}
		auto end()		{ return lst.end();		}
		auto cbegin()	{ return lst.cbegin();	}
		auto cend()		{ return lst.cend();	}
		auto rbegin()	{ return lst.rbegin();	}
		auto rend()		{ return lst.rend();	}
		auto crbegin()	{ return lst.crbegin(); }
		auto crend()	{ return lst.crend();	}


		size_t  getSizeList() const { return lst.size(); }


		void resize(size_t newSize)
		{
			lst.clear();
			lst.resize(newSize);
		}


		void clear()
		{
			size_t maxSize{ lst.size() };
			lst.clear();
			lst.resize(maxSize);
		}


		void createRandomList()
		{
			srand(static_cast<unsigned int>(time(0)));
			std::for_each(lst.begin(), lst.end(), [](int& item) {
				item = rand() % std::numeric_limits<int>::max();
			});
		}


		void shuffle()
		{
			std::vector<Type> tmp(lst.size());
			std::copy(lst.begin(), lst.end(), tmp.begin());
			std::shuffle(tmp.begin(), tmp.end(), std::mt19937(std::random_device()()));
			std::copy(tmp.begin(), tmp.end(), lst.begin());
		}


		void directMergeSort(
			std::list<Type>::iterator begin
			, std::list<Type>::iterator end
			, TypePredicat typePredicat = TypePredicat::less
			){

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

			if (distance < 2)  return;

			auto middle{ begin };
			std::advance(middle, distance / 2);

			directMergeSort(begin, middle, typePredicat);
			directMergeSort(middle, end,  typePredicat);

			std::inplace_merge(begin, middle, end, predicat);
		}

	};

}
