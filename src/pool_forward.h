/// pool_forward.h

#include "pool.h"

namespace ChineseIdiomChain {

class PoolForward : public Pool {
public:
  virtual void load(const string& file) override;
  virtual void update(const LI& path) override;
};/// class PoolForward

}/// namespace ChineseIdiomChain
