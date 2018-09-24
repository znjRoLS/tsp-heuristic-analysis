#include <limits>
#include "nearest_neighbour_double_ended_constructive_algorithm.h"

#include <limits>

using std::numeric_limits;

#define CHOSEN 0.6
#define BEST 1.0
#define CONSIDERING 0.2

namespace TSP {

void NearestNeighbourDoubleEndedConstructiveAlgorithm::Reset() {
  current_path_.clear();
  //current_path_.push_back(0);

  path_.clear();
  path_.push_back(0);
  current_last_head_ = 0;
  current_last_tail_ = 0;


  if (enable_visuals_) {
    visualization_.clear();
  }


  for (int i = 1; i < world_->size; i++) {
    unvisited_.insert(i);
  }

  current_processing_ = unvisited_.begin();
  current_closest_dist_ = numeric_limits<double>::max();
  current_processing_head_ = false;

}

bool NearestNeighbourDoubleEndedConstructiveAlgorithm::Iterate(int granularity) {
  if (granularity == 2) {

    if (enable_visuals_) {
      if (!visualization_.empty() && visualization_.rbegin()->strength == CONSIDERING) {
        visualization_.pop_back();
      }
    }

    if (current_processing_ != unvisited_.end()) {

      int current_last_;
      if (current_processing_head_) {
        current_last_ = current_last_head_;
      } else {
        current_last_ = current_last_tail_;
      }

      if ((*world_->distances_)[current_last_][*current_processing_] < current_closest_dist_) {
        if (enable_visuals_) {
          if (!visualization_.empty() && visualization_.rbegin()->strength == BEST) {
            visualization_.pop_back();
          }
        }

        current_closest_ = *current_processing_;
        current_closest_head_ = current_processing_head_;
        current_closest_dist_ = (*world_->distances_)[current_last_][current_closest_];

        PushVisualEdge({current_last_, current_closest_, GlobalColor::green, BEST});
      } else {
        PushVisualEdge({current_last_, *current_processing_, GlobalColor::blue, CONSIDERING});
      }

      if (current_processing_head_){
        current_processing_head_ = false;
        current_processing_++;
      } else {
        current_processing_head_ = true;
      }

    } else {

      if (enable_visuals_) {
        TSP_ASSERT_EQ(visualization_.rbegin()->strength, BEST);

        visualization_.rbegin()->strength = CHOSEN;
        visualization_.rbegin()->color = GlobalColor::lightGray;
      }

      if (current_closest_head_) {
        path_.push_back(current_closest_);
        current_last_head_ = current_closest_;
      } else {
        path_.push_front(current_closest_);
        current_last_tail_ = current_closest_;
      }

      unvisited_.erase(current_closest_);

      if (unvisited_.empty()) {

        while(path_.front() != 0) {
          path_.push_back(path_.front());
          path_.pop_front();
        }

        while (!path_.empty()) {
          current_path_.push_back(path_.front());
          path_.pop_front();
        }

        current_path_.push_back(0);
        return false;
      }

      current_processing_ = unvisited_.begin();
      current_closest_dist_ = numeric_limits<double>::max();

    }
  } else if (granularity == 1) {
    bool result = true;
    unsigned last_size = unvisited_.size();
    while (last_size == unvisited_.size()) {
      result = Iterate(2);
    }
    return result;

  } else if (granularity == 0) {
    while (Iterate(1));
    return false;
  }

  return true;
}

int NearestNeighbourDoubleEndedConstructiveAlgorithm::GetMaxGranularity() {
  return 2;
}

};// namespace TSP
