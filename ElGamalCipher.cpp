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

// Функция для генерации чисел в заданном диапазоне
__int64 generateRandom(__int64 lowerBound, __int64 upperBound, bool isSimple = false) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<__int64> dist(lowerBound, upperBound);

	__int64 num;

	if (isSimple)
	{
		while (true) {
			num = dist(gen);
			if (isPrime(num)) {
				return num;
			}
		}
	}

	num = dist(gen);
	return num;
}

// Функция для генерации секретного ключа
__int64 generateNum(__int64 p, bool isPMinusOne = false) {
	__int64 num;
	__int64 lowerBound = isPMinusOne ? 1 : 2;
	__int64 upperBound = isPMinusOne ? p - 2 : p - 1;

	do {
		num = generateRandom(lowerBound, upperBound);
	} while (gcd(isPMinusOne ? p - 1 : p, num) != 1);

	return num;
}

// Нахождение первообразного корня g.
__int64 primitiveRoot(__int64& p) {
	__int64 q = (p - 1) / 2;
	__int64 g;

	do {
		g = generateRandom(2, p - 2);
	} while (findMod(g, q, p) == 1);

	return g;
}

// Функция для генерации ключей Эль Гамаля.
void generateElGamalKeys(__int64& p, __int64& g, __int64& x, __int64& y, __int64& k, __int64& r, __int64& e)
{
	g = primitiveRoot(p); // Первообразный корень p
	x = generateNum(p); // Секретный ключ
	y = findMod(g, x, p); // Открытый ключ
	k = generateNum(p, true); // одноразовый секретный ключ
	r = findMod(g, k, p); // Первая часть шифра
	e = findMod(y, k, p); // Вторая часть шифра
}

vector <int> ElGamalEncrypt(string& plaintext, __int64 p, __int64 e) {
	vector <int> encryptedResult;
	for (__int64 i = 0; i < plaintext.size(); i++) 
	{
		encryptedResult.push_back(e * static_cast<__int64>(plaintext[i]) % p);
	}

	return encryptedResult;
}

string ElGamalDecrypt(vector <int>& ciphertext, __int64 p, __int64 x, __int64 r) {
	__int64 h = findMod(r, p - x - 1, p);
	vector <__int64> decryptedResult;

	for (__int64 i = 0; i < ciphertext.size(); i++) 
	{
		decryptedResult.push_back(h * ciphertext[i] % p);
	}

	string decryptedText;
	for (auto i : decryptedResult) { decryptedText += (char)i; }
	return decryptedText;
}

void cipherElGamal()
{
	showCipherMenu("ElGamal");

	__int64 p = 0, g = 0;
	__int64 x = 0, y = 0, k = 0, r = 0, e = 0;

	while (true)
	{
		cout << "\nВыберите необходимое действие (введите соответствующую цифру) >> ";
		try
		{
			string input;
			cin >> input;

			// Переводим input в число.
			__int64 choise = stoi(input);

			switch (choise)
			{
			case 1:
			{	
				p = generateRandom(1000000000, numeric_limits<int>::max(), true);
				generateElGamalKeys(p, g, x, y, k, r, e);

				// Делаем проверку на ввод пароля.
				checkPass();

				string message = methodOfOperation();

				cout << "\n[" << PREFIX << "] Открытый ключ: (" << p << ", " << g << ", " << y << ")" << endl;
				cout << "[" << PREFIX << "] Закрытый ключ: (" << x << ")" << endl;

				vector<int> resultEncrypt = ElGamalEncrypt(message, p, e);
				resultEncrypt.push_back(p); resultEncrypt.push_back(r);
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

				string file;
				cout << "Введите название файла где находится шифр (Пример: text.txt) >> ";
				cin >> file;
				vector<int> message = readFromFile(file, "ElGamal");

				string key;
				cout << "Введите закрытый ключ шифрования (Пример: 271523) >> ";
				cin >> key;
				x = stoll(key);

				pair<__int64, __int64> p = { message[message.size() - 2], message[message.size() - 1] };
				message.resize(message.size() - 2);
				string result = ElGamalDecrypt(message, p.first, x, p.second);

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
				showCipherMenu("ElGamal");
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