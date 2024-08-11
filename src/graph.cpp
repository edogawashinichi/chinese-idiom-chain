/// graph.cpp

#include "graph.h"
#include "reader.h"

#include <algorithm>

#define CIC__FUNC_GET_UNVISITED(Some, some) \
void Graph::getUnvisited##Some(const int vertex, const VI& visited, VI* some) const {\
  if (! some##_.count(vertex)) return;\
  for (const auto v : some##_.at(vertex)) {\
    if (visited[v]) continue;\
    some->emplace_back(v);\
  }\
}

namespace ChineseIdiomChain {

Graph::Graph(const string& file) {
  Reader reader;
  reader.loadGraph(file, this);/// need to thow an error if failed
}/// Graph::Graph

int Graph::maxVertex() const {
  return *(std::max_element(vertices_.begin(), vertices_.end())); 
}/// Graph::maxVertexCode

CIC__FUNC_GET_UNVISITED(Successors, successors)
CIC__FUNC_GET_UNVISITED(Predecessors, predecessors)

void Graph::show() const {
  cout << "graph:\n";
  cout << "vertices size: " << vertices_.size() << "\n";
  cout << "predecessors size: " << predecessors_.size() << "\n";
  cout << "successors size: " << successors_.size() << "\n";
}/// Graph::show

}/// namespace ChineseIdiomChain
