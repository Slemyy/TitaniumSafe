#include "HelperSystem.h"
#include "FileSystem.h"

#include <iostream>
#include <string>

using namespace std;

extern string PREFIX;
extern string filename;

ostream& operator<<(ostream& os, const vector<int>& v) {
	for (const auto& i : v) { os << i << " "; }
	return os;
}

// Функция для проверки, является ли число простым
bool isPrime(const int& number) {
	if (number <= 1) { return false; }
	if (number == 2 || number == 3) { return true; }
	if (number % 2 == 0 || number % 3 == 0) { return false; }

	int sqrtNumber = static_cast<int>(sqrt(number));
	for (int i = 5; i <= sqrtNumber; i += 6) {
		if (number % i == 0 || number % (i + 2) == 0) {
			return false;
		}
	}

	return true;
}

// Функция для нахождения модуля. 
__int64 findMod(__int64 number, __int64 degree, __int64 module) {
	__int64 result = 1;
	number %= module;

	while (degree > 0) {
		__int64 d = degree % 10;
		degree /= 10;

		for (__int64 i = 0; i < d; i++) {
			result = (result * number) % module;
		}

		__int64 temp = number;
		for (__int64 i = 1; i < 10; i++) {
			number = (number * temp) % module;
		}
	}

	return result;
}

// Функция для вычисления наибольшего общего делителя
__int64 gcd(__int64 a, __int64 b) {
	if (a < b) { return(gcd(b, a)); }
	else if (a % b == 0) { return b; }
	else { return(gcd(b, a % b)); }
}

string methodOfOperation()
{
	string choiseVar;
	cout << "Выберите вариацию получения сообщения (file | console) >> ";
	cin >> choiseVar;

	string message;
	if (choiseVar == "console")
	{
		cout << "Введите текст для шифрования >> ";
		cin.ignore();
		getline(cin, message);

		if (saveToFile(filename, message))
		{
			cout << "\n[" << PREFIX << "] Файл записан: " << filename << endl;
		}
	}
	else if (choiseVar == "file")
	{
		string file;
		cout << "Введите название файла (Пример: text.txt) >> ";
		cin >> file;
		message = readFromFile(file);
	}
	else throw runtime_error("Некорректный выбор. Такого варианта не существует");

	return message;
}
