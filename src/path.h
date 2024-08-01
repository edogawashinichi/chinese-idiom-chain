/// path.h

#pragma once

#include "common_notation.h"
#include "mapper.h"

namespace ChineseIdiomChain {

class Path {
public:
  VI codes_;/// consider double link list for searching
public:
  Path() = default;
  Path(const VI&);
  void assign(const VI&);
  inline int size() const {
    return codes_.size();
  }
  
  void show(const Mapper& mapper) const;
};/// class Path

}/// namespace ChineseIdiomChain
