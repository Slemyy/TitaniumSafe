#include "PasswordSystem.h"

#include <iostream>

using namespace std;

string accessPassword = "password";

// Функция для ввода пароля.
bool enterPassword() {
	string password;
	cout << "Введите пароль >> ";
	cin >> password;

	// Делаем проверку на правильно пароля.
	return password == accessPassword;
}