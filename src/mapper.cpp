/// mapper.cpp

#include "mapper.h"
#include "reader.h"

namespace ChineseIdiomChain {

Mapper::Mapper(const string& file) {
  Reader reader;
  reader.loadMapper(file, this);
}

}/// namespace ChineseIdiomChain

