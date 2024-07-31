/// mapper.h

/// use mapper to represent the encoded data

#pragma once

#include "common_notation.h"

namespace ChineseIdiomChain {

class Mapper {
public:
  MSI idiom2code_;
  MIS code2idiom_;
public:
  Mapper() = default;
  Mapper(const string& file);
};/// class Mapper

}/// namespace ChineseIdiomChain
