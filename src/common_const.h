/// common_const.h

#pragma once

#include <string>

namespace ChineseIdiomChain {

using std::string;

const string DATA_DIR("../data/");
const string INPUT_DIR("../data/input/");
const string CACHE_DIR("../data/cache/");
const string OUTPUT_DIR("../data/output/");
const string DATA_FILE("../data/input/data.json");
const string CONFIG_FILE("../data/input/config.json");
const string MAPPER_FILE("../data/cache/mapper.json");
const string GRAPH_FILE("../data/cache/graph.json");
const string SEEDS_DIR("../data/cache/seeds/");
const string SNIPPETS_FORWARD_FILE("../data/cache/snippets/forward.bin");
const string SNIPPETS_BACKWARD_FILE("../data/cache/snippets/backward.bin");
const string SOLUTION_FILE("../data/output/solution.json");

constexpr int CHINESE_UTF8_BYTES = 3;
constexpr int MODE_1_IDIOM_NUM = 4;

}/// namespace ChineseIdiomChain
