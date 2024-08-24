/// pool_backward.h

#pragma once

#include "pool.h"

namespace ChineseIdiomChain {

class PoolBackward : public Pool {
public:
  virtual void load(const string& file) override;
  virtual void update(const TLI path) override;
};/// class PoolBackward

}/// namespace ChineseIdiomChain
