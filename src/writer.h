/// writer.h

/// write direct and intermediate results

#pragma once

#include "Mapper.h"

namespace ChineseIdiomChain {

class Writer {
public:
  bool writeMapper(const Mapper& mapper, const string& file);
  bool writeGraph(const Graph& graph, const string& file);
};/// class Writer

}/// namespace ChineseIdiomChain
