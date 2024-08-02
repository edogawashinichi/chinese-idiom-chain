/// path.h

#pragma once

#include "common_notation.h"
#include "mapper.h"

namespace ChineseIdiomChain {

class Path {
public:
  ///VI vertices_;/// consider double link list for searching
  LI vertices_;
public:
  Path() = default;
  Path(const LI&);
  void assign(const LI&);
  inline int size() const {
    return vertices_.size();
  }
  
  void show(const Mapper& mapper) const;
};/// class Path

}/// namespace ChineseIdiomChain
