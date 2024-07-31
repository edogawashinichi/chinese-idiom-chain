/// encoder.h

/// data ----encoder----> mapper

#pragma once

#include "common_notation.h"
#include "data.h"
#include "mapper.h"

namespace ChineseIdiomChain {

class Encoder {
public:
  bool encodeData(const Data& data, Mapper* mapper);
protected:
  int encode(const string& s, const int i);
};/// class Encoder

}/// namespace ChineseIdiomChain
