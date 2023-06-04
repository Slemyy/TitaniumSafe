#include "ShowMenu.h"

using namespace std;

extern string PREFIX;

void showMenu()
{
	cout << "=============== " << PREFIX << " ===============" << endl;
	cout << "1. ���� ��������" << endl;
	cout << "2. ���� ��� ������" << endl;
	cout << "3. ���� RSA" << endl;
	cout << "4. ������� �������" << endl;
	cout << "5. ����� �� ���������" << endl;
	cout << "============================================" << endl;
}

void showCipherMenu(const string& name)
{
	if (name == "Vigener") { cout << "============ The Vigener Cipher ============" << endl; }
	if (name == "Hill") { cout << "============ El Gamal 's Cipher ============" << endl; }
	if (name == "RSA") { cout << "============== The RSA Cipher ==============" << endl; }

	cout << "1. ����������� �����" << endl;
	cout << "2. ����������� �����" << endl;
	cout << "3. �������� �������" << endl;
	cout << "4. ��������� �����" << endl;
	cout << "============================================" << endl;
}
