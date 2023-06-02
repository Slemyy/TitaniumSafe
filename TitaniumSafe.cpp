// TitaniumSafe.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>

#include "ShowMenu.h"
#include "Ciphers.h"
#include "PasswordSystem.h"

using namespace std;

string PREFIX = "TitaniumSafe";
const char* SYSTEM_CLEAR = "cls";

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
				system(SYSTEM_CLEAR);
				cipherVigener();
				break;
			}

			case 2:
			{
				system(SYSTEM_CLEAR);
				cipherHill();
				break;
			}

			case 3:
			{
				system(SYSTEM_CLEAR);
				cipherRSA();
				break;
			}

			case 4:
			{
				system(SYSTEM_CLEAR);
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