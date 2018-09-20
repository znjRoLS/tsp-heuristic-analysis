#pragma once

#include <vector>

using std::vector;

namespace Random {

int GetInt();

int GetInt(int max);

int GetInt(int min, int max);

double GetDouble();

double GetDouble(double max);

double GetDouble(double min, double max);

void Shuffle(std::vector<int>::iterator begin, std::vector<int>::iterator end);

void Shuffle(std::vector<std::pair<int,int>>::iterator begin, std::vector<std::pair<int,int>>::iterator end);

template<typename T>
T GetChoice(vector<T> items) {
  if (items.empty()) return T();
  return items[GetInt(items.size() - 1)];
}

int GetWeightedInt(vector<double> weights);

template<typename T>
T GetWeightedChoice(vector<T> items, vector<double> weights) {
  return items[GetWeightedInt(weights)];
}

} // namespace Random
