/// path.h

#pragma once

#include "common_notation.h"
#include "mapper.h"

namespace ChineseIdiomChain {

class Path {
public:
  VI codes_;
public:
  Path() = default;
  Path(const VI&);
  void assign(const VI&);

  void show(const Mapper& mapper) const;
};/// class Path

}/// namespace ChineseIdiomChain
