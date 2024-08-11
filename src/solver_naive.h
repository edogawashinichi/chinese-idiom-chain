/// solver_naive.h

/// derived class from class Solver, using naive method

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
  void biDFS(LI& path, VI& visited);
  void extendFront(const VI& predecessors, LI& path, VI& visited) const;
  void extendBack(const VI& successors, LI& path, VI& visited) const;

protected:
  int iter_num_;
public:
  inline void setIterNum(const int n) {
    iter_num_ = n;
  }
};

}/// namespace ChineseIdiomChain
