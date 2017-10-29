#include <iostream>

#include "CppConsoleTable.hpp"

using ConsoleTable = samilton::ConsoleTable;

int main()
{
	ConsoleTable table(2, 3, ConsoleTable::Alignment::right);

	table[0][0] = "some";
	table[1][3] = true;
	table[2][1] = 10;
	table[3][3] = "bla";
	table[2][2] = 2.354;
	table[0][1] = false;

	std::cout << table;

	system("pause");
}