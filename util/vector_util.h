#pragma once

#include <string>
#include <sstream>

using std::string;
using std::stringstream;

template<typename T>
string vector_to_string(vector<T> data) {
  stringstream out;
  out << "{";
  for (T& elem : data) out << elem << ", ";
  out.seekp(-2, out.cur);
  out << "}";
  return out.str();
}
