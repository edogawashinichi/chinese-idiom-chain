/// writer.cpp

#include "writer.h"

#include <fstream>
#include <jsoncpp/json/json.h>

namespace ChineseIdiomChain {

using std::ofstream;

bool Writer::writeMapper(const Mapper& mapper, const string& file) {
  ofstream out(file);
  if (!out.is_open()) {
    /// TODO
    cout << "open " << file << " FAILED!\n";
    return false;
  }
  
  out.close();
  return true;
}/// Writer::writeMapper

bool Writer::writeGraph(const Graph& graph, const string& file) {
  return true;
}/// Writer::writeGraph

}/// namespace ChineseIdiomChain
