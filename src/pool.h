/// pool.h

#pragma once

#include "common_notation.h"

namespace ChineseIdiomChain {

class Pool {
public:
  MIVI end2path_;
  int energy_;

public:
  virtual void load(const string& file) = 0;
  void cache(const string& file);
  virtual void update(const LI& path) = 0;
};/// class Pool

}/// namespace ChineseIdiomChain
