/// reader.h

/// file ----reader----> data

#pragma once

#include "data.h"
#include <string>

namespace ChineseIdiomChain {

using std::string;

class Reader {
public:
  bool readData(const string& file, Data* data);
};

}/// namespace ChineseIdiomChain
