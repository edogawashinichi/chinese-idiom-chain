/// reader.h

/// DATA_FILE ----reader----> Data
/// MAPPER_FILE ----reader----> Mapper
/// GRAPH_FILE ----reader----> Graph

#pragma once

#include "common_notation.h"
#include "data.h"
#include "mapper.h"
#include "graph.h"
#include "solver.h"
#include "path.h"

namespace ChineseIdiomChain {

class Reader {
public:
  bool readData(const string& file, Data* data);
  bool loadMapper(const string& file, Mapper* mapper);
  bool loadGraph(const string& file, Graph* graph);
  bool readConfig(const string& file, Solver* solver);
  bool loadSolution(const string& file, const Mapper& mapper, Path* path);
  bool loadSeed(const string& file, LI* community);
  bool loadSnippetsForward(const string& file, MIVI* end2path);
  bool loadSnippetsBackward(const string& file, MIVI* end2path);
};

}/// namespace ChineseIdiomChain
