/// population.h

#pragma once

#include "common_notation.h"

namespace ChineseIdiomChain {

class Population {
public:
  int capacity_;
  VPLI communities_;

public:
  void init();
  void load(const string& dir);
  void cache(const string& dir);
};/// class Population

}/// namespace ChineseIdiomChain
