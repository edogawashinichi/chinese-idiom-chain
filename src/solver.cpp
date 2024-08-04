/// solver.cpp

#include "solver.h"
#include "reader.h"
#include "common_const.h"

namespace ChineseIdiomChain {

Solver::Solver(const string& mapper_file, const string& graph_file) 
: mapper_(nullptr), graph_(nullptr) {
  mapper_ = make_unique<Mapper>(mapper_file);
  graph_ = make_unique<Graph>(graph_file);
}/// Solver::Solver

bool Solver::readConfig() {
  Reader reader;
  reader.readConfig(CONFIG_FILE, this);
}/// Solver::readConfig

bool Solver::updateSolution(const LI& path) {
  if (path.size() < best_path_.size()) return false;
  best_path_.assign(path);
  return true;
}/// Solver::updateSolution

void Solver::showSolution() const {
  best_path_.show(*mapper_);
}/// Solver::showSolution

}/// namespace ChineseIdiomChain
