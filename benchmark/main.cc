
#include "runner.h"

using TSP::Benchmark::Runner;

int main() {

  Runner runner;

  vector<string> input_files {"bench3.conf"};

  runner.Run("../benchmark/configs/", input_files, "../benchmark/outputs/");

}