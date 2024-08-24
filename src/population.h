/// population.h

#pragma once

#include "common_notation.h"

namespace ChineseIdiomChain {

class Population {
public:
  int capacity_;
  VULI communities_;

public:
  void init();
  void load(const string& dir);
  void cache(const string& dir);
  void worship(const LI& path);
  int size() const;
};/// class Population

}/// namespace ChineseIdiomChain
