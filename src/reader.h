/// reader.h

/// DATA_FILE ----reader----> Data
/// MAPPER_FILE ----reader----> Mapper
/// GRAPH_FILE ----reader----> Graph

#pragma once

#include "common_notation.h"
#include "data.h"
#include "Mapper.h"
#include "Graph.h"
#include "Solver.h"

namespace ChineseIdiomChain {

class Reader {
public:
  bool readData(const string& file, Data* data);
  bool loadMapper(const string& file, Mapper* mapper);
  bool loadGraph(const string& file, Graph* graph);
  bool readConfig(const string& file, Solver* solver);
};

}/// namespace ChineseIdiomChain
