/// solver.h

/// to solve the problem

#pragma once

#include "common_notation.h"
#include "Mapper.h"
#include "Graph.h"
#include "Path.h"

namespace ChineseIdiomChain {

class Solver {
public:
  Solver(const string& mapper_file, const string& graph_file);
  virtual void run() = 0;
  void showSolution() const;

protected:
  bool readConfig();
  bool updateSolution(const LI& path);

protected:
  unique_ptr<Mapper> mapper_;
  unique_ptr<Graph> graph_;

protected:
  Path best_path_;
};

}/// namespace ChineseIdiomChain
