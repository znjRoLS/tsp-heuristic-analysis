#include <random>
#include <algorithm>
#include <climits>
#include <vector>
#include <ctime>

using std::shuffle;

#include "random.h"

namespace Random {

// MINGW implementation of random_device returns same number always
// https://sourceforge.net/p/mingw-w64/bugs/338/
// std::random_device rd;
std::mt19937 mt((unsigned) time(nullptr));

int GetInt(int min, int max) {
  std::uniform_int_distribution<int> dist(min, max);
  return dist(mt);
}

int GetInt(int max) {
  return GetInt(0, max);
}

int GetInt() {
  return GetInt(INT_MAX);
}

double GetDouble(double min, double max) {
  std::uniform_real_distribution<double> dist(min, max);
  return dist(mt);
}

double GetDouble(double max) {
  return GetDouble(0, max);
}

double GetDouble() {
  return GetDouble(1.0);
}

void Shuffle(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
  shuffle(begin, end, mt);
}


void Shuffle(std::vector<std::pair<int,int>>::iterator begin, std::vector<std::pair<int,int>>::iterator end) {
  shuffle(begin, end, mt);
}

int GetWeightedInt(vector<double> weights) {
  if (weights.empty()) return -1;

  double sum = 0;
  for (auto &item : weights) sum += item;

  double r = GetDouble(sum);

  for (unsigned i = 0; i < weights.size(); i++) {
    if (r > weights[i]) {
      r -= weights[i];
    } else {
      return i;
    }
  }

  // not reachable;
  return -1;
}

} // namespace Random
