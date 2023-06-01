#pragma once

#include <iostream>

std::string readFromFile(const std::string& filename);

void saveToFile(const std::string& filename, const std::string& content);

bool fileExists(const std::string& filename);