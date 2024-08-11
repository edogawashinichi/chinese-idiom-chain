/// writer.cpp

#include "writer.h"
#include "common_math.h"

namespace ChineseIdiomChain {

bool Writer::cacheMapper(const Mapper& mapper, const string& file) {
  CIC__WRITE_JSON_START(file, out, root)

  for (const auto& kv : mapper.idiom2code_) {
    Json::Value obj;
    obj["idiom"] = Json::Value(kv.first);
    obj["code"] = Json::Value(kv.second);
    root.append(obj);
  }

  CIC__WRITE_JSON_END(out, root)
}/// Writer::writeMapper

bool Writer::cacheGraph(const Graph& graph, const string& file) {
  CIC__WRITE_JSON_START(file, out, root)

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

  CIC__WRITE_JSON_END(out, root)
}/// Writer::writeGraph

bool Writer::writeSolution(const Path& path, const Mapper& mapper, const string& file) {
  CIC__WRITE_JSON_START(file, out, root)

  root["size"] = Json::Value(path.size());
  Json::Value chain;
  for (const auto vertex : path.vertices_) {
    const string idiom(mapper.code2idiom_.at(vertex));
    chain.append(Json::Value(idiom));
  }
  root["chain"] = chain;

  CIC__WRITE_JSON_END(out, root)
}/// Writer::writeSolution

bool Writer::cacheSeed(const LI& community, const string& file) {
  CIC__WRITE_JSON_START(file, out, root)

  Json::Value chain;
  for (const auto vertex : community) {
    chain.append(Json::Value(vertex));
  }
  root["chain"] = chain;

  CIC__WRITE_JSON_END(out, root)
}/// Writer::cacheSeed

bool Writer::cacheSnippets(const MIVI& end2path, const string& file) {
  CIC__WRITE_BIN_START(file, out)

  char high8, low8;
  for (const auto& iter : end2path) {
    const short size16 = static_cast<short>(iter.second.size());
    split16bits(size16, high8, low8);
    out.put(high8);
    out.put(low8);
    for (const auto vertex : iter.second) {
      const short vertex16 = static_cast<short>(vertex);
      split16bits(vertex16, high8, low8);
      out.put(high8);
      out.put(low8);
    }/// for second
  }/// for end2path

  CIC__WRITE_BIN_END(out)
}/// Writer::cacheSnippets

}/// namespace ChineseIdiomChain
