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

С этой утилитой вы можете делать текстовые таблици в консоле легко и настраивать их так, как вам нужно

## Интеграция

Все что вам нужно это один единственный файл `CppConsoleTable.hpp` который находится в корневой директории или [в Release](https://github.com/DenisSamilton/CppConsoleTable/releases). Все что вам нужно - это добавить

```cpp
#include "CppConsoleTable.hpp"

// for convenience
using ConsoleTable = samilton::ConsoleTable;
```

к файлу, в котором вы хотите использовать эту утилиту.

**CppConsoleTable** использует стандарт C++17, поэтому важно включить стандарт C++17 в настройках проекта или при компиляции.

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

Если вы хотите добавить новую строку или колонку к существующей таблице, или присвоить новую таблицу, попробуйте эти методы:

```C++
// добавляет новую колонку в таблицу используя initializer_list
table.addColumn({ 1, 2, 3 }); 

// добавляет новую строку в таблицу с vector
std::vector<char> vec = { 'a', 'b', 'c' };
table.addRow(vec);

// добавляет новую колонку в таблицу со стандартного динамического массива
double *arr = new double[3];
arr[0] = 1.3; arr[1] = 2.34; arr[2] = 3.14;
table.addColumn(arr, 3);

// присвоить новую таблицу с элементами с помощью функции используя initializer_list
table.assign({ {"stringA1", "stringA2"}, {"stringB1"}, {"stringC1", "stringC2", "stringC3"} }); 

// присвоить новую таблицу с элементами с помощью функции со стандартного динамического массива
std::string **arr = new std::string*[3];
for (auto i = 0; i < 3; ++i) {
	arr[i] = new std::string[2];
	for (auto j = 0; j < 2; ++j) { arr[i][j] = std::to_string(i+j); }
}
table.assign(arr, 2, 3);

// присвоить новую таблицу с элементами с помощью перегруженного оператора присваивания используя initializer_list
table = { {1, 22}, {33}, {37, 74, 945} }; 

// присвоить новую таблицу с элементами с vector
std::vector<std::vector<int>> vec = { {1, 4, 6}, {2, 3} };
table = vec;
```

Вы также можете поменять выравнивание всех обьектов таблицу (по умолчанию это **left**):

```C++
// используя конструктор
ConsoleTable table(samilton::Alignment::center);

// или используя метод
table.setAlignment(samilton::Alignment::right);
```

Или вы можете поменять выравнивание конкретной строки или ячейки:

```C++
// установить выравнивание конкретной строки
table[0](samilton::Alignment::center);

// установить выравнивание конкретной строки с присвоением элемента
table[0](samilton::Alignment::right)[1] = 3.14;

// установить выравнивание конкретной ячейки
table[1][2](samilton::Alignment::left) = "ExampleString";
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
Вывод:
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

## Лицензия

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The class is licensed under the [MIT License](http://opensource.org/licenses/MIT):

Copyright &copy; 2019 DenisSamilton

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## Контакты

Если у вас есть вопросы касающиеся библиотеки, я хотел бы пригласить вас [открыть вопрос в GitHub](https://github.com/DenisSamilton/CppConsoleTable/issues/new). Пожалуйста опишите ваш запрос, проблему, или вопрос как можно подробнее, также укажите версию утилиты что вы используете, версию вашего компилятора и операционной системы. Открытие вопроса на Github позволяет сотрудничать другим пользователям и авторам этой библиотеки.

Если только у вас есть вопросы имеющие конфиденциальную информацию, пожалуйста [отправьте мне e-mail](mailto:d.bogdan99@gmail.com).
