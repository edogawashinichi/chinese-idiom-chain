/// solver_gene.h

/// derived class from class Solver, using genetic method

#pragma once

#include "solver.h"
#include "population.h"
#include "pool_forward.h"
#include "pool_backward.h"
#include "common_notation.h"

namespace ChineseIdiomChain {

class SolverGene : public Solver {
public:
  SolverGene(const string& mapper_file, const string& graph_file);

public:
  virtual void run() override;
protected:
  void runOnce();
  void memoBiDFS(LI& path, VI& visited);
  bool decideDirection(const bool forward_empty, const bool backward_empty) const;
  void forwardDFS(VI& successors, LI& path, VI& visited);
  void backwardDFS(VI& predecessors, LI& path, VI& visited);
  void memoForwardDFS(LI& path, VI& visited);
  void memoBackwardDFS(LI& path, VI& visited);
protected:
  int iter_num_;
  float recovery_ratio_;
  float search_ratio_;
  int extension_size_;
  int instant_ret_;
protected:
  int instantRet(const LI& path, const VI& visited);
public:
  void configIterNum(const int num);
  void configRecoveryRatio(const float ratio);
  void configSearchRatio(const float ratio);
  void configExtensionSize(const int size);

protected:
  unique_ptr<Population> seeds_;
  void loadSeeds();
  void cacheSeeds();
  void updateSeeds(const LI& path);
public:
  void configSeeds(const int capacity);

protected:
  unique_ptr<PoolForward> snippets_forward_;
  unique_ptr<PoolBackward> snippets_backward_;
  void loadSnippetsForward();
  void loadSnippetsBackward();
  void cacheSnippetsForward();
  void cacheSnippetsBackward();
  void updateSnippets(const LI& path);
public:
  void configSnippets(const int energy);
};/// class SolverGene

}/// namespace ChineseIdiomChain
