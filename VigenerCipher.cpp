#include "Ciphers.h"
#include "ShowMenu.h"
#include "FileSystem.h"
#include "PasswordSystem.h"
#include "HelperSystem.h"

#include <iostream>
#include <string>

using namespace std;

extern string PREFIX;
extern string filename;
extern string encryptedFile;
extern string decryptedFile;
extern const char* SYSTEM_CLEAR;

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

bool isEnglishText(const string& text) {
	for (char c : text) {
		if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
			return false;
	}
	return true;
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
				// Делаем проверку на ввод пароля.
				checkPass();

				string message = methodOfOperation();

				string key;
				while (true)
				{
					cout << "Введите ключ шифрования (Одно слово на английском языке) >> ";
					cin >> key;

					if (isEnglishText(key)) { break; }
					cout << "\n[" << PREFIX << "] Ошибка: Ключ должен быть на английском языке" << endl;
				}

				string result = vigenereEncrypt(message, key);
				if (saveToFile(encryptedFile, result)) 
				{ 
					cout << "\n[" << PREFIX << "] Файл записан: " << encryptedFile << endl;
				}

				cout << "[" << PREFIX << "] Содержимое файла: " << result << endl;
				break;
			}

			case 2:
			{
				// Делаем проверку на ввод пароля.
				checkPass();

				string file;
				cout << "Введите название файла где находится шифр (Пример: text.txt) >> ";
				cin >> file;
				string message = readFromFile(file);

				string key;
				while (true)
				{
					cout << "Введите ключ шифрования >> ";
					cin >> key;

					if (isEnglishText(key)) { break; }
					cout << "\n[" << PREFIX << "] Ошибка: Ключ должен быть на английском языке" << endl;
				}

				string result = vigenereDecrypt(message, key);

				if (saveToFile(decryptedFile, result))
				{
					cout << "\n[" << PREFIX << "] Файл записан: " << decryptedFile << endl;
				}
				cout << "[" << PREFIX << "] Содержимое файла: " << result << endl;

				break;
			}

			case 3:
			{
				system(SYSTEM_CLEAR);
				cout << "[" << PREFIX << "] Консоль успешно очищена.\n" << endl;
				showCipherMenu("Vigener");
				break;
			}

			case 4:
			{
				system(SYSTEM_CLEAR);
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