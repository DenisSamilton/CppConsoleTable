<p align="center">
<img src="https://lh3.googleusercontent.com/QLx9TsSHq9v7E67EZXvrImzdo7s9_3572ikFL5Q35-eIuLG2RthAI4JyGobylI4J3L_NhNesi4LVfUhMCHvd6RLh5f3998g4EDZzyh5Mq99JNBhUGf7DKXGGQ1tfk588VectgFbhqkVqwNAtV1hGjM8JS-p3AHDYA69zNMKRMA_fpfHoAaqjSu7Ai4pTTavSvYIjY3dkfmYredSsO82xXBxtLmHKHzVgUpj2ghXQzojh7HVSVhh3t5IPNumW3fgkoagum_XVNIuf6PFlZvN4bt4ce7jmrOftdPMqeyg2VqaaJ9mQ2UiHoALszH7I37SujHKQtMM-pRI006_Zhtz0lR_iWiZAJeaYROa_OeEXRFg9zv9iHCnAenNZKgTQsFhoH9XD9ssQrGoNh6jCwP8qWo-Hpws1bvCPfsFSd9gV7nyHGEuZKP2FxjbUHG7OCFmB9nIDtP5vhfHpelAaCOGHsH3BEOZdRNcp_KEYeJQVvhi3A6ptueKeyT6lAvp-QjXRXT2OuimZMh_wBPi6h4XAilUkdsHPqqFvvQHtwtJxD7TULEbEfAEpoHoX8TqNAjalQu2LYFpZOgO0NFPYQwXb7oS7fDdVXrPJgIYRonPhhCZvLwLvCUI3O64pVZzWZHO4M5Iu1jJfYRJwTxvOXC12qjQ9kQ=w832-h161-no" width="491" height="95">
<br><br>
<a href="https://opensource.org/licenses/MIT" alt="License">
	<img src="https://img.shields.io/github/license/DenisSamilton/CppConsoleTable.svg" /></a>
<a href="https://github.com/DenisSamilton/CppConsoleTable/issues" alt="Open issues">
        <img src="https://img.shields.io/github/issues/DenisSamilton/CppConsoleTable.svg" /></a>
<a href="https://github.com/DenisSamilton/CppConsoleTable/releases/latest" alt="Latest release">
        <img src="https://img.shields.io/github/release/DenisSamilton/CppConsoleTable.svg" /></a>
</p>

:ru:[**На русском**](https://github.com/DenisSamilton/CppConsoleTable/blob/master/README_RU.md)

With this tool you can make text table in console easily and set up as you need.

## Integration

The single required source, file `CppConsoleTable.hpp` is in the root directory or [released here](https://github.com/DenisSamilton/CppConsoleTable/releases). All you need to do is add

```cpp
#include "CppConsoleTable.hpp"

// for convenience
using ConsoleTable = samilton::ConsoleTable;
```

to the files you want to use ConsoleTable.

**CppConsoleTable** uses C++17 standard, so it's necessary to enable C++17.

## Examples

With the **ConsoleTable** class, you could write:

```C++
// create an empty structure (null)
ConsoleTable table;

// add a number of double type
table[0][1] = 3.141;

// add a Boolean 
table[1][0] = true;

// add a number of int type
table[2][1] = 56;

// add a "const char[]" string (it also could be an std::string)
table[2][0] = "some";
```

If you want to add new row, column to existence table, or assign new table, you should try this methods:

```C++
// add new column to table using initializer_list
table.addColumn({ 1, 2, 3 }); 

// add new row to table from vector
std::vector<char> vec = { 'a', 'b', 'c' };
table.addRow(vec);

// add new column to table from vanilla dynamic array
double *arr = new double[3];
arr[0] = 1.3; arr[1] = 2.34; arr[2] = 3.14;
table.addColumn(arr, 3);

// assign new table with elements by function using initializer_list
table.assign({ {"stringA1", "stringA2"}, {"stringB1"}, {"stringC1", "stringC2", "stringC3"} }); 

// assign new table with elements by function using vanilla dynamic array
std::string **arr = new std::string*[3];
for (auto i = 0; i < 3; ++i) {
	arr[i] = new std::string[2];
	for (auto j = 0; j < 2; ++j) { arr[i][j] = std::to_string(i+j); }
}
table.assign(arr, 2, 3);

// assign new table with elements by overloaded assign operator using initializer_list
table = { {1, 22}, {33}, {37, 74, 945} }; 

// assign new table with elements from vector
std::vector<std::vector<int>> vec = { {1, 4, 6}, {2, 3} };
table = vec;
```

You can also change the alignment of all objects in table (for default it's **left**):

```C++
// using constructor
ConsoleTable table(samilton::Alignment::center);

// or using a method
table.setAlignment(samilton::Alignment::right);
```

Or, you can change alignment of specific row or cell:

```C++
// set alignment to specific row
table[0](samilton::Alignment::center);

// set alignment to specific row with element assign
table[0](samilton::Alignment::right)[1] = 3.14;

// set alignment to specific cell
table[1][2](samilton::Alignment::left) = "ExampleString";
```

If you need indent before or after your elements, you can change it:

```C++
// using constructor
ConsoleTable table(2, 3);

// or using a method
table.setIndent(2, 3);
```

If you need to change the characters of table, you can easily do it with TableChars struct:
```C++
// creating struct
ConsoleTable::TableChars chars;

// modifying characters
chars.topDownSimple = '-';
chars.leftSeparation = '+';

// changing characters in table
table.setTableChars(chars);
```

Then, all you need to do is out this table to stream:

```C++
// using iostream
std::cout << table;

// you can also out it to file using fstream
std::fstream file("test.txt");
file << table;

// of course you can out it also to stringstream
std::stringstream stream;
stream << table;
```

Full example of using:

```C++
#include <iostream>

#include "CppConsoleTable.hpp"

using namespace std;
using ConsoleTable = samilton::ConsoleTable;

int main()
{
	ConsoleTable table(1, 1, samilton::Alignment::centre);

	table[0][0] = "Some String";
	table[1][3] = true;
	table[2][1] = 10;
	table[3][3] = "Some\nMulti String";
	table[2][2] = 2.354;
	table[0][1] = false;

	cout << table;

	system("pause");
}
```
Output:
```
╔═════════════╦═══════╦══════════╦══════════════╗
║ Some String ║ false ║          ║              ║
╠═════════════╬═══════╬══════════╬══════════════╣
║             ║       ║          ║     true     ║
╠═════════════╬═══════╬══════════╬══════════════╣
║             ║  10   ║ 2.354000 ║              ║
╠═════════════╬═══════╬══════════╬══════════════╣
║             ║       ║          ║     Some     ║
║             ║       ║          ║ Multi String ║
╚═════════════╩═══════╩══════════╩══════════════╝
```

## License

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The class is licensed under the [MIT License](http://opensource.org/licenses/MIT):

Copyright &copy; 2019 DenisSamilton

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## Contact

If you have questions regarding the library, I would like to invite you to [open an issue at Github](https://github.com/DenisSamilton/CppConsoleTable/issues/new). Please describe your request, problem, or question as detailed as possible, and also mention the version of the library you are using as well as the version of your compiler and operating system. Opening an issue at Github allows other users and contributors to this library to collaborate.

Only if your request would contain confidential information, please [send me an email](mailto:d.bogdan99@gmail.com).
