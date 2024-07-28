/// reader.cpp

#include "reader.h"
#include <jsoncpp/json/json.h>
#include <fstream>

namespace ChineseIdiomChain {

using std::ifstream;
using std::ios;

bool Reader::readData(const string& file, Data* data) {
  if (nullptr == data) {
    /// TODO
    // DEBUG_MSG();
    return false;
  }  

  ifstream in(file, ios::binary);
  if (!in.is_open()) {
    /// TODO
    // implement a simple log manager
    // DEBUG_MSG();
    /// cout << "Error opening " << file << "!\n";
    return false;
  }
  Json::Reader reader;
  Json::Value root;
  if (!reader.parse(in, root)) {
    /// TODO
    /// cout << "Error parse " << file << "!\n";
    return false;
  }

  for (const auto& obj : root) {
    data->data_.emplace_back(obj["word"].asString());
  }
  //INFO_MSG("readData succeed!");
  return true;
}/// Reader::readData

}/// namespace ChineseIdiomChain


