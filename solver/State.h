//
// Created by Bojan Roško on 9/2/17.
//

#ifndef TSPHEURISTICANALYSIS_STATE_H
#define TSPHEURISTICANALYSIS_STATE_H

#include "Util.h"

namespace TSP{

  struct State {

  public:
    State(World world);

    World world;
    Path path;

    string ToString();

    static Path Default(int size);
  };

  typedef shared_ptr<State> SharedState;
}

ostream& operator<<(ostream& out, const TSP::SharedState& state);

#endif //TSPHEURISTICANALYSIS_STATE_H
