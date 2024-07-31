/// writer.h

/// write direct and intermediate results

#pragma once

#include "common_notation.h"
#include "Mapper.h"
#include "Graph.h"


namespace ChineseIdiomChain {

class Writer {
public:
  bool cacheMapper(const Mapper& mapper, const string& file);
  bool cacheGraph(const Graph& graph, const string& file);
};/// class Writer

}/// namespace ChineseIdiomChain
