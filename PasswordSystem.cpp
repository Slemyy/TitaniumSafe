#include "PasswordSystem.h"

#include <iostream>

using namespace std;

extern string PREFIX;
string accessPassword = "password";

// ������� ��� ����� ������.
bool enterPassword() {
	string password;
	cout << "������� ������ >> ";
	cin >> password;

	// ������ �������� �� ��������� ������.
	return password == accessPassword;
}

// ��� �������� ������.
void checkPass()
{
	while (true)
	{
		bool isPass = enterPassword();
		if (!isPass) cout << "\n[" << PREFIX << "] �������� ������. � ������� ��������." << endl;
		else break;
	}
}