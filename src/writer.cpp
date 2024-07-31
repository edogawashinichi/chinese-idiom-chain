/// writer.cpp

#include "writer.h"

namespace ChineseIdiomChain {

bool Writer::cacheMapper(const Mapper& mapper, const string& file) {
  CIC__WRITE_JSON_START

  for (const auto& kv : mapper.idiom2code_) {
    Json::Value obj;
    obj["idiom"] = Json::Value(kv.first);
    obj["code"] = Json::Value(kv.second);
    root.append(obj);
  }

  CIC__WRITE_JSON_END
}/// Writer::writeMapper

bool Writer::cacheGraph(const Graph& graph, const string& file) {
  CIC__WRITE_JSON_START

  Json::Value vertices;
  for (const auto vertex : graph.vertices_) {
    vertices.append(Json::Value(vertex));
  }
  root["vertices"] = vertices;

  Json::Value predecessors;
  for (const auto& kv : graph.predecessors_) {
    Json::Value obj;
    obj["cur"] = Json::Value(kv.first);
    Json::Value pres;
    for (const auto p : kv.second) {
      pres.append(Json::Value(p));
    }
    obj["pres"] = pres;
    predecessors.append(obj);
  }
  root["predecessors"] = predecessors;

  CIC__WRITE_JSON_END
}/// Writer::writeGraph

}/// namespace ChineseIdiomChain
