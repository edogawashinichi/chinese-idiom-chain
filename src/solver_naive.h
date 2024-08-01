/// solver_naive.h

#pragma once

#include "common_notation.h"
#include "solver.h"

namespace ChineseIdiomChain {

class SolverNaive : public Solver {
public:
  SolverNaive(const string& mapper_file, const string& graph_file);
  virtual void run() override;

protected:
  void runOnce();
  void biDFS(VI& path, VI& visited);
  void getUnvisitedPredecessors(const int vertex, const VI& visited, VI* predecessors) const;
  void getUnvisitedSuccessors(const int vertex, const VI& visited, VI* successors) const;
  void extendFront(VI& predecessors, VI& path, VI& visited) const;
  void extendBack(VI& successors, VI& path, VI& visited) const;
};

}/// namespace ChineseIdiomChain
