/// solver_naive.cpp

#include "solver_naive.h"
#include "common_math.h"

namespace ChineseIdiomChain {

SolverNaive::SolverNaive(const string& mapper_file, const string& graph_file)
: Solver(mapper_file, graph_file) {
}

void SolverNaive::run() {
  const int start_index = randomChoose(graph_->vertices_);
  const int start_vertex = (graph_->vertices_)[start_index];
  #ifdef CIC__DEBUG_INFO
    const string start_idiom((mapper_->code2idiom_).at(start_vertex));
    STR_VAR_L(start_index)
    STR_VAR_L(start_vertex)
    STR_VAR_L(start_idiom)
  #endif
}/// SolverNaive::run

}/// namespace ChineseIdiomChain
