/// pool.cpp

#include "pool.h"
#include "writer.h"
#include "reader.h"

namespace ChineseIdiomChain {

void Pool::cache(const string& file) {
  Writer writer;
  writer.cacheSnippets(end2path_, file);
}/// Pool::cache

}/// namespace ChineseIdiomChain
