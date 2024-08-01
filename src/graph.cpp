/// graph.cpp

#include "graph.h"
#include "reader.h"

#include <algorithm>

namespace ChineseIdiomChain {

Graph::Graph(const string& file) {
  Reader reader;
  reader.loadGraph(file, this);
}/// Graph::Graph

int Graph::maxVertex() const {
  return *(std::max_element(vertices_.begin(), vertices_.end())); 
}/// Graph::maxVertexCode

void Graph::show() const {
  cout << "graph:\n";
  cout << "vertices size: " << vertices_.size() << "\n";
  cout << "predecessors size: " << predecessors_.size() << "\n";
  cout << "successors size: " << successors_.size() << "\n";
}/// Graph::show

}/// namespace ChineseIdiomChain
