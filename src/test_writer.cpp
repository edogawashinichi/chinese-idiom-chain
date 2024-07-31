/// test_writer.cpp

#include "common_test_header.h"

void test_1() {
  TEST_SEPAR(1)
  Reader reader;
  Data data;
  reader.readData(DATA_FILE, &data);
  Encoder encoder;
  Mapper mapper;
  encoder.encodeData(data, &mapper);
  
  Writer writer;
  if (false == writer.cacheMapper(mapper, MAPPER_FILE)) {
    FAIL_INFO_RET(1)
  }
  PASS_INFO(1)
  TEST_SEPAR(1)
}/// test_1

void test_2() {
  TEST_SEPAR(2)
  Reader reader;
  Mapper mapper;
  reader.loadMapper(MAPPER_FILE, &mapper);
  const int mode = 1;
  Builder builder;
  Graph graph;
  builder.buildGraph(mapper, mode, &graph);/// time: 4min
  
  Writer writer;
  if (false == writer.cacheGraph(graph, GRAPH_FILE)) {
    FAIL_INFO_RET(2)
  }
  PASS_INFO(2)
  TEST_SEPAR(2)
}/// test_2

MAIN_START
test_1();
test_2();
MAIN_END
