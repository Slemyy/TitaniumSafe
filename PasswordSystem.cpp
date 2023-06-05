#include "PasswordSystem.h"

#include <iostream>

using namespace std;

extern string PREFIX;
string accessPassword = "password";

// Функция для ввода пароля.
bool enterPassword() {
	string password;
	cout << "Введите пароль >> ";
	cin >> password;

	// Делаем проверку на правильно пароля.
	return password == accessPassword;
}

// Для проверки пароля.
void checkPass()
{
	while (true)
	{
		bool isPass = enterPassword();
		if (!isPass) cout << "\n[" << PREFIX << "] Неверный пароль. В доступе отказано." << endl;
		else break;
	}
}