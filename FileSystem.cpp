#include "fileSystem.h"

#include <fstream>
#include <string>

using namespace std;

extern string PREFIX;

// �������� �� ��, ������ �� ����
bool fileExists(const string& filename)
{
	ifstream file(filename);
	return file.good();
}

// ������� ��� ������ ������ �� �����
string readFromFile(const string& filename)
{
	ifstream file(filename);
	if (!file) throw runtime_error("�� ������� ��������� ����");

	string content;
	string line;
	while (getline(file, line)) { content += line; }

	file.close();
	return content;
}

// ������� ��� �������� �����
void saveToFile(const string& filename, const string& content)
{
	ofstream file(filename);

	file << content; // ������� ���� � ���������� � ���� ����������.

	file.close();
	cout << "\n[" << PREFIX << "] ���� ������: " << filename << std::endl;
}
