#pragma once

#include <iostream>
#include <vector>

std::string readFromFile(const std::string& filename);

std::vector<int> readFromFile(const std::string& filename, const std::string& type);

bool saveToFile(const std::string& filename, const std::string& content);

bool saveToFile(const std::string& filename, const std::vector<int>& content);

bool fileExists(const std::string& filename);