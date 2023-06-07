#include "FileSystem.h"

#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string filename = "plaintext.txt";
string encryptedFile = "encrypted.txt";
string decryptedFile = "decrypted.txt";

// Проверка на то, создан ли файл
bool fileExists(const string& filename)
{
	ifstream file(filename);
	return file.good();
}

bool isEnglish(const string& text) {
	for (char c : text) {
		if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||  (c == '.')))
			return false;
	}
	return true;
}

// Функция для чтения текста из файла
string readFromFile(const string& filename)
{
	if (!isEnglish(filename)) throw runtime_error("Название файла должно быть на английском языке");
	string content;
	ifstream file(filename);

	if (file.is_open())
	{
		string line;
		while (getline(file, line)) { content += line; }
		file.close();
	}
	
	else throw runtime_error("Не удалось прочитать файл");
	return content;
}

bool isNumber(const string& s) {
	istringstream iss(s);
	double dummy;
	iss >> noskipws >> dummy;
	return iss.eof() && !iss.fail();
}

// Функция для чтения текста из файла
vector<int> readFromFile(const string& filename, const string& type)
{
	if (!isEnglish(filename)) throw runtime_error("Название файла должно быть на английском языке");
	vector<int> content, result;
	ifstream file(filename);

	if (file.is_open())
	{
		string input;
		int number;
		while (file >> input) {
			if (!isNumber(input)) throw runtime_error("Файл должен состоять только из цифр");
			number = stoi(input);
			result.push_back(number);
		}

		if (type == "ElGamal")
		{
			if (result.size() < 2) throw runtime_error("В файле должно быть больше цифр");
		}

		file.close();
	}
	else throw runtime_error("Не удалось прочитать файл");

	return result;
}

// Функция для создания файла
bool saveToFile(const string& filename, const string& content)
{
	ofstream file(filename);

	if (file.is_open())
	{
		file << content; // Создаем файл и записываем в него информацию.
		file.close();
		return true;
	}

	else throw runtime_error("Не удалось открыть файл");
}

// Функция для создания файла
bool saveToFile(const string& filename, const vector<int>& content)
{
	ofstream file(filename);

	if (file.is_open())
	{
		for (const auto& i : content)
		{
			file << i << " "; // Создаем файл и записываем в него информацию.
		}

		file.close();
		return true;
	}

	else throw runtime_error("Не удалось открыть файл");
}
