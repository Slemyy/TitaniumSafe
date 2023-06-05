#include "FileSystem.h"

#include <fstream>
#include <string>

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

// Функция для чтения текста из файла
string readFromFile(const string& filename)
{
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

// Функция для чтения текста из файла
vector<int> readFromFile(const string& filename, const string& type)
{
	vector<int> content, result;
	ifstream file(filename);

	if (file.is_open())
	{
		int number;
		while (file >> number) {
			result.push_back(number);
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
