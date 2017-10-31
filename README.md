# C++ Console Table

[**На русском**](https://github.com/Oradle/CppConsoleTable/blob/master/README_RU.md)

With this tool you can make text table in console easily and set up as you need.

## Integration

The single required source, file `CppConsoleTable.hpp` is in the root directory or [released here](https://github.com/Oradle/CppConsoleTable/releases). All you need to do is add

```cpp
#include "CppConsoleTable.hpp"

// for convenience
using ConsoleTable = samilton::ConsoleTable;
```

to the files you want to use ConsoleTable. That's it.

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

You can also change the alignment of all objects in table (for default it's **left**):

```C++
// using constructor
ConsoleTable table(ConsoleTable::Alignment::right);

// or using a method
table.setAlignment(ConsoleTable::Alignment::right);
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
	ConsoleTable table(2, 1, ConsoleTable::Alignment::right);

	table[0][0] = "some";
	table[1][3] = true;
	table[2][1] = 10;
	table[3][3] = "bla";
	table[2][2] = 2.354;
	table[0][1] = false;

	cout << table;

	system("pause");
}
```
Output:
```
╔═══════╦════════╦═══════════╦═══════╗
║  some ║  false ║           ║       ║
╠═══════╬════════╬═══════════╬═══════╣
║       ║        ║           ║  true ║
╠═══════╬════════╬═══════════╬═══════╣
║       ║     10 ║  2.354000 ║       ║
╠═══════╬════════╬═══════════╬═══════╣
║       ║        ║           ║   bla ║
╚═══════╩════════╩═══════════╩═══════╝
```

## License

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The class is licensed under the [MIT License](http://opensource.org/licenses/MIT):

Copyright &copy; 2017 Oradle

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## Contact

If you have questions regarding the library, I would like to invite you to [open an issue at Github](https://github.com/Oradle/CppConsoleTable/issues/new). Please describe your request, problem, or question as detailed as possible, and also mention the version of the library you are using as well as the version of your compiler and operating system. Opening an issue at Github allows other users and contributors to this library to collaborate.

Only if your request would contain confidential information, please [send me an email](mailto:d.bogdan99@gmail.com).
