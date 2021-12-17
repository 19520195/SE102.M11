#pragma once
#include <string>
#include <unordered_set>

#define STL_IN(uns, elm) (uns.find(elm) != uns.end())

class Strings
{
public:
  static std::vector<std::string> Split(const std::string& str, const std::string& delim);

  static std::string Strip(const std::string& str, const std::string& chars = " \t\r\n");
  static std::string Strip(const std::string& str, const std::unordered_set<char>& chars);
};
