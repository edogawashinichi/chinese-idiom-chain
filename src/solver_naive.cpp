/// solver_naive.cpp

#include "solver_naive.h"
#include "common_math.h"

namespace ChineseIdiomChain {

SolverNaive::SolverNaive(const string& mapper_file, const string& graph_file)
: Solver(mapper_file, graph_file) {
  iter_num_ = 1;
  this->readConfig();
}/// SolverNaive::SolverNaive

void SolverNaive::run() {
  for (int t = 0; t < iter_num_; ++t) {
    STR_VAR_2_L(t, best_path_.size())
    runOnce();
  }
  showSolution();
  writeSolution();
}/// SolverNaive::run

void SolverNaive::runOnce() {
  const int start_index = randomChoose(graph_->vertices_);
  const int start_vertex = (graph_->vertices_)[start_index];
  #ifdef CIC__DEBUG_INFO
    const string start_idiom((mapper_->code2idiom_).at(start_vertex));
    STR_VAR_L(start_index)
    STR_VAR_L(start_vertex)
    STR_VAR_L(start_idiom)
  #endif
  
  LI path = {start_vertex};
  const int N = graph_->maxVertex() + 1;
  VI visited(N, 0);
  visited[start_vertex] = 1;
  biDFS(path, visited);
}/// SolverNaive::runOnce

void SolverNaive::biDFS(LI& path, VI& visited) {
  #ifdef CIC__DEBUG__INFO
    cout << "start biDFS path size: " << path.size() << "\n";
  #endif
  VI frontUnvPreds;
  graph_->getUnvisitedPredecessors(path.front(), visited, &frontUnvPreds);
  VI backUnvSuccs;
  graph_->getUnvisitedSuccessors(path.back(), visited, &backUnvSuccs);
  if (frontUnvPreds.empty() && backUnvSuccs.empty()) {
    updateSolution(path);
    return;
  }

  if (frontUnvPreds.empty()) {
    extendBack(backUnvSuccs, path, visited);
  }/// if frontUnvPreds.empty
  else if (backUnvSuccs.empty()) {
    extendFront(frontUnvPreds, path, visited);
  }/// if backUnvSuccs.empty
  else {
    const float probability = 0.5f;
    if (bet(probability)) {
      extendBack(backUnvSuccs, path, visited);
    } else {
      extendFront(frontUnvPreds, path, visited);
    }/// if ! bet
  }/// if both not empty
  biDFS(path, visited);
}/// SolverNaive::biDFS

void SolverNaive::extendFront(const VI& predecessors, LI& path, VI& visited) const {
  const int index = randomChoose(predecessors);
  const int pred = predecessors[index];
  path.emplace_front(pred);
  visited[pred] = 1;
}/// SolverNaive::extendFront

void SolverNaive::extendBack(const VI& successors, LI& path, VI& visited) const {
  const int index = randomChoose(successors);
  const int succ = successors[index];
  path.emplace_back(succ);
  visited[succ] = 1;
}/// SolverNaive::extendBack

}/// namespace ChineseIdiomChain
