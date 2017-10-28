/*
=========================    Cpp Console Table
| Cpp | Console | Table |    version 1.0.0
=========================    https://github.com/Oradle/CppConsoleTable

Licensed under the MIT License <http://opensource.org/licenses/MIT>.
Copyright (c) 2017 Oradle

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once
#ifndef _CPP_CONSOLE_TABLE_
#define _CPP_CONSOLE_TABLE_

#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>

namespace samilton {
	// force declaration
	class ConsoleTable;

	class ConsoleString {
	public:
		ConsoleString &operator=(const std::string &val) {
			_str = val;
			return *this;
		}

		ConsoleString &operator=(const char *val) {
			_str = val;
			return *this;
		}

		ConsoleString &operator=(const long &val) {
			_str = std::to_string(val);
			return *this;
		}

		ConsoleString &operator=(const int &val) {
			_str = std::to_string(val);
			return *this;
		}

		ConsoleString &operator=(const double &val) {
			_str = std::to_string(val);
			return *this;
		}

		ConsoleString &operator=(const float &val) {
			_str = std::to_string(val);
			return *this;
		}

		ConsoleString &operator=(const bool &val) {
			if (val)
				_str = "true";
			else
				_str = "false";

			return *this;
		}
	private:
		friend std::ostream &operator<<(std::ostream &stream, ConsoleTable &table);

		std::string _str;
	};

	class ConsoleRow {
	public:
		~ConsoleRow() {
			for (auto &element : _rowData) {
				delete element.second;
			}
		}

		ConsoleString &operator[](const size_t &column) {
			try {
				return *_rowData.at(column);
			}
			catch (...) {
				_rowData[column] = new ConsoleString;
				return *_rowData[column];
			}
		}
	private:
		friend std::ostream &operator<<(std::ostream &stream, ConsoleTable &table);

		std::map<size_t, ConsoleString*> _rowData;
	};

	class ConsoleTable {
	public:
		enum class Alignment {
			left = 0,
			centre,
			right
		};

		ConsoleTable() {
			_alignment = Alignment::left;
			_leftIndent = 0;
			_rightIndent = 0;
		}

		ConsoleTable(const Alignment &alignment) {
			_alignment = alignment;
			_leftIndent = 0;
			_rightIndent = 0;
		}

		ConsoleTable(const size_t &leftIndent, const size_t &rightIndent, const Alignment &alignment = Alignment::left) {
			_leftIndent = leftIndent;
			_rightIndent = rightIndent;
			_alignment = alignment;
		}

		~ConsoleTable() {
			for (auto &element : _tableData) {
				delete element.second;
			}
		}

		void setAlignment(const Alignment &alignment) {
			_alignment = alignment;
		}

		void setIndent(const size_t &leftIndent, const size_t &rightIndent)
		{
			_leftIndent = leftIndent;
			_rightIndent = rightIndent;
		}

		ConsoleRow &operator[](const size_t &row) {
			try {
				return *_tableData.at(row);
			}
			catch (...) {
				_tableData[row] = new ConsoleRow;
				return *_tableData[row];
			}
		}

		friend std::ostream &operator<<(std::ostream &stream, ConsoleTable &table);
	private:
		std::map<size_t, ConsoleRow*> _tableData;
		Alignment _alignment;
		size_t _leftIndent, _rightIndent;
	};

	inline std::ostream &operator<<(std::ostream &stream, ConsoleTable &table) {
		// Return if table is empty
		if (table._tableData.size() == 0)
			return stream;
		
		// Calculation row and column
		size_t row = 0;
		size_t column = 0;
		for (auto &i : table._tableData) {
			row = std::max(row, i.first);
			for (auto &j : i.second->_rowData)
				column = std::max(column, j.first);
		}
		row++;
		column++;
	
		// Calculation width of every column
		std::vector<size_t> columnWidth;
		for (size_t i = 0; i < column; i++) {
			size_t tmp = 1;
			for (size_t j = 0; j < row; j++) {
				if (table._tableData[j] != nullptr && table._tableData[j]->_rowData[i] != nullptr) {
					tmp = std::max(tmp, table._tableData[j]->_rowData[i]->_str.size());
				}
			}
			columnWidth.push_back(tmp);
		}

		// Set up every symbol
		const char topRight = 187, topLeft = 201, downRight = 188, downLeft = 200;
		const char topDownSimple = 205, topSeparation = 203, downSeparation = 202;
		const char leftRightSimple = 186, leftSeparation = 204, rightSeparation = 185;
		const char centreSeparation = 206;

		if (table._alignment != ConsoleTable::Alignment::centre) {
			stream << std::right << topLeft << std::setfill(topDownSimple) << std::setw(columnWidth[0] + 1);

			if (column != 1) {
				for (size_t i = 1; i < column; i++) {
					stream << topSeparation << std::setw(columnWidth[i] + 1);
				}
			}
			stream << topRight << std::endl;

			for (size_t i = 0; i < row; i++) {
				if (table._alignment == ConsoleTable::Alignment::left)
					stream << std::left;
				else if (table._alignment == ConsoleTable::Alignment::right)
					stream << std::right;

				for (size_t j = 0; j < column; j++) {
					if (table._tableData[i] != nullptr && table._tableData[i]->_rowData[j] != nullptr) {
						stream << leftRightSimple << std::setfill(' ') << std::setw(columnWidth[j]) << table._tableData[i]->_rowData[j]->_str;
					}
					else {
						stream << leftRightSimple << std::setfill(' ') << std::setw(columnWidth[j]) << ' ';
					}
				}
				stream << std::right << leftRightSimple << std::endl;

				if (i == row - 1) {
					stream << downLeft << std::setfill(topDownSimple) << std::setw(columnWidth[0] + 1);

					if (column != 1) {
						for (size_t j = 1; j < column; j++) {
							stream << downSeparation << std::setw(columnWidth[j] + 1);
						}
					}
					stream << downRight << std::endl;
				}
				else {
					stream << leftSeparation << std::setfill(topDownSimple) << std::setw(columnWidth[0] + 1);

					if (column != 1) {
						for (size_t j = 1; j < column; j++) {
							stream << centreSeparation << std::setw(columnWidth[j] + 1);
						}
					}
					stream << rightSeparation << std::endl;
				}
			}
		}
		else {
			for (auto &i : table._tableData) {
				for (auto &j : i.second->_rowData) {
				}
			}
		}

		return stream;
	}
}

#endif // _CPP_CONSOLE_TABLE_