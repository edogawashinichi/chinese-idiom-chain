/// test_solver.cpp

#include "common_test_header.h"

void test_1() {
  TEST_SEPAR(1)
  unique_ptr<Solver> solver = make_unique<SolverNaive>(MAPPER_FILE, GRAPH_FILE);
  solver->run();
  solver->showSolution();
  PASS_INFO(1)
  TEST_SEPAR(1)
}/// test_1

MAIN_START
test_1();
MAIN_END
