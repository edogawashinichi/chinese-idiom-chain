/// solver_naive.h

#pragma once

#include "common_notation.h"
#include "solver.h"

namespace ChineseIdiomChain {

class SolverNaive : public Solver {
public:
  SolverNaive(const string& mapper_file, const string& graph_file);
  virtual void run() override;
};

}/// namespace ChineseIdiomChain
