/// common_math.h

#pragma once

#include <vector>

namespace ChineseIdiomChain {

using std::vector;

vector<int> linearVec(const int n, const int k, const int b);
vector<int> idVec(const int n, const int start_val);
vector<int> idVec(const int n);

}/// namespace ChineseIdiomChain
