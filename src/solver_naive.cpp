/// solver_naive.cpp

#include "solver_naive.h"
#include "common_math.h"

#define CIC__FUNC_GET_UNVISITED(Some, some) \
void SolverNaive::getUnvisited##Some(const int vertex, const VI& visited, VI* some) const {\
  if (! (graph_->some##_).count(vertex)) return;\
  for (const auto v : (graph_->some##_).at(vertex)) {\
    if (visited[v]) continue;\
    some->emplace_back(v);\
  }\
}

namespace ChineseIdiomChain {

SolverNaive::SolverNaive(const string& mapper_file, const string& graph_file)
: Solver(mapper_file, graph_file) {
}

void SolverNaive::run() {
  const int T = 100000;
  for (int t = 0; t < T; ++t) {
    #ifdef CIC__DEBUG_INFO
      STR_VAR_L(t)
    #endif
    runOnce();
  }
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
  
  VI path = {start_vertex};
  const int N = graph_->maxVertex() + 1;
  VI visited(N, 0);
  visited[start_vertex] = 1;
  biDFS(path, visited);
}/// SolverNaive::runOnce

void SolverNaive::biDFS(VI& path, VI& visited) {
  VI frontUnvPreds;
  getUnvisitedPredecessors(path.front(), visited, &frontUnvPreds);
  VI backUnvSuccs;
  getUnvisitedSuccessors(path.back(), visited, &backUnvSuccs);
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

void SolverNaive::extendFront(VI& predecessors, VI& path, VI& visited) const {
  shuffle(predecessors);
  const auto pred = predecessors.front();
  path.emplace(path.begin(), pred);/// TODO: low efficiency
  visited[pred] = 1;
}/// SolverNaive::extendFront

void SolverNaive::extendBack(VI& successors, VI& path, VI& visited) const {
  shuffle(successors);
  const auto succ = successors.front();
  path.emplace_back(succ);
  visited[succ] = 1;
}/// SolverNaive::extendBack

CIC__FUNC_GET_UNVISITED(Predecessors, predecessors)
CIC__FUNC_GET_UNVISITED(Successors, successors)

}/// namespace ChineseIdiomChain
