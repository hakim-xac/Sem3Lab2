#pragma once
#include <iostream>
#include <list>									
#include "enums.h"							

namespace LAB2 {
	class MyApp
	{
		static int sizeList;
		static std::list<int> lst;

	public:

		static int  getSizeList					();
		static void clearList					();		
		static void generatesListFromRandom		();

	};
}
