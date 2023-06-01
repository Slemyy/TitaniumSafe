#include "fileSystem.h"

#include <fstream>
#include <string>

using namespace std;

extern string PREFIX;

// Проверка на то, создан ли файл
bool fileExists(const string& filename)
{
	ifstream file(filename);
	return file.good();
}

// Функция для чтения текста из файла
string readFromFile(const string& filename)
{
	ifstream file(filename);
	if (!file) throw runtime_error("Не удалось прочитать файл");

	string content;
	string line;
	while (getline(file, line)) { content += line; }

	file.close();
	return content;
}

// Функция для создания файла
void saveToFile(const string& filename, const string& content)
{
	ofstream file(filename);

	file << content; // Создаем файл и записываем в него информацию.

	file.close();
	cout << "\n[" << PREFIX << "] Файл создан: " << filename << std::endl;
}
