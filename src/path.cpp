/// path.cpp

#include "path.h"

namespace ChineseIdiomChain {

Path::Path(const VI& vec) : codes_(vec) {
}

void Path::assign(const VI& vec) {
  codes_ = vec;
}/// Path::assign

void Path::show(const Mapper& mapper) const {
  for (const auto code : codes_) {
    cout << mapper.code2idiom_.at(code) << "  ";
  }
  cout << "\nsize: " << codes_.size() << "\n";
}/// Path::show

}/// namespace ChineseIdiomChain
