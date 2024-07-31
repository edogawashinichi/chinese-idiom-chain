/// filter.cpp

#include "filter.h"

namespace ChineseIdiomChain {

MSI Filter::idiom2Code(const Mapper& mapper, const int mode) {
  MSI res;
  if (0 == mode) {
  } else if (1 == mode) { /// mode 1: length four
    for (const auto& kv : mapper.idiom2code_) {
      if (kv.first.size() != CHINESE_UTF8_BYTES * MODE_1_IDIOM_NUM) continue;
      res.insert(kv);
    }
  } else if (2 == mode) {
  } else if (3 == mode) {
  }
  return res;
}

MIS Filter::code2Idiom(const Mapper& mapper, const int mode) {
  MIS res;
  if (0 == mode) {
  } else if (1 == mode) {
    for (const auto& kv : mapper.code2idiom_) {
      if (kv.second.size() != CHINESE_UTF8_BYTES * MODE_1_IDIOM_NUM) continue;
      res.insert(kv);
    }
  } else if (2 == mode) {
  } else if (3 == mode) {
  }
  return res;
}

}/// namespace ChineseIdiomChain
