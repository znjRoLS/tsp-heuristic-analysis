#include "split_str.h"

std::vector<std::string> split_str(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split_str(s, delim, std::back_inserter(elems));
  return elems;
}