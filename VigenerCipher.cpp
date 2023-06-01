#include "Ciphers.h"
#include "ShowMenu.h"
#include "FileSystem.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

extern string PREFIX;

// Функция для шифровки
string vigenereEncrypt(const string& plaintext, const string& key)
{
	string ciphertext;
	int textLength = plaintext.length();
	int keyLength = key.length();

	for (int i = 0; i < textLength; ++i)
	{
		char currentChar = plaintext[i];
		char keyChar = key[i % keyLength];
		int shift = (keyChar + 1) % 256; // Число символов в ASCII таблице

		currentChar = (currentChar + shift) % 256;

		ciphertext += currentChar;
	}

	return ciphertext;
}

// Функция для дешифровки
string vigenereDecrypt(const string& ciphertext, const string& key)
{
	string decryptedText;
	int textLength = ciphertext.length();
	int keyLength = key.length();

	for (int i = 0; i < textLength; ++i)
	{
		char currentChar = ciphertext[i];
		char keyChar = key[i % keyLength];
		int shift = (keyChar + 1) % 256; // Число символов в ASCII таблице

		currentChar = (currentChar - shift + 256) % 256;

		decryptedText += currentChar;
	}

	return decryptedText;
}

void cipherVigener()
{
	showCipherMenu("Vigener");

	while (true)
	{
		cout << "\nВыберите необходимое действие (введите соответствующую цифру) >> ";

		try
		{
			string input;
			cin >> input;

			// Переводим input в число.
			int choise = stoi(input);

			switch (choise)
			{
			case 1:
			{
				string message;
				cout << "\nВведите текст для шифрования >> ";
				cin.ignore();
				getline(cin, message);

				string key;
				cout << "Введите ключ шифрования >> ";
				cin >> key;

				string filename;
				cout << "Введите имя файла, куда будет сохранен результат >> ";
				cin >> filename;

				filename += ".txt";

				if (fileExists(filename)) { throw runtime_error("Файл уже существует"); }

				string result = vigenereEncrypt(message, key);
				saveToFile(filename, result);
				cout << "[" << PREFIX << "] Содержимое файла: " << result << endl;
				break;
			}

			case 2:
			{
				string filename;
				cout << "Введите имя файла, откуда будет взят текст >> ";
				cin >> filename;

				filename += ".txt";
				string message = readFromFile(filename);

				string key;
				cout << "Введите ключ шифрования >> ";
				cin >> key;

				string result = vigenereDecrypt(message, key);
				cout << result << " " << endl;
				break;
			}

			case 3:
			{
				system("cls");
				cout << "[" << PREFIX << "] Консоль успешно очищена.\n" << endl;
				showCipherMenu("Vigener");
				break;
			}

			case 4:
			{
				system("cls");
				cout << "[" << PREFIX << "] Вы вернулись в начальное меню." << endl << endl;
				showMenu();
				return;
			}

			default:
				cerr << "\n[" << PREFIX << "] Некорректный выбор. Попробуйте снова.";
				break;
			}
		}
		catch (const exception& e) { cerr << "\n[" << PREFIX << "] Ошибка: " << e.what(); }
	}
}