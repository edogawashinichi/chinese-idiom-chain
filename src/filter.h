/// filter.h

/// filter a mapper of some mode to obtain its subset

#pragma once

#include "Mapper.h"

namespace ChineseIdiomChain {

class Filter {
public:
  MSI idiom2Code(const Mapper& mapper, const int mode);
  MIS code2Idiom(const Mapper& mapper, const int mode);
};/// class Filter

}/// namespace ChineseIdiomChain
