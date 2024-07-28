/// mapper.h

/// use mapper to represent the encoded data

#pragma once

#include <unordered_map>
#include <string>

namespace ChineseIdiomChain {

using std::unordered_map;
using std::string;
using std::pair;

using MSI = unordered_map<string, int>;
using MIS = unordered_map<int, string>;
using PIS = pair<int, string>;

class Mapper {
public:
  MSI idiom2code_;
  MIS code2idiom_;
};/// class Mapper

}/// namespace ChineseIdiomChain
