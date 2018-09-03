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

void Randomize(vector<int> *data);

} // namespace Random
