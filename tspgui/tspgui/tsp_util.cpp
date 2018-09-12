#include "tsp_util.h"

namespace TSP {

unordered_map<string, shared_ptr<EuclideanWorldGenerator>> world_generators = {
    {"Random Euclidean World Generator", make_shared<RandomEuclideanWorldGenerator>()},
};

unordered_map<string, shared_ptr<ConstructiveAlgorithm>> constructive_algorithms = {
    {"Random Constructive Algorithm", make_shared<RandomConstructiveAlgorithm>()},
};

unordered_map<string, shared_ptr<ImprovementAlgorithm>> improvement_algorithms = {
    {"K-Opt 2 Improvement Algorithm", make_shared<Kopt2ImprovementAlgorithm>()},
    {"K-Opt 2 Search Improvement Algorithm", make_shared<Kopt2SearchImprovementAlgorithm>()},
};

} // namespace TSP
