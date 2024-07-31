/// builder.h

/// mapper(mode) ----builder----> graph

#pragma once

#include "common_notation.h"
#include "filter.h"
#include "graph.h"

namespace ChineseIdiomChain {

class Builder {
public:
  bool buildGraph(const Mapper& mapper, const int mode, Graph* graph);
protected:
  bool isConnected(const string& prev_idiom, const string& next_idiom);
};/// class Builder

}/// namespace ChineseIdiomChain
