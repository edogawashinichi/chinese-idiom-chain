/// population.cpp

#include "population.h"
#include "reader.h"
#include "writer.h"

namespace ChineseIdiomChain {

void Population::init() {
  #ifdef CIC__DEBUG_INFO
    STR_L("Population::init")
    STR_VAR_L(capacity_)
  #endif
  if (capacity_ <= 0) return;
  for(auto& ptr : communities_) {
    #ifdef CIC__DEBUG_INFO
      STR_L("release communities_ manually")
    #endif
    ptr = nullptr;/// release memory manually
  }
  communities_.reserve(capacity_);
  #ifdef CIC__DEBUG_INFO
    STR_L("reserve ok")
  #endif
  for (int i = 0; i < capacity_; ++i) {
    communities_.emplace_back(std::move(make_unique<LI>()));
    #ifdef CIC__DEBUG_INFO
      STR_L("communities_ make unique ok")
    #endif
  }
  #ifdef CIC__DEBUG_INFO
    STR_L("Population::init ok")
  #endif
}/// Population::init

void Population::load(const string& dir) {
  Reader reader;
  for (int i = 0; i < capacity_; ++i) {
    const string file(dir + to_string(i) + ".json");
    reader.loadSeed(file, communities_[i].get());
  }
}/// Population::load

void Population::cache(const string& dir) {
  Writer writer;
  for (int i = 0; i < capacity_; ++i) {
    const string file(dir + to_string(i) + ".json");
    writer.cacheSeed(*(communities_[i]), file);
  }
}/// Population::cache

}/// namespace ChineseIdiomChain
