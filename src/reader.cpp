/// reader.cpp

#include "reader.h"

namespace ChineseIdiomChain {

bool Reader::readData(const string& file, Data* data) {
  CIC__READ_JSON_START(data)

  for (const auto& obj : root) {
    data->idioms_.emplace_back(obj["word"].asString());
  }

  CIC__READ_JSON_END
}/// Reader::readData

bool Reader::loadMapper(const string& file, Mapper* mapper) {
  CIC__READ_JSON_START(mapper)
  
  for (const auto& obj : root) {
    const string& idiom(obj["idiom"].asString());
    const int code = obj["code"].asInt();
    (mapper->idiom2code_)[idiom] = code;
    (mapper->code2idiom_)[code] = idiom;
  }

  CIC__READ_JSON_END
}/// Reader::loadMapper

bool Reader::loadGraph(const string& file, Graph* graph) {
  CIC__READ_JSON_START(graph)
  
  (graph->vertices_).clear();
  (graph->vertices_).reserve(root["vertices"].size());
  for (const auto& vertex : root["vertices"]) {
    (graph->vertices_).push_back(vertex.asInt());
  }

  (graph->predecessors_).clear();
  (graph->successors_).clear();
  for (const auto& obj : root["predecessors"]) {
    const int cur = obj["cur"].asInt();
    (graph->predecessors_)[cur].reserve(obj["pres"].size());
    for (const auto& pre : obj["pres"]) {
      const int p = pre.asInt();
      (graph->predecessors_)[cur].push_back(p);
      (graph->successors_)[p].push_back(cur);
    }
  }

  CIC__READ_JSON_END
}/// Reader::loadGraph

}/// namespace ChineseIdiomChain
