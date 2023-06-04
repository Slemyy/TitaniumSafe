#include "ShowMenu.h"

using namespace std;

extern string PREFIX;

void showMenu()
{
	cout << "=============== " << PREFIX << " ===============" << endl;
	cout << "1. Шифр Виженера" << endl;
	cout << "2. Шифр Эль Гамаля" << endl;
	cout << "3. Шифр RSA" << endl;
	cout << "4. Очистка консоли" << endl;
	cout << "5. Выход из программы" << endl;
	cout << "============================================" << endl;
}

void showCipherMenu(const string& name)
{
	if (name == "Vigener") { cout << "============ The Vigener Cipher ============" << endl; }
	if (name == "Hill") { cout << "============ El Gamal 's Cipher ============" << endl; }
	if (name == "RSA") { cout << "============== The RSA Cipher ==============" << endl; }

	cout << "1. Зашифровать текст" << endl;
	cout << "2. Дешифровать текст" << endl;
	cout << "3. Очистить консоль" << endl;
	cout << "4. Вернуться назад" << endl;
	cout << "============================================" << endl;
}
