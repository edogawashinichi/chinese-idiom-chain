/// path.h

#pragma once

#include "common_notation.h"
#include "mapper.h"

namespace ChineseIdiomChain {

class Path {
public:
  LI vertices_;
public:
  Path() = default;
  Path(const LI&);
  void assign(const LI&);
  inline void extendBack(const int v) {
    vertices_.emplace_back(v);
  }
  inline int size() const {
    return vertices_.size();
  }

  int getForwardMaxUniqueIndex(const VI& memo, const VI& visited) const;
  int getBackwardMinUniqueIndex(const VI& memo, const VI& visited) const;
  
  void show(const Mapper& mapper) const;
};/// class Path

}/// namespace ChineseIdiomChain
