/// path.cpp

#include "path.h"

namespace ChineseIdiomChain {

Path::Path(const LI& list) : vertices_(list) {
}/// Path::Path

void Path::assign(const LI& list) {
  vertices_ = list;
}/// Path::assign

void Path::show(const Mapper& mapper) const {
  for (const auto vertex : vertices_) {
    cout << mapper.code2idiom_.at(vertex) << "  ";
  }
  cout << "\nsize: " << vertices_.size() << "\n";
}/// Path::show

}/// namespace ChineseIdiomChain
