/// pool_forward.cpp

#include "pool_forward.h"
#include "reader.h"
#include "common_math.h"

namespace ChineseIdiomChain {

void PoolForward::load(const string& file) {
  Reader reader;
  reader.loadSnippetsForward(file, &end2path_);
}/// PoolForward::load

void PoolForward::update(const TLI path) {
  const VI vec(path->begin(), path->end());
  const int max_index = vec.size() - energy_;
  if (max_index < 0 || max_index >= vec.size()) return;
  const int start_index = randomChoose(vec, 0, max_index);
  const int start_vertex = vec[start_index];
  if (false == end2path_.count(start_vertex)) {
    end2path_.insert(PIVI(start_vertex, VI(vec.begin() + start_index, vec.end())));
    return;
  }
  const VI& memo = end2path_.at(start_vertex);
  if (betSharpenPow(vec.size() - start_index, memo.size())) {
    end2path_[start_vertex] = VI(vec.begin() + start_index, vec.end());
  }
}/// PoolForward::update

}/// namespace ChineseIdiomChain
