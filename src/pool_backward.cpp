/// pool_backward.cpp

#include "pool_backward.h"
#include "reader.h"
#include "common_math.h"

namespace ChineseIdiomChain {

void PoolBackward::load(const string& file) {
  Reader reader;
  reader.loadSnippetsBackward(file, &end2path_);
}/// PoolBackward::load

void PoolBackward::update(const LI& path) {
  const VI vec(path.begin(), path.end());
  const int min_index = energy_ - 1;
  if (min_index < 0 || min_index >= vec.size()) return;
  const int last_index = randomChoose(vec, min_index, vec.size() - 1);
  const int last_vertex = vec[last_index];
  if (false == end2path_.count(last_vertex)) {
    end2path_.insert(PIVI(last_vertex, VI(vec.begin(), vec.begin() + last_index + 1)));
    return;
  }
  const VI& memo = end2path_.at(last_vertex);
  if (betSharpenPow(last_index, memo.size())) {
    end2path_[last_vertex] = VI(vec.begin(), vec.begin() + last_index + 1);
  }
}/// PoolBackward::update

}/// namespace ChineseIdiomChain
