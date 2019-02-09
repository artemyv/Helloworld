#pragma once
#include <string>

std::wstring utf8toutf16(const std::string& input, bool ignore_invalid = true);
std::wstring utf8toutf16(const char* input, bool ignore_invalid = true);
