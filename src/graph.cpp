/// graph.cpp

#include "graph.h"
#include "reader.h"

namespace ChineseIdiomChain {

Graph::Graph(const string& file) {
  Reader reader;
  reader.loadGraph(file, this);
}/// Graph::Graph

void Graph::show() const {
  
}/// Graph::show

}/// namespace ChineseIdiomChain
