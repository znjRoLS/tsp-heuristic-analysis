
#include "runner.h"

using TSP::Benchmark::Runner;

int main() {

  Runner runner;

  vector<string> input_files {"../benchmark/configs/test.conf"};

  runner.Run(input_files);

}