/*
 =========================    Cpp Console Table
 | Cpp | Console | Table |    version 1.3.0
 =========================    https://github.com/DenisSamilton/CppConsoleTable

Licensed under the MIT License <http://opensource.org/licenses/MIT>.
Copyright (c) 2019 DenisSamilton

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

#include <algorithm> // max
#include <iomanip> // setfill, setw, right, left
#include <iostream> // ostream, endl
#include <initializer_list> // initializer_list
#include <map> // map
#include <optional> // optional
#include <stdexcept> // invalid_argument, out_of_range
#include <string> // string, to_string
#include <type_traits> // enable_if, is_arithmetic, is_same, remove_pointer
#include <vector> // vector

namespace samilton {
	// force declaration
	class ConsoleTable;
	class ConsoleRow;

	enum class Alignment {
		left = 0,
		centre,
		right
	};

	class ConsoleString {
	public:
		ConsoleString() = default;

		ConsoleString(const ConsoleString &obj) {
			*this = obj;
		}

		void clear() {
			_str.clear();
		}

		ConsoleString &operator=(const std::string &val) {
			clear();
			_parseString(val);
			return *this;
		}

		ConsoleString &operator=(const char *val) {
			clear();
			_parseString(std::string(val));
			return *this;
		}

		ConsoleString &operator=(const char &val) {
			clear();
			_parseString(std::string(1, val));
			return *this;
		}

		template<class T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
		ConsoleString &operator=(const T &val) {
			clear();
			_str.push_back(std::to_string(val));
			return *this;
		}

		ConsoleString &operator=(const bool &val) {
			clear();

			if (val)
				_str.emplace_back("true");
			else
				_str.emplace_back("false");

			return *this;
		}

		ConsoleString &operator=(const ConsoleString &obj) {
			clear();
			_alignment = obj._alignment;
			_str = obj._str;

			return *this;
		}

		template<typename T, typename... Args>
		ConsoleString &operator()(T firstArg, Args... args) {
			if constexpr (std::is_same<T, Alignment>::value) {
				_alignment = firstArg;
			}
			else {
				if constexpr (!std::is_same<T, nullptr_t>::value) {
					throw std::invalid_argument("args");
				}
			}

			if constexpr (!std::is_same<T, nullptr_t>::value)
				(*this)(args..., nullptr);

			return *this;
		}

		~ConsoleString() {
			clear();
		}
	private:
		friend std::ostream &operator<<(std::ostream &stream, ConsoleTable &table);

		void _parseString(const std::string &val) {
			auto tmpIterator = val.begin();
			for (auto i = val.begin(); i < val.end(); ++i) {
				if (*i == '\n') {
					_str.emplace_back(tmpIterator, i);
					tmpIterator = i + 1;
				}
			}

			_str.emplace_back(tmpIterator, val.end());
		}

		std::vector<std::string> _str;
		std::optional<Alignment> _alignment;
	};

	class ConsoleRow {
	public:
		ConsoleRow(ConsoleTable *parent) {
			_parent = parent;
		}

		ConsoleRow(const ConsoleRow &obj) = delete;

		ConsoleRow(const ConsoleRow &obj, ConsoleTable *parent) {
			_parent = parent;
			*this = obj;
		}

		void clear() {
			for (auto &i : _rowData) {
				delete i.second;
			}
			_rowData.clear();
		}

		ConsoleRow &operator=(const ConsoleRow &obj) {
			clear();

			for (auto &i : obj._rowData)
				_rowData[i.first] = new ConsoleString(*i.second);

			return *this;
		}

		template<typename T, typename... Args>
		ConsoleRow &operator()(T firstArg, Args... args) {
			if constexpr (std::is_same<T, Alignment>::value) {
				_alignment = firstArg;
			}
			else {
				if constexpr (!std::is_same<T, nullptr_t>::value) {
					throw std::invalid_argument("args");
				}
			}

			if constexpr (!std::is_same<T, nullptr_t>::value)
				(*this)(args..., nullptr);

			return *this;
		}

		~ConsoleRow() {
			clear();
		}

		ConsoleString &operator[](size_t column);
	private:
		friend std::ostream &operator<<(std::ostream &stream, ConsoleTable &table);

		ConsoleTable *_parent;
		std::map<size_t, ConsoleString*> _rowData;
		std::optional<Alignment> _alignment;
	};

	class ConsoleTable {
	public:
		struct TableChars {
			unsigned char topRight = 187, topLeft = 201, downRight = 188, downLeft = 200;
			unsigned char topDownSimple = 205, topSeparation = 203, downSeparation = 202;
			unsigned char leftRightSimple = 186, leftSeparation = 204, rightSeparation = 185;
			unsigned char centreSeparation = 206;
		};

		ConsoleTable() {
			_alignment = Alignment::left;
			_leftIndent = _rightIndent = _rowSize = _columnSize = 0;
		}

		ConsoleTable(const Alignment &alignment) {
			_alignment = alignment;
			_leftIndent = _rightIndent = _rowSize = _columnSize = 0;
		}

		ConsoleTable(const size_t &leftIndent, const size_t &rightIndent, const Alignment &alignment = Alignment::left) {
			_leftIndent = leftIndent;
			_rightIndent = rightIndent;
			_alignment = alignment;
			_rowSize = _columnSize = 0;
		}

		ConsoleTable(const ConsoleTable &obj) {
			*this = obj;
		}

		~ConsoleTable() {
			clear();
		}

		template<class T, 
		class = typename std::enable_if<std::is_arithmetic<T>::value || 
		std::is_same<std::string, T>::value || 
		std::is_same<char*, T>::value>::type>
		void addRow(const std::vector<T> &row) {
			const size_t tmp = _rowSize;
			for (size_t i = 0; i < row.size(); i++) {
				(*this)[tmp][i] = row[i];
			}
		}

		template<class T,
		class = typename std::enable_if<std::is_arithmetic<typename std::remove_pointer<T>::type>::value ||
		std::is_same<std::string, typename std::remove_pointer<T>::type>::value>::type>
		void addRow(const T row, const size_t &size) {
			const size_t tmp = _rowSize;
			for (size_t i = 0; i < size; i++) {
				(*this)[tmp][i] = row[i];
			}
		}

		template<class T,
		class = typename std::enable_if<std::is_arithmetic<T>::value ||
		std::is_same<std::string, T>::value ||
		std::is_same<const char*, T>::value>::type>
		void addRow(const std::initializer_list<T> &row) {
			const size_t tmp = _rowSize;
			for (size_t i = 0; i < row.size(); i++) {
				(*this)[tmp][i] = *(row.begin() + i);
			}
		}

		template<class T,
		class = typename std::enable_if<std::is_arithmetic<T>::value ||
		std::is_same<std::string, T>::value ||
		std::is_same<char*, T>::value>::type>
		void addColumn(const std::vector<T> &column) {
			const size_t tmp = _columnSize;
			for (size_t i = 0; i < column.size(); i++) {
				(*this)[i][tmp] = column[i];
			}
		}

		template<class T,
		class = typename std::enable_if<std::is_arithmetic<typename std::remove_pointer<T>::type>::value ||
		std::is_same<std::string*, T>::value>::type>
		void addColumn(const T column, const size_t &size) {
			const size_t tmp = _columnSize;
			for (size_t i = 0; i < size; i++) {
				(*this)[i][tmp] = column[i];
			}
		}

		template<class T,
		class = typename std::enable_if<std::is_arithmetic<T>::value ||
		std::is_same<std::string, T>::value ||
		std::is_same<const char*, T>::value>::type>
		void addColumn(const std::initializer_list<T> &column) {
			const size_t tmp = _columnSize;
			for (size_t i = 0; i < column.size(); i++) {
				(*this)[i][tmp] = *(column.begin() + i);
			}
		}

		template<class T,
		class = typename std::enable_if<std::is_arithmetic<T>::value ||
		std::is_same<std::string, T>::value ||
		std::is_same<char*, T>::value>::type>
		void assign(const std::vector<std::vector<T>> &table) {
			clear();
			for (size_t i = 0; i < table.size(); i++)
				for (size_t j = 0; j < table[i].size(); j++)
					(*this)[i][j] = table[i][j];
		}

		template<class T,
		class = typename std::enable_if<std::is_arithmetic<T>::value ||
		std::is_same<std::string, typename std::remove_pointer<typename std::remove_pointer<T>::type>::type>::value>::type>
		void assign(T table, const size_t &rowSize, const size_t &columnSize) {
			clear();
			for (size_t i = 0; i < columnSize; i++)
				for (size_t j = 0; j < rowSize; j++)
					(*this)[i][j] = table[i][j];
		}

		template<class T,
		class = typename std::enable_if<std::is_arithmetic<T>::value ||
		std::is_same<std::string, T>::value ||
		std::is_same<const char*, T>::value>::type>
		void assign(const std::initializer_list<std::initializer_list<T>> &table) {
			clear();
			for (size_t i = 0; i < table.size(); i++)
				for (size_t j = 0; j < (table.begin() + i)->size(); j++)
					(*this)[i][j] = *((table.begin() + i)->begin() + j);
		}
		
		void clear() {
			for (auto &element : _tableData) {
				delete element.second;
			}

			_tableData.clear();
			_columnSize = _rowSize = 0;
		}

		void setAlignment(const Alignment &alignment) {
			_alignment = alignment;
		}

		void setIndent(const size_t &leftIndent, const size_t &rightIndent) {
			_leftIndent = leftIndent;
			_rightIndent = rightIndent;
		}

		void setTableChars(const TableChars &chars) {
			_chars = chars;
		}

		template<class T,
		class = typename std::enable_if<std::is_arithmetic<T>::value ||
		std::is_same<std::string, T>::value ||
		std::is_same<char*, T>::value>::type>
		ConsoleTable &operator=(const std::vector<std::vector<T>> &table) {
			assign(table);
			return *this;
		}

		template<class T,
		class = typename std::enable_if<std::is_arithmetic<T>::value ||
		std::is_same<std::string, T>::value ||
		std::is_same<const char*, T>::value>::type>
		ConsoleTable &operator=(const std::initializer_list<std::initializer_list<T>> &table) {
			assign(table);
			return *this;
		}

		ConsoleTable &operator=(const ConsoleTable &obj) {
			clear();

			_chars = obj._chars;
			_alignment = obj._alignment;
			_leftIndent = obj._leftIndent;
			_rightIndent = obj._rightIndent;
			_rowSize = obj._rowSize;
			_columnSize = obj._columnSize;

			for (auto &i : obj._tableData)
				_tableData[i.first] = new ConsoleRow(*i.second, this);

			return *this;
		}

		ConsoleRow &operator[](size_t row);

		friend std::ostream &operator>>(ConsoleTable &table, std::ostream &stream) {
			return stream << table;
		}

		friend std::ostream &operator<<(std::ostream &stream, ConsoleTable &table);
	private:
		friend ConsoleString &ConsoleRow::operator[](size_t column);

		static void _fillStreamByChar(std::ostream &stream, const char &fillChar, const size_t &lenght) {
			if (lenght > 0)
				stream << std::setfill(fillChar) << std::setw(lenght);
		}

		static void _fillStreamByChar(std::ostream &stream, const char &fillChar, const char &endChar, const size_t &lenght) {
			if (lenght > 0)
				stream << std::setfill(fillChar) << std::setw(lenght) << endChar;
		}

		TableChars _chars;
		std::map<size_t, ConsoleRow*> _tableData;
		Alignment _alignment;
		size_t _leftIndent, _rightIndent;
		size_t _rowSize, _columnSize;
	};

	inline ConsoleRow &ConsoleTable::operator[](const size_t row){
		try {
			return *_tableData.at(row);
		}
		catch (std::out_of_range&) {
			_rowSize = std::max(_rowSize, row + 1);

			_tableData[row] = new ConsoleRow(this);
			return *_tableData[row];
		}
	}

	inline ConsoleString &ConsoleRow::operator[](const size_t column) {
		try {
			return *_rowData.at(column);
		}
		catch (std::out_of_range&) {
			_parent->_columnSize = std::max(_parent->_columnSize, column + 1);

			_rowData[column] = new ConsoleString();
			return *_rowData[column];
		}
	}

	inline std::ostream &operator<<(std::ostream &stream, ConsoleTable &table) {
		// Return if table is empty
		if (table._tableData.empty())
			return stream;
		
		// Read width member and use it as indentation parameter if nonzero
		const auto tableIndentation = stream.width() > 0 ? stream.width() : 0;
		
		// Reset width to 0 for subsequent calls to this stream
		stream.width(0);
		
		// Calculation width of every column
		std::vector<size_t> columnWidth;
		for (size_t i = 0; i < table._columnSize; i++) {
			size_t tmp = 1;
			for (size_t j = 0; j < table._rowSize; j++) {
				if (table._tableData[j] != nullptr && table._tableData[j]->_rowData[i] != nullptr) {
					for (const auto& k : table._tableData[j]->_rowData[i]->_str) {
						tmp = std::max(tmp, k.size());
					}
				}
			}
			columnWidth.push_back(tmp);
		}

		// Calculation height of every row
		std::vector<size_t> rowHeight;
		for (size_t i = 0; i < table._rowSize; i++) {
			size_t tmp = 1;
			for (size_t j = 0; j < table._columnSize; j++) {
				if (table._tableData[i] != nullptr && table._tableData[i]->_rowData[j] != nullptr) {
					tmp = std::max(tmp, table._tableData[i]->_rowData[j]->_str.size());
				}
			}
			rowHeight.push_back(tmp);
		}

		// Top border
		ConsoleTable::_fillStreamByChar(stream, ' ', ' ', static_cast<size_t>(tableIndentation));
		stream << std::right << table._chars.topLeft;
		ConsoleTable::_fillStreamByChar(stream, table._chars.topDownSimple, columnWidth[0] + 1 + table._leftIndent + table._rightIndent);

		if (table._columnSize != 1) {
			for (size_t i = 1; i < table._columnSize; i++) {
				stream << table._chars.topSeparation << std::setw(columnWidth[i] + 1 + table._leftIndent + table._rightIndent);
			}
		}
		stream << table._chars.topRight << std::endl;

		// Elements and middle borders
		for (size_t i = 0; i < table._rowSize; i++) {
			for (size_t k = 0; k < rowHeight[i]; ++k) { // Loop for multiline cells
				ConsoleTable::_fillStreamByChar(stream, ' ', ' ', static_cast<size_t>(tableIndentation));
				for (size_t j = 0; j < table._columnSize; j++) {		
					
					// If cell has data and current line of cell not empty
					if (table._tableData[i] != nullptr && table._tableData[i]->_rowData[j] != nullptr && k < table._tableData[i]->_rowData[j]->_str.size()) {
						const Alignment cellAlignment = table._tableData[i]->_rowData[j]->_alignment
							                                ? *(table._tableData[i]->_rowData[j]->_alignment)
							                                : (table._tableData[i]->_alignment
								                                   ? *(table._tableData[i]->_alignment)
								                                   : table._alignment);
						
						if (cellAlignment == Alignment::centre) {
							const size_t leftSpaceInCell = columnWidth[j] - table._tableData[i]->_rowData[j]->_str[k].size();

							size_t leftAlignmentIndent, rightAlignmentIndent;
							if (leftSpaceInCell % 2) {
								leftAlignmentIndent = leftSpaceInCell / 2;
								rightAlignmentIndent = leftSpaceInCell / 2 + 1;
							}
							else {
								leftAlignmentIndent = rightAlignmentIndent = leftSpaceInCell / 2;
							}

							stream << table._chars.leftRightSimple;
							ConsoleTable::_fillStreamByChar(stream, ' ', ' ', table._leftIndent + leftAlignmentIndent);

							stream << table._tableData[i]->_rowData[j]->_str[k];
							ConsoleTable::_fillStreamByChar(stream, ' ', ' ', table._rightIndent + rightAlignmentIndent);
						}
						else {
							if (cellAlignment == Alignment::left)
								stream << std::left;
							else if (cellAlignment == Alignment::right)
								stream << std::right;

							stream << table._chars.leftRightSimple;
							ConsoleTable::_fillStreamByChar(stream, ' ', ' ', table._leftIndent);

							ConsoleTable::_fillStreamByChar(stream, ' ', columnWidth[j]);
							
							stream << table._tableData[i]->_rowData[j]->_str[k];
							ConsoleTable::_fillStreamByChar(stream, ' ', ' ', table._rightIndent);
						}
					}
					else { // If cell hasn't any data or current line of cell is empty
						stream << table._chars.leftRightSimple;
						ConsoleTable::_fillStreamByChar(stream, ' ', ' ', table._leftIndent);

						ConsoleTable::_fillStreamByChar(stream, ' ', columnWidth[j]);
						stream << ' ';

						ConsoleTable::_fillStreamByChar(stream, ' ', ' ', table._rightIndent);
					}
				}
				stream << std::right << table._chars.leftRightSimple << std::endl;
			}

			// Down border
			ConsoleTable::_fillStreamByChar(stream, ' ', ' ', static_cast<size_t>(tableIndentation));
			if (i == table._rowSize - 1) {
				stream << table._chars.downLeft;
				ConsoleTable::_fillStreamByChar(stream, table._chars.topDownSimple, columnWidth[0] + 1 + table._leftIndent + table._rightIndent);

				if (table._columnSize != 1) {
					for (size_t j = 1; j < table._columnSize; j++) {
						stream << table._chars.downSeparation << std::setw(columnWidth[j] + 1 + table._leftIndent + table._rightIndent);
					}
				}
				stream << table._chars.downRight << std::endl;
			}
			else {
				stream << table._chars.leftSeparation;
				ConsoleTable::_fillStreamByChar(stream, table._chars.topDownSimple, columnWidth[0] + 1 + table._leftIndent + table._rightIndent);

				if (table._columnSize != 1) {
					for (size_t j = 1; j < table._columnSize; j++) {
						stream << table._chars.centreSeparation << std::setw(columnWidth[j] + 1 + table._leftIndent + table._rightIndent);
					}
				}
				stream << table._chars.rightSeparation << std::endl;
			}
		}

		return stream;
	}
}

#endif // _CPP_CONSOLE_TABLE_