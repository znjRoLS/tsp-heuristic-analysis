
#include "runner.h"
#include "command_line_arguments.h"

using TSP::Benchmark::Runner;

int main(int argc, char **argv) {

  Runner runner;

  vector<string> input_files = CommandLineArguments::Parse(argc, argv);

  runner.Run("../benchmark/configs/", input_files, "../benchmark/outputs/");

}