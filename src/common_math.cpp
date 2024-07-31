/// common_math.cpp

#include "common_math.h"

#include <functional> /// fix std::generate problem only for C++17 
#include <numeric>
#include <random>

#define CIC__RAND_ENV(sum, res) \
std::random_device rd;\
std::mt19937 rng(rd());\
std::uniform_int_distribution<int> distr(0, sum - 1);\
const int res = distr(rng);

namespace ChineseIdiomChain {

using std::generate;

bool isEqual(const VI& u, const VI& v) {
  if (u.size() != v.size()) return false;
  for (int i = 0; i < u.size(); ++i) {
    if (u[i] != v[i]) return false;
  }
  return true;
}/// isEqual

VI linearVec(const int n, const int k, const int b) {
  VI res(n, 0);
  int y = b - k;
  generate(res.begin(), res.end(), [&]{y += k; return y;});
  return res;
}/// linearVec

VI idVec(const int n, const int start_val) {
  return linearVec(n, 1, start_val);
}/// idVec

VI idVec(const int n) {
  return linearVec(n, 1, 0);
}/// idVec

int randomChoose(const VI& vec) {
    VI freq(vec.size(), 1);
    return randomChoose(vec, freq);
}/// randomChoose

int randomChoose(const VI& vec, const VI& freq) {
    const int sum = accumulate(freq.begin(), freq.end(), 0);
    if (sum < 1) return -1;

    CIC__RAND_ENV(sum, res)

    int index = 0, prev_sum = 0;
    for (; index < vec.size(); ++index) {
        prev_sum += freq[index];
        if (res < prev_sum) break;
    }
    return index;
}/// randomChoose

}/// namespace ChineseIdiomChain
