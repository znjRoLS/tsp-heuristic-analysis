#include "state.h"

namespace TSP {

    State::State(shared_ptr<TSP::World> world):
        world_(world)
    {
        SetDefaultPath();
    }

    State::State(shared_ptr<TSP::World> world, TSP::Path path):
        world_(world),
        current_path_(path)
    {

    }

    void State::SetDefaultPath() {
        current_path_.clear();
        for (int i = 0 ; i < world_->size; i ++) {
            current_path_.push_back(i);
        }
        current_path_.push_back(0);
    }

    double State::CurrentPathCost() {
        double sum = 0;
        int curr_node = current_path_[0];
        for (int i = 1; i < current_path_.size(); i ++) {
            int next_node = current_path_[i];
            sum += (world_[next_node] - world_[curr_node]).abs();
        }
        return sum;
    }

    void State::UpdateOptimalPath(TSP::State state) {
        ASSERT_EQ(world_, state.world_);

        if (state.CurrentPathCost() < CurrentPathCost()) {
            current_path_ = state.current_path_;
        }
    }

} // namespace TSP