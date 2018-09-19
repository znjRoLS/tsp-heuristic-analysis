#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

namespace CommandLineArguments {

vector<string> Parse(int argc, char **argv);

} // namespace CommandLineArguments
