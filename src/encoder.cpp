/// encoder.cpp

#include "encoder.h"

namespace ChineseIdiomChain {

bool Encoder::encodeData(const Data& data, Mapper* mapper) {
  if (nullptr == mapper) {
    /// TODO
    return false;
  }

  for (int i = 0; i < data.idioms_.size(); ++i) {
    const auto& idiom = (data.idioms_)[i];
    const int code = encode(idiom, i);
    (mapper->idiom2code_)[idiom] = code;
    (mapper->code2idiom_)[code] = idiom;
  }
  
  /// TODO
  return true;
}/// Encoder::encodeData

int Encoder::encode(const string& s, const int i) {
  return i;
}/// Encoder::encode

}/// namespace ChineseIdiomChain
