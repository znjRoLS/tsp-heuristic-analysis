#include "tsp_util.h"

namespace TSP {
unordered_map<string, shared_ptr<WorldGenerator>> world_generators = {
   {"Random Euclidean World Generator", make_shared<RandomEuclideanWorldGenerator>()},
};
}
