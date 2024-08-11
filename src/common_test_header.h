/// common_test_header.h

#pragma once

#include "common_const.h"
#include "common_notation.h"
#include "common_math.h"

#include "reader.h"
#include "data.h"
#include "encoder.h"
#include "mapper.h"
#include "filter.h"
#include "builder.h"
#include "graph.h"
#include "writer.h"
#include "solver.h"
#include "solver_naive.h"
#include "solver_gene.h"

using ChineseIdiomChain::Reader;
using ChineseIdiomChain::Data;
using ChineseIdiomChain::Encoder;
using ChineseIdiomChain::Mapper;
using ChineseIdiomChain::Filter;
using ChineseIdiomChain::Builder;
using ChineseIdiomChain::Graph;
using ChineseIdiomChain::Writer;
using ChineseIdiomChain::Solver;
using ChineseIdiomChain::SolverNaive;
using ChineseIdiomChain::SolverGene;

using ChineseIdiomChain::DATA_FILE;
using ChineseIdiomChain::MAPPER_FILE;
using ChineseIdiomChain::GRAPH_FILE;

using ChineseIdiomChain::isEqual;
using ChineseIdiomChain::linearVec;
using ChineseIdiomChain::idVec;
using ChineseIdiomChain::randomChoose;
using ChineseIdiomChain::split16bits;
using ChineseIdiomChain::composite16bits;
