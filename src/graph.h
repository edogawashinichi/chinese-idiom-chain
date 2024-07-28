/// graph.h

/// use a graph to model the longest Chinese idiom chain problem

#pragma once

#include <unordered_map>
#include <vector>

namespace ChineseIdiomChain {

using std::unordered_map;
using std::vector;

using VI = vector<int>;
using MIVI = unordered_map<int, VI>;

class Graph {
public:
  VI vertices_;
  MIVI successors_;
  MIVI predecessors_;

public:
  inline int order() const {
    return vertices_.size();
  }
  inline int size() const {
    int sz = 0;
    for (const auto& kv : successors_) {
      sz += kv.second.size();
    }
    return sz;
  }
  inline int startOrder() const {
    return vertices_.size() - predecessors_.size();
  }
  inline int endOrder() const {
    return vertices_.size() - successors_.size();
  }
};/// class Graph

}/// namespace ChineseIdiomChain
