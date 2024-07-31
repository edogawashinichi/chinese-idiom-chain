/// test_reader.cpp

#include "common_test_header.h"

void test_1() {
  TEST_SEPAR(1)
  const int EXP = 30895;
  const string file(DATA_FILE);
  Reader reader;
  Data data;

  if (false == reader.readData(file, &data)) {
    FAIL_INFO_RET(1)
  }

  cout << "data size: " << data.idioms_.size() << "\n";
  if (EXP != data.idioms_.size()) {
    cout << "EXP: " << EXP << "\n";
    FAIL_INFO_RET(1)
  }
  PASS_INFO(1)
  TEST_SEPAR(1)
}/// test_1

void test_2() {
  TEST_SEPAR(2)
  const int EXP = 30895;
  Reader reader;
  Mapper mapper;
  if (false == reader.loadMapper(MAPPER_FILE, &mapper)) {
    FAIL_INFO_RET(2)
  }
  
  cout << "mapper size: " << mapper.code2idiom_.size() << "\n";
  if (EXP != mapper.code2idiom_.size()) {
    FAIL_INFO_RET(2)
  }
  PASS_INFO(2)
  TEST_SEPAR(2)
}/// test_2

void test_3() {
  TEST_SEPAR(3)
  const int EXP_ORDER = 29502;
  const int EXP_SIZE = 713426;
  const int EXP_START_ORDER = 2817;
  const int EXP_END_ORDER = 3183;
  Reader reader;
  Graph graph;
  if (false == reader.loadGraph(GRAPH_FILE, &graph)) {
    FAIL_INFO_RET(3)
  }

  cout << "graph order: " << graph.order() << "\n";
  cout << "graph size: " << graph.size() << "\n";
  if (EXP_ORDER != graph.order() || EXP_SIZE != graph.size()) {
    FAIL_INFO_RET(3)
  }
  cout << "start order: " << graph.startOrder() << "\n";
  cout << "end order: " << graph.endOrder() << "\n";
  if (EXP_START_ORDER != graph.startOrder() || EXP_END_ORDER != graph.endOrder()) {
    FAIL_INFO_RET(3)
  }
  PASS_INFO(3)
  TEST_SEPAR(3)
}/// test_3

MAIN_START
test_1();
test_2();
test_3();
MAIN_END
