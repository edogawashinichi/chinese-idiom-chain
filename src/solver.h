/// solver.h

/// base class to solve the problem

#pragma once

#include "common_notation.h"
#include "mapper.h"
#include "graph.h"
#include "path.h"

namespace ChineseIdiomChain {

class Solver {
public:
  Solver(const string& mapper_file, const string& graph_file);
protected:
  unique_ptr<Mapper> mapper_;
  unique_ptr<Graph> graph_;

public:
  virtual void run() = 0;

protected:
  bool readConfig();

protected:
  Path best_path_;
  virtual bool updateSolution(const LI& path);
  void showSolution() const;
  void writeSolution() const;
  void loadSolution();
};

}/// namespace ChineseIdiomChain
