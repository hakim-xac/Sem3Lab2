#include "MyApp.h"
#include <limits>
#include <random>
#include <ctime>




int LAB2::MyApp::getSizeList()
{
	return lst.size();
}
void LAB2::MyApp::clearList()
{
	lst.clear();
	lst.resize(sizeList);
}

void LAB2::MyApp::generatesListFromRandom()
{
	srand(static_cast<unsigned int>(time(0)));
	for (auto&& it : lst) it = rand() % std::numeric_limits<int>::max();
}
