#include "random_euclidean_world_generator.h"

#include <memory>
#include "random.h"

using std::shared_ptr;
using std::make_shared;

namespace TSP {

shared_ptr<Nodes2> RandomEuclideanWorldGenerator::GenerateNodes(int n) {
  shared_ptr<Nodes2> nodes = make_shared<Nodes2>((unsigned) n);

  for (int i = 0; i < n; i++) {
    (*nodes)[i] = {Random::GetDouble(), Random::GetDouble()};
  }

  return nodes;
}

} // namespace TSP
