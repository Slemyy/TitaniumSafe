#include "PasswordSystem.h"

#include <iostream>

using namespace std;

string accessPassword = "password";

// ������� ��� ����� ������.
bool enterPassword() {
	string password;
	cout << "������� ������ >> ";
	cin >> password;

	// ������ �������� �� ��������� ������.
	return password == accessPassword;
}