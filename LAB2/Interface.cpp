#include "Interface.h"
#include "MyApp.h"

void LAB2::Interface::showHeader()
{
	std::string header{ generatingStrings("Лабораторная работа № 2", "Быстрые методы сортировки последовательностей.") };
	std::string header2{ generatingStrings("Группа ПБ-11", "Хакимов А.C.") };

	std::string hr{ delimiter() };

	out << hr;
	out << header;
	out << delimiter('-');
	out << header2;
	out << hr;
}

void LAB2::Interface::showMenu()
{

	/// <summary>
	/// Вывод меню
	/// </summary>

	std::string hr{ delimiter() };

	out << delimiter(' ');
	out << hr;
	out << delimiter(' ');
	out << generatingStrings("Нажмите на клавишу и нажмите ВВОД");;
	out << delimiter('_');
	out << generatingStrings("( 1 )", "Генерация случайного массива", '.');
	out << generatingStrings("( 2 )", "Просмотр массива", '.');
	out << generatingStrings("( 3 )", "Очистить массив", '.');
	out << generatingStrings("( 4 )", "Изменить размер массива", '.');
	out << generatingStrings("( z )", "Сортировать массив методом прямого выбора по Возрастанию", '.');
	out << generatingStrings("( x )", "Сортировать массив методом прямого выбора по Убыванию", '.');
	out << generatingStrings("( c )", "Сортировать массив методом Шелла по Возрастанию", '.');
	out << generatingStrings("( v )", "Сортировать массив методом Шелла по Убыванию", '.');
	out << generatingStrings("( b )", "Сортировать массив методом Хоара по Возрастанию", '.');
	out << generatingStrings("( n )", "Сортировать массив методом Хоара по Убыванию", '.');
	out << generatingStrings("( 8 )", "Перемешать массив", '.');
	out << generatingStrings("( 9 )", "Показать подсчет серии и контрольной суммы", '.');
	out << generatingStrings("( 0 )", "Выход", '.');
	out << hr;
}

void LAB2::Interface::showGeneratedRandom()
{
	LAB2::MyApp::generatesListFromRandom();
	flagClearArray = false;
	activeStatus = LAB2::SortingStatus::RandomSorted;
	addInStatusBar("Список успешно заполнен случайными числами!");
}

void LAB2::Interface::addInStatusBar(const std::string& part)
{
	bufferForStatusBar.emplace(delimiter());
	bufferForStatusBar.emplace(delimiter(' '));
	bufferForStatusBar.emplace(generatingStrings(part));
	bufferForStatusBar.emplace(delimiter(' '));
	bufferForStatusBar.emplace(delimiter());
}

void LAB2::Interface::addInStatusBar(const std::string&& part)
{
	bufferForStatusBar.emplace(delimiter());
	bufferForStatusBar.emplace(delimiter(' '));
	bufferForStatusBar.emplace(generatingStrings(part));
	bufferForStatusBar.emplace(delimiter(' '));
	bufferForStatusBar.emplace(delimiter());
}

void LAB2::Interface::clearList()
{
	if (flagClearArray) {
		addInStatusBar("Очищать нечего, массив ещё пустой!");
		return;
	}
	MyApp::clearList();
	flagClearArray = true;
	activeStatus = LAB2::SortingStatus::NotStatus;
	addInStatusBar("Массив успешно очищен!");
}

void LAB2::Interface::showStatusBar()
{
	if (!bufferForStatusBar.empty())
	{
		std::string hr{ delimiter() };
		std::string hr2{ delimiter(' ') };

		out << hr;
		out << hr2;

		while (!bufferForStatusBar.empty()) {
			out << bufferForStatusBar.front();
			bufferForStatusBar.pop();
		}

		out << hr2;
		out << hr;

	}
}

std::string LAB2::Interface::generatingStrings(const std::string& str, char del)
{
	try {
		if (str.empty()) throw std::exception("Dont empty string! -> LAB2::MyApp::generatingStrings(const std::string& str)");
		int parity{ str.length() % 2 == 0 };
		size_t middleSize{ maxTableWidth > (str.length() + 2) ? (maxTableWidth - str.length() - 2) / 2 : 0 };

		std::string middle(middleSize - parity, del);
		std::string result{ "#" + middle + str + (parity ? " " : "") + middle + "#\n" };

		return result;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what();
		return std::string();
	}
}

std::string LAB2::Interface::generatingStrings(const std::string&& str, char del)
{
	try {
		if (str.empty()) throw std::exception("Dont empty string! -> LAB2::MyApp::generatingStrings(const std::string& str)");
		int parity{ str.length() % 2 == 0 };
		size_t middleSize{ maxTableWidth > (str.length() + 2) ? (maxTableWidth - str.length() - 2) / 2 : 0 };

		std::string middle(middleSize - parity, del);
		std::string result{ "#" + middle + str + (parity ? " " : "") + middle + "#\n" };

		return result;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what();
		return std::string();
	}
}

std::string LAB2::Interface::generatingStrings(const std::string& str, const std::string& str2, char del)
{
	try {
		size_t len{ str.length() + str2.length() + 11 };
		size_t middleSize{ maxTableWidth > len ? maxTableWidth - len : 11 };

		std::string middle(middleSize, del);
		std::string result{ "#    " + str + middle + str2 + "    #\n" };

		return result;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what();
		return std::string();
	}
}

std::string LAB2::Interface::generatingStrings(const std::string&& str, const std::string&& str2, char del)
{
	try {
		size_t len{ str.length() + str2.length() + 11 };
		size_t middleSize{ maxTableWidth > len ? maxTableWidth - len : 11 };

		std::string middle(middleSize, del);
		std::string result{ "#    " + str + middle + str2 + "    #\n" };

		return result;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what();
		return std::string();
	}
}

void LAB2::Interface::showStatusList() {
	out << generatingStrings("Статус Списка:", flagClearArray ? "ПУСТОЙ" : "ЗАПОЛНЕН");
	out << delimiter('-');
	out << generatingStrings("количество элементов списка:", std::to_string(MyApp::getSizeList()));
	out << delimiter();
}

const std::string LAB2::Interface::delimiter(char del) {
	std::string result(maxTableWidth, del);
	result.at(0) = '#';	result[result.size() - 2] = '#'; result.back() = '\n';
	return result;
}