#include <iostream>

#include "CppConsoleTable.hpp"

using ConsoleTable = samilton::ConsoleTable;

int main()
{
	// Creating table with indents and alignment
	ConsoleTable table(1, 2, samilton::Alignment::centre);

	// Assign data to table
	table[0][0] = "Some char string";
	table[1][3] = true; // boolean data
	table[2](samilton::Alignment::right)[1] = 10; // int data with own row alignment to right
	table[3][3] = std::string("Some std::string");
	table[2][2] = 2.354; // double data
	table[0][1](samilton::Alignment::left) = "Some char multi string.\nWorks fine!\nEven with own alignment";

	table.clear(); // clear all table cells
	table.addColumn({ 1, 2, 3 }); // add new column to table with elements
	table.addRow({ "FirstString", "SecondString", "ThirdString" }); // add new row to table with elements
	table.assign({ {"stringA1", "stringA2"}, {"stringB1"}, {"stringC1", "stringC2", "stringC3"} }); // clear all table and assign new with elements
	table = { {"stringA1", "stringA2"}, {"stringB1"}, {"stringC1", "stringC2", "stringC3"} }; // same as assign but with overloaded operator

	// Change settings of table
	table.setAlignment(samilton::Alignment::centre); // set alignment of all table
	table.setIndent(2, 1); // set indent of all table

	ConsoleTable::TableChars chars; // creating TableChars struct with standard symbols setup
	chars.centreSeparation = '+'; // changing symbol in struct
	table.setTableChars(chars); // set TableChars struct as new symbol setup

	// Output table
	std::cout << table << std::endl;

	system("pause");
}