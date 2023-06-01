// TitaniumSafe.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>

#include "ShowMenu.h"
#include "Ciphers.h"

using namespace std;

string PREFIX = "TitaniumSafe";

// Функция для ввода пароля.
bool enterPassword() {
	string password;
	cout << "Введите пароль >> ";
	cin >> password;

	// Делаем проверку на правильно пароля.
	return password == "password";
}

int main()
{
	system("chcp 1251 > nul");

	// Делаем проверку на ввод пароля.
	while (true)
	{
		bool isPass = enterPassword();
		if (!isPass) cout << "\n[" << PREFIX << "] Неверный пароль. В доступе отказано." << endl;
		else break;
	}

	cout << endl;
	showMenu();

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
				system("cls");
				cipherVigener();
				break;
			}

			case 2:
			{
				system("cls");
				cipherHill();
				break;
			}

			case 3:
			{
				system("cls");
				cipherRSA();
				break;
			}

			case 4:
			{
				system("cls");
				cout << "[" << PREFIX << "] Консоль успешно очищена.\n" << endl;
				showMenu();
				break;
			}

			case 5:
			{
				system("pause");
				return 0;
			}

			default:
				cerr << "\n[" << PREFIX << "] Некорректный выбор. Попробуйте снова.";
				break;
			}
		}
		catch (const exception& e) { cerr << "\n[" << PREFIX << "] Ошибка: " << e.what(); }
		catch (...) { cerr << "\n[" << PREFIX << "] Ошибка: Неизвестная ошибка :("; }
	}

	return 0;
}