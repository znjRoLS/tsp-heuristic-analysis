#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include "world_generator.h"
#include "euclidean_world_generator.h"
#include "random_euclidean_world_generator.h"

using std::string;
using std::unordered_map;
using std::shared_ptr;
using std::make_shared;

namespace TSP {
    extern unordered_map<string, shared_ptr<WorldGenerator>> world_generators;
}