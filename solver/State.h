//
// Created by Bojan Roško on 9/2/17.
//

#ifndef TSPHEURISTICANALYSIS_STATE_H
#define TSPHEURISTICANALYSIS_STATE_H

#include "Util.h"

namespace TSP{

  struct State {
    World world;
    Path path;
  };

  typedef shared_ptr<State> SharedState;
}

ostream& operator<<(ostream& out, const TSP::SharedState& state);

#endif //TSPHEURISTICANALYSIS_STATE_H
