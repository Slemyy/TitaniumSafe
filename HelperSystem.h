#pragma once

#include <iostream>
#include <vector>

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v);

// Функция для нахождения модуля. 
__int64 findMod(__int64 number, __int64 degree, __int64 module);

// Функция для нахождения простого числа
bool isPrime(const int& number);

// Функция для вычисления наибольшего общего делителя
__int64 gcd(__int64 a, __int64 b);
