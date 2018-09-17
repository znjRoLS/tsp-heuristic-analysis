#include "tsp_util.h"

#include "random_euclidean_world_generator.h"
#include "random_constructive_algorithm.h"
#include "nearest_neighbour_constructive_algorithm.h"
#include "greedy_constructive_algorithm.h"
#include "kopt2_improvement_algorithm.h"
#include "kopt2_search_improvement_algorithm.h"
#include "held_karp_lower_bound_algorithm.h"
#include "min_1tree_lower_bound_algorithm.h"

namespace TSP {

unordered_map<string, shared_ptr<EuclideanWorldGenerator>> world_generators = {
    {"Random Euclidean", make_shared<RandomEuclideanWorldGenerator>()},
};

unordered_map<string, shared_ptr<LowerBoundAlgorithm>> lower_bound_algorithms = {
    {"Min 1-tree", make_shared<Min1treeLowerBoundAlgorithm>()},
    {"Held Karp", make_shared<HeldKarpLowerBoundAlgorithm>(1)},
};

unordered_map<string, shared_ptr<ConstructiveAlgorithm>> constructive_algorithms = {
    {"Random", make_shared<RandomConstructiveAlgorithm>()},
    {"Nearest Neighbour", make_shared<NearestNeighbourConstructiveAlgorithm>()},
    {"Greedy", make_shared<GreedyConstructiveAlgorithm>()},
};

unordered_map<string, shared_ptr<ImprovementAlgorithm>> improvement_algorithms = {
    {"K-Opt 2", make_shared<Kopt2ImprovementAlgorithm>()},
    {"K-Opt 2 Search", make_shared<Kopt2SearchImprovementAlgorithm>()},
};

} // namespace TSP
