/// common_math.cpp

#include "common_math.h"
#include <functional> /// fix std::generate problem only for C++17 
#include <numeric>

namespace ChineseIdiomChain {

using std::generate;

vector<int> linearVec(const int n, const int k, const int b) {
  vector<int> res(n, 0);
  int y = b - k;
  generate(res.begin(), res.end(), [&]{y += k; return y;});
  return res;
}

vector<int> idVec(const int n, const int start_val) {
  return linearVec(n, 1, start_val);
}

vector<int> idVec(const int n) {
  return linearVec(n, 1, 0);
}

}/// namespace ChineseIdiomChain
