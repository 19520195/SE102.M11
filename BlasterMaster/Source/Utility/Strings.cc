#include "Strings.hh"

std::vector<std::string> Strings::Split(const std::string& str, const std::string& delim)
{
  std::vector<std::string> tokens;
  size_t last = 0; size_t next = 0;
  for (; (next = str.find(delim, last)) != std::string::npos; last = next + 1)
    tokens.emplace_back(str.substr(last, next - last));
  tokens.emplace_back(str.substr(last));
  return tokens;
}

std::string Strings::Strip(const std::string& str, const std::string& chars)
{
  return Strip(str, std::unordered_set<char>(chars.begin(), chars.end()));
}

std::string Strings::Strip(const std::string& str, const std::unordered_set<char>& chars)
{
  size_t left = 0;
  size_t right = str.length();

  while (left < right && STL_IN(chars, str[left])) ++left;
  while (left < right && STL_IN(chars, str[right - 1])) --right;

  if (left >= right) return std::string();
  return str.substr(left, right - left);
}
