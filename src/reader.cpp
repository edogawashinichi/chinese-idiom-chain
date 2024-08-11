/// reader.cpp

#include "reader.h"
#include "solver_naive.h"
#include "solver_gene.h"
#include "common_math.h"

#define CIC__GET_END2PATH(in, c, some) \
char d;\
in.get(d);\
const short size16 = composite16bits(c, d);\
cout << "c: " << static_cast<int>(c) << "\n";\
cout << "d: " << static_cast<int>(d) << "\n";\
cout << "size16: " << size16 << "\n";\
VI path;\
path.reserve(size16);\
for (int i = 0; i < size16; ++i) {\
  in.get(c);\
  in.get(d);\
  const short vertex16 = composite16bits(c, d);\
  path.emplace_back(vertex16);\
}\
const int end = path.some();\
end2path->insert({end, path});

namespace ChineseIdiomChain {

bool Reader::readData(const string& file, Data* data) {
  CIC__READ_JSON_START(file, data, in, root)

  for (const auto& obj : root) {
    data->idioms_.emplace_back(obj["word"].asString());
  }

  CIC__READ_JSON_END(in)
}/// Reader::readData

bool Reader::loadMapper(const string& file, Mapper* mapper) {
  CIC__READ_JSON_START(file, mapper, in, root)
  
  for (const auto& obj : root) {
    const string& idiom(obj["idiom"].asString());
    const int code = obj["code"].asInt();
    (mapper->idiom2code_)[idiom] = code;
    (mapper->code2idiom_)[code] = idiom;
  }

  CIC__READ_JSON_END(in)
}/// Reader::loadMapper

bool Reader::loadGraph(const string& file, Graph* graph) {
  CIC__READ_JSON_START(file, graph, in, root)
  
  (graph->vertices_).clear();
  #ifdef CIC__DEBUG_INFO
    const int vertex_size = root["vertices"].size();
    STR_VAR_L(vertex_size)
  #endif
  (graph->vertices_).reserve(root["vertices"].size());
  for (const auto& vertex : root["vertices"]) {
    (graph->vertices_).push_back(vertex.asInt());
  }

  (graph->predecessors_).clear();
  (graph->successors_).clear();
  for (const auto& obj : root["predecessors"]) {
    const int cur = obj["cur"].asInt();
    #ifdef CIC__DEBUG_INFO
      const int pres_size = obj["pres"].size();
      STR_VAR_L(pres_size)
    #endif
    (graph->predecessors_)[cur].reserve(obj["pres"].size());
    for (const auto& pre : obj["pres"]) {
      const int p = pre.asInt();
      (graph->predecessors_)[cur].push_back(p);
      (graph->successors_)[p].push_back(cur);
    }
  }

  CIC__READ_JSON_END(in)
}/// Reader::loadGraph

bool Reader::readConfig(const string& file, Solver* solver) {
  CIC__READ_JSON_START(file, solver, in, root)

  if (typeid(*solver) == typeid(SolverNaive)) {
    SolverNaive* derived = dynamic_cast<SolverNaive*>(solver);
    derived->setIterNum(root["solver_naive_iter_num"].asInt());
  } else if (typeid(*solver) == typeid(SolverGene)) {
    SolverGene* derived = dynamic_cast<SolverGene*>(solver);
    derived->configIterNum(root["solver_gene_iter_num"].asInt());
    derived->configSeeds(root["solver_gene_seeds_capacity"].asInt());
    derived->configRecoveryRatio(root["solver_gene_recovery_ratio"].asFloat());
    derived->configSearchRatio(root["solver_gene_search_ratio"].asFloat());
    derived->configExtensionSize(root["solver_gene_extension_size"].asInt());
    derived->configSnippets(root["solver_gene_snippets_energy"].asInt());
  }
  
  CIC__READ_JSON_END(in)
}/// Reader::readerConfig

bool Reader::loadSolution(const string& file, const Mapper& mapper, Path* path) {
  CIC__READ_JSON_START(file, path, in, root)

  for (const auto& obj : root["chain"]) {
    const int vertex = mapper.idiom2code_.at(obj.asString());
    path->extendBack(vertex);
  }

  CIC__READ_JSON_END(in)
}/// Reader::loadSolution

bool Reader::loadSeed(const string& file, LI* community) {
  CIC__READ_JSON_START(file, community, in, root)

  for (const auto& obj : root["chain"]) {
    const int vertex = obj.asInt();
    community->emplace_back(vertex);
  }

  CIC__READ_JSON_END(in)
}/// Reader::loadSeed

bool Reader::loadSnippetsForward(const string& file, MIVI* end2path) {
  CIC__READ_BIN_START(file, in)

  #ifdef CIC__DEBUG_INFO
    STR_L("start loadSnippetsForward")
  #endif

  char c;
  while (in.get(c)) {
    CIC__GET_END2PATH(in, c, front)
  }/// while

  #ifdef CIC__DEBUG_INFO
    STR_L("finish loadSnippetsForward")
  #endif

  CIC__READ_BIN_END(in)
}/// Reader::loadSnippetsForward

bool Reader::loadSnippetsBackward(const string& file, MIVI* end2path) {
  CIC__READ_BIN_START(file, in)

  char c;
  while (in.get(c)) {
    CIC__GET_END2PATH(in, c, back)
  }/// while

  CIC__READ_BIN_END(in)
}/// Reader::loadSnippetsBackward

}/// namespace ChineseIdiomChain
