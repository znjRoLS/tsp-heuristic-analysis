#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <iterator>

template<typename Out>
void split_str(const std::string &s, char delim, Out result) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    *(result++) = item;
  }
}

std::vector<std::string> split_str(const std::string &s, char delim);
