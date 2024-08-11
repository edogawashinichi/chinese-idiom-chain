/// graph.h

/// use a graph to model the longest Chinese idiom chain problem

#pragma once

#include "common_notation.h"

namespace ChineseIdiomChain {

class Graph {
public:
  Graph() = default;
  Graph(const string& file);
  void show() const;

public:
  VI vertices_;
  MIVI successors_;
  MIVI predecessors_;
public:
  int maxVertex() const;
  void getUnvisitedSuccessors(const int vertex, const VI& visited, VI* successors) const;
  void getUnvisitedPredecessors(const int vertex, const VI& visited, VI* predecessors) const;

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
