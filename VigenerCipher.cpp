#include "Ciphers.h"
#include "ShowMenu.h"
#include "FileSystem.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

extern string PREFIX;

// ������� ��� ��������
string vigenereEncrypt(const string& plaintext, const string& key)
{
	string ciphertext;
	int textLength = plaintext.length();
	int keyLength = key.length();

	for (int i = 0; i < textLength; ++i)
	{
		char currentChar = plaintext[i];
		char keyChar = key[i % keyLength];
		int shift = (keyChar + 1) % 256; // ����� �������� � ASCII �������

		currentChar = (currentChar + shift) % 256;

		ciphertext += currentChar;
	}

	return ciphertext;
}

// ������� ��� ����������
string vigenereDecrypt(const string& ciphertext, const string& key)
{
	string decryptedText;
	int textLength = ciphertext.length();
	int keyLength = key.length();

	for (int i = 0; i < textLength; ++i)
	{
		char currentChar = ciphertext[i];
		char keyChar = key[i % keyLength];
		int shift = (keyChar + 1) % 256; // ����� �������� � ASCII �������

		currentChar = (currentChar - shift + 256) % 256;

		decryptedText += currentChar;
	}

	return decryptedText;
}

void cipherVigener()
{
	showCipherMenu("Vigener");

	while (true)
	{
		cout << "\n�������� ����������� �������� (������� ��������������� �����) >> ";

		try
		{
			string input;
			cin >> input;

			// ��������� input � �����.
			int choise = stoi(input);

			switch (choise)
			{
			case 1:
			{
				string message;
				cout << "\n������� ����� ��� ���������� >> ";
				cin.ignore();
				getline(cin, message);

				string key;
				cout << "������� ���� ���������� >> ";
				cin >> key;

				string filename;
				cout << "������� ��� �����, ���� ����� �������� ��������� >> ";
				cin >> filename;

				filename += ".txt";

				if (fileExists(filename)) { throw runtime_error("���� ��� ����������"); }

				string result = vigenereEncrypt(message, key);
				saveToFile(filename, result);
				cout << "[" << PREFIX << "] ���������� �����: " << result << endl;
				break;
			}

			case 2:
			{
				string filename;
				cout << "������� ��� �����, ������ ����� ���� ����� >> ";
				cin >> filename;

				filename += ".txt";
				string message = readFromFile(filename);

				string key;
				cout << "������� ���� ���������� >> ";
				cin >> key;

				string result = vigenereDecrypt(message, key);
				cout << result << " " << endl;
				break;
			}

			case 3:
			{
				system("cls");
				cout << "[" << PREFIX << "] ������� ������� �������.\n" << endl;
				showCipherMenu("Vigener");
				break;
			}

			case 4:
			{
				system("cls");
				cout << "[" << PREFIX << "] �� ��������� � ��������� ����." << endl << endl;
				showMenu();
				return;
			}

			default:
				cerr << "\n[" << PREFIX << "] ������������ �����. ���������� �����.";
				break;
			}
		}
		catch (const exception& e) { cerr << "\n[" << PREFIX << "] ������: " << e.what(); }
	}
}