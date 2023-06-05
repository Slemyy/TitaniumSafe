#include "FileSystem.h"

#include <fstream>
#include <string>

using namespace std;

string filename = "plaintext.txt";
string encryptedFile = "encrypted.txt";
string decryptedFile = "decrypted.txt";

// �������� �� ��, ������ �� ����
bool fileExists(const string& filename)
{
	ifstream file(filename);
	return file.good();
}

// ������� ��� ������ ������ �� �����
string readFromFile(const string& filename)
{
	string content;
	ifstream file(filename);

	if (file.is_open())
	{
		string line;
		while (getline(file, line)) { content += line; }
		file.close();
	}
	
	else throw runtime_error("�� ������� ��������� ����");
	return content;
}

// ������� ��� ������ ������ �� �����
vector<int> readFromFile(const string& filename, const string& type)
{
	vector<int> content, result;
	ifstream file(filename);

	if (file.is_open())
	{
		int number;
		while (file >> number) {
			result.push_back(number);
		}
		file.close();
	}
	else throw runtime_error("�� ������� ��������� ����");

	return result;
}

// ������� ��� �������� �����
bool saveToFile(const string& filename, const string& content)
{
	ofstream file(filename);

	if (file.is_open())
	{
		file << content; // ������� ���� � ���������� � ���� ����������.
		file.close();
		return true;
	}

	else throw runtime_error("�� ������� ������� ����");
}

// ������� ��� �������� �����
bool saveToFile(const string& filename, const vector<int>& content)
{
	ofstream file(filename);

	if (file.is_open())
	{
		for (const auto& i : content)
		{
			file << i << " "; // ������� ���� � ���������� � ���� ����������.
		}

		file.close();
		return true;
	}

	else throw runtime_error("�� ������� ������� ����");
}
