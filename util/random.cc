
#include <random>

using std::shuffle;

#include "random.h"

namespace Random {

std::random_device rd;
std::mt19937 mt(rd());

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

void Randomize(vector<int> *data) {
  shuffle(data->begin(), data->end(), mt);
}

} // namespace Random
