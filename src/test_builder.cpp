/// test_builder.cpp

#include "common_test_header.h"

void test_1() {
  TEST_SEPAR(1)
  const int EXP_ORDER = 29502;
  const int EXP_SIZE = 713426;
  const int EXP_START_ORDER = 2817;
  const int EXP_END_ORDER = 3183;
  const string file(DATA_FILE);
  Reader reader;
  Data data;
  reader.readData(file, &data);
  Encoder encoder;
  Mapper mapper;
  encoder.encodeData(data, &mapper);
  const int mode = 1;
  Graph graph;
  Builder builder;
  if (false == builder.buildGraph(mapper, mode, &graph)) {
    FAIL_INFO_RET(1)
  }
  cout << "graph order: " << graph.order() << "\n";
  cout << "graph size: " << graph.size() << "\n";
  if (EXP_ORDER != graph.order() || EXP_SIZE != graph.size()) {
    FAIL_INFO_RET(1)
  }
  cout << "start order: " << graph.startOrder() << "\n";
  cout << "end order: " << graph.endOrder() << "\n";
  if (EXP_START_ORDER != graph.startOrder() || EXP_END_ORDER != graph.endOrder()) {
    FAIL_INFO_RET(1)
  }

  /// TODO
  // benchmark for time
  PASS_INFO(1)
  TEST_SEPAR(1)
}/// test_1

MAIN_START
test_1();
MAIN_END
