/// solver.cpp

#include "solver.h"

namespace ChineseIdiomChain {

using std::make_unique;

Solver::Solver(const string& mapper_file, const string& graph_file) 
: mapper_(nullptr), graph_(nullptr) {
  mapper_ = make_unique<Mapper>(mapper_file);
  graph_ = make_unique<Graph>(graph_file);
}/// Solver::Solver

void Solver::showSolution() const {
  best_path_.show(*mapper_);
}/// Solver::showSolution

}/// namespace ChineseIdiomChain
