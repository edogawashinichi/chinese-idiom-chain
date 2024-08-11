/// writer.h

/// write direct and intermediate results

#pragma once

#include "common_notation.h"
#include "mapper.h"
#include "graph.h"
#include "path.h"


namespace ChineseIdiomChain {

class Writer {
public:
  bool cacheMapper(const Mapper& mapper, const string& file);
  bool cacheGraph(const Graph& graph, const string& file);
  bool writeSolution(const Path& path, const Mapper& mapper, const string& file);
  bool cacheSeed(const LI& community, const string& file);
  bool cacheSnippets(const MIVI& end2path, const string& file);
};/// class Writer

}/// namespace ChineseIdiomChain
