#include "Ciphers.h"
#include "ShowMenu.h"
#include "FileSystem.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

extern string PREFIX;
extern string filename;
extern string encryptedFile;
extern string decryptedFile;
extern const char* SYSTEM_CLEAR;

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

bool isEnglishText(const string& text) {
	for (char c : text) {
		if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
			return false;
	}
	return true;
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

				if (saveToFile(filename, message))
				{
					cout << "\n[" << PREFIX << "] ���� �������: " << filename << std::endl;
				}

				string key;
				while (true)
				{
					cout << "������� ���� ���������� >> ";
					cin >> key;

					if (isEnglishText(key)) { break; }
					cout << "\n[" << PREFIX << "] ������: ���� ������ ���� �� ���������� �����" << endl;
				}

				string result = vigenereEncrypt(message, key);
				if (saveToFile(encryptedFile, result)) 
				{ 
					cout << "\n[" << PREFIX << "] ���� �������: " << encryptedFile << std::endl;
				}

				cout << "[" << PREFIX << "] ���������� �����: " << result << endl;
				break;
			}

			case 2:
			{
				string key;
				while (true)
				{
					cout << "������� ���� ���������� >> ";
					cin >> key;

					if (isEnglishText(key)) { break; }
					cout << "\n[" << PREFIX << "] ������: ���� ������ ���� �� ���������� �����" << endl;
				}

				string message = readFromFile(encryptedFile);
				string result = vigenereDecrypt(message, key);

				if (saveToFile(decryptedFile, result))
				{
					cout << "\n[" << PREFIX << "] ���� �������: " << decryptedFile << std::endl;
				}
				cout << "[" << PREFIX << "] ���������� �����: " << result << endl;

				break;
			}

			case 3:
			{
				system(SYSTEM_CLEAR);
				cout << "[" << PREFIX << "] ������� ������� �������.\n" << endl;
				showCipherMenu("Vigener");
				break;
			}

			case 4:
			{
				system(SYSTEM_CLEAR);
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