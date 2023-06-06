#include "Ciphers.h"
#include "ShowMenu.h"
#include "FileSystem.h"
#include "PasswordSystem.h"
#include "HelperSystem.h"

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cmath>

using namespace std;

extern string PREFIX;
extern string filename;
extern string encryptedFile;
extern string decryptedFile;
extern const char* SYSTEM_CLEAR;

// Функция для генерации простых чисел в заданном диапазоне
int generatePrime(int lowerBound, int upperBound) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(lowerBound, upperBound);

	while (true) {
		__int64 num = dist(gen);
		if (isPrime(num)) {
			return num;
		}
	}
}

// Функция для нахождения обратного элемента в кольце по модулю
__int64 findInverse(__int64 a, __int64 m) {
	__int64 m0 = m;
	__int64 y = 0, x = 1;
	__int64 q, temp;

	if (m == 1) {
		return 0;
	}

	while (a > 1) {
		q = a / m;
		temp = m;
		m = a % m;
		a = temp;

		temp = y;
		y = x - q * y;
		x = temp;
	}

	if (x < 0) {
		x += m0;
	}

	return x;
}

// Функция для выбора целого числа e ( 1 < e < t ), взаимно простое со значением функции Эйлера (t).
__int64 calculateE(const int& p, const int& q, const __int64& phi) {
	while (true)
	{
		__int64 i = generatePrime(10000000, 99000000);
		if (i < phi && gcd(i, phi) == 1 && i != p && i != q) {
			return i;
		}
	}

	return 0; // Возвращаем 0, если не найдено подходящее значение e
}

// Функция для генерации ключей RSA
void generateRSAKeys(const int& p, const int& q, __int64& n, __int64& e, __int64& d) {
	n = p * q;
	__int64 phi = (p - 1) * (q - 1);

	e = calculateE(p, q, phi);
	d = findInverse(e, phi);
}

vector<int> RSAEncrypt(vector<int>& plaintext, __int64 e, __int64 n) {
	vector<int> encryptedResult;

	for (int i = 0; i < plaintext.size(); i++)
	{
		int s = findMod(plaintext[i], e, n);
		encryptedResult.push_back(s);
	}

	return encryptedResult;
}

string RSADecrypt(vector<int>& ciphertext, __int64 d, __int64 n) {
	vector<char> decryptedResult;

	for (int i = 0; i < ciphertext.size(); i++)
	{
		char a = static_cast<char>(findMod(ciphertext[i], d, n));
		decryptedResult.push_back(a);
	}

	string decryptedText;
	for (auto i : decryptedResult) { decryptedText += i; }
	return decryptedText;
}

void cipherRSA()
{
	showCipherMenu("RSA");

	int p = 0, q = 0;
	__int64 n = 0, e = 0, d = 0;

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
				p = generatePrime(10000, 46000);
				q = generatePrime(10000, 46000);
				generateRSAKeys(p, q, n, e, d);

				// Делаем проверку на ввод пароля.
				checkPass();

				cout << "\n[" << PREFIX << "] Открытый ключ: (" << e << ", " << n << ")" << endl;
				cout << "[" << PREFIX << "] Закрытый ключ: (" << d << ", " << n << ")" << endl;

				string message;
				cout << "\nВведите текст для шифрования >> ";
				cin.ignore();
				getline(cin, message);

				if (saveToFile(filename, message))
				{
					cout << "[" << PREFIX << "] Файл записан: " << filename << endl;
				}

				vector<int> ASCIIMessage;
				for (const auto& i : message) { ASCIIMessage.push_back(static_cast<double>(i)); }
		
				vector<int> resultEncrypt = RSAEncrypt(ASCIIMessage, e, n);
				if (saveToFile(encryptedFile, resultEncrypt))
				{
					cout << "\n[" << PREFIX << "] Файл записан: " << encryptedFile << endl;
				}
		
				cout << "[" << PREFIX << "] Содержимое файла: " << resultEncrypt << endl;
				break;
			}
		
			case 2:
			{
				// Делаем проверку на ввод пароля.
				checkPass();

				vector<int> message = readFromFile(encryptedFile, "vector");

				string keyD, keyN;
				cout << "Введите закрытый ключ шифрования (Пример: 271 523) >> ";
				cin >> keyD >> keyN;
				d = stoll(keyD), n = stoll(keyN);

				string result = RSADecrypt(message, d, n);
		
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
				showCipherMenu("RSA");
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