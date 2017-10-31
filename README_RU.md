# C++ Console Table
С этой утилитой вы можете делать текстовые таблици в консоле легко и настраивать их так, как вам нужно

## Интеграция

Все что вам нужно это один единственный файл `CppConsoleTable.hpp` который находится в корневой директории или [в Release](https://github.com/Oradle/CppConsoleTable/releases). Все что вам нужно - это добавить

```cpp
#include "CppConsoleTable.hpp"

// для упрощения
using ConsoleTable = samilton::ConsoleTable;
```

к файлу, в котором вы хотите использовать эту утилитиу. Вот и всё.

## Примеры

С классом **ConsoleTable** вы можете написать:

```C++
// создаем пустую структуру
ConsoleTable table;

// добавляем число типа double
table[0][1] = 3.141;

// добавляем Boolean значение
table[1][0] = true;

// добавляем число типа int
table[2][1] = 56;

// добавляем "const char[]" строку (там также может быть std::string)
table[2][0] = "some";
```

Вы также можете поменять выравнивание всех обьектов таблицу (по умолчанию это **left**):

```C++
// используя конструктор
ConsoleTable table(ConsoleTable::Alignment::right);

// или используя метод
table.setAlignment(ConsoleTable::Alignment::right);
```

Если вам нужны отступы перед и после элементов, мы можете установить их так:

```C++
// используя конструктор
ConsoleTable table(2, 3);

// или используя метод
table.setIndent(2, 3);
```

Если вам нужно поменять символы таблици, вы можете с легкостью сделать это с TableChars структурой:

```C++
// создаем структуру
ConsoleTable::TableChars chars;

// меняем нужные символы
chars.topDownSimple = '-';
chars.leftSeparation = '+';

// меняем символы в таблице
table.setTableChars(chars);
```

Затем, все что вам нужно сделать это вывести эту таблицу в поток:

```C++
// используя iostream
std::cout << table;

// вы также можете вывести таблицу в файл, используя fstream
std::ofstream file("test.txt");
file << table;

// конечно вы так же можете вывести таблицу в stringstream
std::stringstream stream;
stream << table;
```

Полный пример использования:

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
Вывод:
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

## Лицензия

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The class is licensed under the [MIT License](http://opensource.org/licenses/MIT):

Copyright &copy; 2017 Oradle

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## Контакты

Если у вас есть вопросы касающиеся библиотеки, я хотел бы пригласить вас [открыть вопрос в GitHub](https://github.com/Oradle/CppConsoleTable/issues/new). Пожалуйста опиште ваш запрос, проблему, или вопрос как можно подробнее, также укажите версию утилиты что вы используете, версию вашего компилятора и операционной системы.

Если только у вас есть вопросы имеющие конфиденциальную информацию, пожалуйста [отправьте мне e-mail](mailto:d.bogdan99@gmail.com).
