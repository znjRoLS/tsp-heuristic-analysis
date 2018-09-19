#include "command_line_arguments.h"

namespace CommandLineArguments {

vector<string> Parse(int argc, char ** argv) {

  vector<string> args;
  for (int i = 1; i < argc; i++) {
    args.push_back(argv[i]);
  }

  return args;
}

} // namespace CommandLineArguments
