#pragma once

#include <iostream>
#include <vector>

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v);

// ������� ��� ���������� ������. 
__int64 findMod(__int64 number, __int64 degree, __int64 module);

// ������� ��� ���������� �������� �����
bool isPrime(const int& number);

// ������� ��� ���������� ����������� ������ ��������
__int64 gcd(__int64 a, __int64 b);
