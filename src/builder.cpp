/// builder.cpp

#include "builder.h"
#include "common_math.h"
#include "common_const.h"

namespace ChineseIdiomChain {

bool Builder::buildGraph(const Mapper& mapper, const int mode, Graph* graph) {
  if (nullptr == graph) {
    /// TODO
    return false;
  }

  Filter filter;
  const auto code2idiom = filter.code2Idiom(mapper, mode);  
  (graph->vertices_).reserve(code2idiom.size());

  for (const auto& kv1 : code2idiom) {
    (graph->vertices_).push_back(kv1.first);

    for (const auto& kv2 : code2idiom) {
      if (kv1.first == kv2.first) continue;
      if (false == isConnected(kv1.second, kv2.second)) continue;
      (graph->successors_)[kv1.first].push_back(kv2.first);
      (graph->predecessors_)[kv2.first].push_back(kv1.first);
    }
  }

  /// TODO
  return true;
}/// Builder::buildGraph

bool Builder::isConnected(const string& prev_idiom, const string& next_idiom) {
  const vector<int> pos(idVec(CHINESE_UTF8_BYTES));
  const int psz = prev_idiom.size(), nsz = next_idiom.size();
  for (const auto i : pos) {
    const int ni = i;
    const int pi = psz - CHINESE_UTF8_BYTES + i;
    if (pi < 0 || pi >= psz) return false;
    if (ni < 0 || ni >= nsz) return false;
    if (prev_idiom[pi] != next_idiom[ni]) return false;
  }
  return true;
}/// Builder::isConnected

}/// namespace ChineseIdiomChain
