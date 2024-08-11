/// common_math.cpp

#include "common_math.h"

#include <functional> /// fix std::generate problem only for C++17 
#include <numeric>
#include <random>

#define CIC__RAND_ENV(rng) \
std::random_device rd;\
std::mt19937 rng(rd());

#define CIC__DISTR_ENV(sum, res) \
CIC__RAND_ENV(rng)\
std::uniform_int_distribution<int> distr(0, sum - 1);\
const int res = distr(rng);

namespace ChineseIdiomChain {

using std::generate;
using std::transform;

void split16bits(const short bits16, char& high8, char& low8) {
  high8 = static_cast<char>(bits16 >> 8);
  low8 = static_cast<char>(bits16 & 0x00FF);
}/// split16bits

short composite16bits(const char high8, const char low8) {
  short bits16 = high8;
  bits16 = (bits16 << 8);
  bits16 |= (static_cast<short>(low8) & 0x00FF);
  return bits16;
}/// composite16bits

bool isEqual(const VI& u, const VI& v) {
  /*if (u.size() != v.size()) return false;
  for (int i = 0; i < u.size(); ++i) {
    if (u[i] != v[i]) return false;
  }
  return true;*/
  return u == v;
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

int randomChoose(const int n) {
  CIC__DISTR_ENV(n, res)
  return res;
}

int randomChoose(const VI& vec) {
  VI freq(vec.size(), 1);
  return randomChoose(vec, freq);
}/// randomChoose

PII randomChooseSub(const VI& vec) {
  const int sum = vec.size() * vec.size();
  CIC__DISTR_ENV(sum, res)
  const int a = res / vec.size();
  const int b = res % vec.size();
  if (a < b) return PII({a, b});
  return PII({b, a});
}/// randomChooseSub

int randomChoose(const VI& vec, const int min_index, const int max_index) {
  VI freq(vec.size(), 1);
  return randomChoose(vec, freq, min_index, max_index);
}/// randomChoose

int randomChoose(const VI& vec, const VI& freq) {
  return randomChoose(vec, freq, 0, vec.size() - 1);
}/// randomChoose

int randomChoose(const VI& vec, const VI& freq, const int min_index, const int max_index) {
  const int sum = accumulate(freq.begin() + min_index, freq.begin() + max_index + 1, 0);
  if (sum < 1) return -1;

  CIC__DISTR_ENV(sum, res)

  int index = min_index, prev_sum = 0;
  for (; index <= max_index; ++index) {
    prev_sum += freq[index];
    if (res < prev_sum) break;
  }
  return index;
}/// randomChoose

void shuffle(VI& v) {
  CIC__RAND_ENV(rng)
  shuffle(v.begin(), v.end(), rng);
}/// shuffle

void inverse(VI& v) {
  const int max_val = *(max_element(v.begin(), v.end()));
  const int min_val = *(min_element(v.begin(), v.end()));
  transform(v.begin(), v.end(), v.begin(), [&](const int i){ return max_val + min_val - i; });
}/// inverse

void sharpen(VI& v) {
  const int max_val = *(max_element(v.begin(), v.end()));
  transform(v.begin(), v.end(), v.begin(), [&](const int i){ return static_cast<int>(static_cast<float>(i) * i / max_val + 1); });
}/// sharpen

void inverseSharpen(VI& v) {
  const int max_val = *(max_element(v.begin(), v.end()));
  const int min_val = *(min_element(v.begin(), v.end()));
  transform(v.begin(), v.end(), v.begin(), [&](const int i){ const float j = max_val + min_val - i; return static_cast<int>(j * j / min_val + 1); });
}/// inverseSharpen

bool bet(const float probability) {
  const int N = 10000;
  const int f0 = N * probability;
  const int f1 = N - f0;
  return 0 == randomChoose({0, 1}, {f0, f1});
}/// bet

bool sharpenBet(const int x, const int y) {
  return 0 == randomChoose({0, 1}, {x, static_cast<int>(static_cast<float>(y) * y / x)});
}/// bet

}/// namespace ChineseIdiomChain
