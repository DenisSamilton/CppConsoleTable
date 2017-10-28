#include <iostream>
#include <iomanip>

#include "CppConsoleTable.hpp"

using namespace std;
using namespace samilton;

int main()
{
	ConsoleTable table(ConsoleTable::Alignment::right);

	table[0][0] = "some";
	table[1][3] = true;
	table[2][1] = 10;
	table[3][3] = "bla";
	table[2][2] = 2.354;
	table[0][1] = false;

	cout << table;

	system("pause");
}