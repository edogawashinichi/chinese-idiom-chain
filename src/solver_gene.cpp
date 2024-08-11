/// solver_gene.cpp

#include "solver_gene.h"
#include "common_const.h"
#include "common_math.h"
#include <algorithm>

#define CIC__FUNC_SNIPPETS(op, Some, some, SOME) \
void SolverGene::op##Snippets##Some() {\
  snippets_##some##_->op(SNIPPETS_##SOME##_FILE);\
}

namespace ChineseIdiomChain {

SolverGene::SolverGene(const string& mapper_file, const string& graph_file) :
Solver(mapper_file, graph_file), seeds_(nullptr), snippets_forward_(nullptr), snippets_backward_(nullptr) {
  seeds_ = make_unique<Population>();
  snippets_forward_ = make_unique<PoolForward>();
  snippets_backward_ = make_unique<PoolBackward>();
  this->readConfig();/// derived ptr can penetrate to base function
  #ifdef CIC__DEBUG_INFO
    STR_L("readConfig ok")
  #endif
  loadSeeds();
  #ifdef CIC__DEBUG_INFO
    STR_L("loadSeeds ok")
  #endif
  loadSnippetsForward();
  #ifdef CIC__DEBUG_INFO
    STR_L("loadSnippetsForward ok")
  #endif
  loadSnippetsBackward();
  #ifdef CIC__DEBUG_INFO
    STR_L("SolverGene::SolverGene ok")
  #endif
}/// SolverGene::SolverGene

void SolverGene::run() {
  for (int t = 0; t < iter_num_; ++t) {
    STR_VAR_2_L(t, best_path_.size());
    runOnce();
    showSolution();
    writeSolution();
  }
}/// SolverGene::run

void SolverGene::runOnce() {

  /// candidates: seeds_[0...capacity-1], LI(random_start)
  /// random candidate with random clip
  /// memoBiDFS(candidate)

  #ifdef CIC__DEBUG_INFO
    STR_L("start runOnce")
  #endif

  LI path;
  VI visited(graph_->maxVertex() + 1, 0);
  #ifdef CIC__DEBUG_INFO
    STR_L("graph_ ok")
  #endif
  const int C = seeds_->capacity_ + 1;
    STR_L("seeds_ ok")
  const int index = randomChoose(idVec(C));
  if (index != C - 1) {
    #ifdef CIC__DEBUG_INFO
      STR_VAR_L(visited.size())
      STR_VAR_L(C)
      STR_VAR_L(index)
    #endif
    const int sz = (seeds_->communities_)[index]->size();
    if (sz != 0) {
      #ifdef CIC__DEBUG_INFO
        STR_VAR_L(sz)
      #endif
      const auto pair = randomChooseSub(idVec(sz));
      #ifdef CIC__DEBUG_INFO
        STR_VAR_L(pair.first)
        STR_VAR_L(pair.second)
      #endif
      LI::iterator it_start = (seeds_->communities_)[index]->begin();
      std::advance(it_start, pair.first);
      LI::iterator it_end = (seeds_->communities_)[index]->begin();
      std::advance(it_end, pair.second + 1);
      path.splice(path.begin(), *((seeds_->communities_)[index]), it_start, it_end);
      for (const auto vertex : path) {
        visited[vertex] = 1;
      }/// for path
      #ifdef CIC__DEBUG_INFO
        STR_VAR_L(path.size())
      #endif
    }/// if sz != 0
  }/// if index != C - 1

  if (path.size() == 0) {
    #ifdef CIC__DEBUG_INFO
      STR_L("path size 0")
    #endif
    const int index = randomChoose(graph_->order());/// order: vertex size; size: edge size
    #ifdef CIC__DEBUG_INFO
      STR_VAR_L(index)
    #endif
    const int vertex = (graph_->vertices_)[index];
    #ifdef CIC__DEBUG_INFO
      STR_VAR_L(vertex)
    #endif
    path.emplace_back(vertex);
    visited[vertex] = 1;
  }

  #ifdef CIC__DEBUG_INFO
    STR_VAR_L(path.front());
  #endif

  memoBiDFS(path, visited);
  #ifdef CIC__DEBUG_INFO
    STR_L("runOnce finish memoBiDFS")
  #endif
  
  cacheSeeds();
  #ifdef CIC__DEBUG_INFO
    STR_L("runOnce finish cacheSeeds")
  #endif
  cacheSnippetsForward();
  #ifdef CIC__DEBUG_INFO
    STR_L("runOnce finish cacheSnippetsForward")
  #endif
  cacheSnippetsBackward(); 

  #ifdef CIC__DEBUG_INFO
    STR_L("finish runOne")
  #endif
}/// SolverGene::runOnce

void SolverGene::memoBiDFS(LI& path, VI& visited) {
  /// condition -> immediately return from recursive stack
  #ifdef CIC__DEBUG_INFO
    STR_L("start memoBiDFS")
  #endif

  #ifdef CIC__DEBUG_INFO
    const int visited_cnt = std::count(visited.begin(), visited.end(), 1);
    STR_VAR_2_L(path.size(), visited_cnt)
  #endif

  updateSolution(path);
  #ifdef CIC__DEBUG_INFO
    STR_L("updateSolution ok")
  #endif
  updateSeeds(path);
  #ifdef CIC__DEBUG_INFO
    STR_L("updateSeeds ok")
  #endif
  updateSnippets(path);
  #ifdef CIC__DEBUG_INFO
    STR_L("updateSnippets ok")
  #endif

  VI unvisitedPredecessors;
  graph_->getUnvisitedPredecessors(path.front(), visited, &unvisitedPredecessors);
  #ifdef CIC__DEBUG_INFO
    STR_L("graph get unvisited predecessors ok")
  #endif
  VI unvisitedSuccessors;
  graph_->getUnvisitedSuccessors(path.back(), visited, &unvisitedSuccessors);
  #ifdef CIC__DEBUG_INFO
    STR_L("graph get unvisited successors ok")
  #endif
  if (unvisitedPredecessors.empty() && unvisitedSuccessors.empty()) {
    #ifdef CIC__DEBUG_INFO
      STR_L("both empty ret!")
    #endif
    return;
  }

  bool ward = decideDirection(unvisitedSuccessors.empty(), unvisitedPredecessors.empty());
  #ifdef CIC__DEBUG_INFO
    STR_L("decideDirection ok")
    STR_VAR_L(ward)
  #endif

  /// TODO: consider class Searcher
  if (ward) {/// forward
    if (!bet(search_ratio_)) {
      memoForwardDFS(path, visited);
      #ifdef CIC__DEBUG_INFO
        STR_L("after memoForwardDFS")
      #endif
    }
    forwardDFS(unvisitedSuccessors, path, visited);
  } else {/// backward
    if (!bet(search_ratio_)) {
      memoBackwardDFS(path, visited);
      #ifdef CIC__DEBUG_INFO
        STR_L("after memoBackwardDFS")
      #endif
    }
    backwardDFS(unvisitedPredecessors, path, visited);
  }/// else backward
  #ifdef CIC__DEBUG_INFO
    STR_L("finish memoBiDFS")
    const int finish_memoBiDFS_cnt = std::count(visited.begin(), visited.end(), 1);
    STR_VAR_2_L(path.size(), finish_memoBiDFS_cnt)
  #endif
}/// SolverGene::memoBiDFS

bool SolverGene::decideDirection(const bool forward_empty, const bool backward_empty) const {
  /// true - forward
  /// false - backward
  if (backward_empty) {
    return true;
  } else if (forward_empty) {
    return false;
  } else {
    return bet(0.5f);
  }
}/// SolverGene::decideDirection

void SolverGene::memoForwardDFS(LI& path, VI& visited) {
  #ifdef CIC__DEBUG_INFO
    STR_L("start memoForwardDFS")
  #endif
  const int back = path.back();
  if (false == (snippets_forward_->end2path_).count(back)) return;
  const auto& memo = (snippets_forward_->end2path_).at(back);
  const int max_unique_index = Path(path).getForwardMaxUniqueIndex(memo, visited);
  if (max_unique_index < extension_size_) return;
  const int index = randomChoose(memo, extension_size_, max_unique_index);
  for (int i = 1; i <= index; ++i) {
    const int vertex = memo[i];
    path.emplace_back(vertex);
    visited[vertex] = 1;
  }
  memoBiDFS(path, visited);
  for (int i = 1; i <= index; ++i) {
    path.pop_back();
    visited[memo[i]] = 0;
  }
  #ifdef CIC__DEBUG_INFO
    STR_L("finish memoForwardDFS")
    const int visited_cnt = std::count(visited.begin(), visited.end(), 1);
    STR_VAR_2_L(path.size(), visited_cnt)
  #endif
}/// SolverGene::memoForwardDFS
void SolverGene::memoBackwardDFS(LI& path, VI& visited) {
  #ifdef CIC__DEBUG_INFO
    STR_L("start memoBackwardDFS")
  #endif
  const int front = path.front();
  if (false == (snippets_backward_->end2path_).count(front)) return;
  const auto& memo = (snippets_backward_->end2path_).at(front);
  const int min_unique_index = Path(path).getBackwardMinUniqueIndex(memo, visited);
  const int max_extension_size = memo.size() - 1 - min_unique_index;
  if (max_extension_size < extension_size_) return;
  const int index = randomChoose(memo, min_unique_index, memo.size() - 2);
  for (int i = memo.size() - 2; i >= index; --i) {
    const int vertex = memo[i];
    path.emplace_front(vertex);
    visited[vertex] = 1;
  }
  memoBiDFS(path, visited);
  for (int i = memo.size() - 2; i >= index; --i) {
    path.pop_back();
    visited[memo[i]] = 0;
  }
  #ifdef CIC__DEBUG_INFO
    STR_L("finish memoBackwardDFS")
    const int visited_cnt = std::count(visited.begin(), visited.end(), 1);
    STR_VAR_2_L(path.size(), visited_cnt)
  #endif
}/// SolverGene::memoBackwardDFS

void SolverGene::forwardDFS(VI& successors, LI& path, VI& visited) {
  #ifdef CIC__DEBUG_INFO
    STR_L("start forwardDFS")
  #endif
  shuffle(successors);
  for (const auto succ : successors) {
    #ifdef CIC__DEBUG_INFO
      STR_L("start forwardDFS for successors")
      STR_VAR_L(succ)
    #endif
    if (visited[succ]) continue;/// shall check visited due to recovery_ratio_
    #ifdef CIC__DEBUG_INFO
      STR_L("not continue")
    #endif
    path.emplace_back(succ);
    visited[succ] = 1;
    memoBiDFS(path, visited);
    path.pop_back();
    if (bet(recovery_ratio_)) visited[succ] = 0;
    #ifdef CIC__DEBUG_INFO
      STR_L("finish forwardDFS for successors")
      STR_VAR_L(succ)
    #endif
  }/// for
  #ifdef CIC__DEBUG_INFO
    STR_L("finish forwardDFS")
  #endif
}/// SolverGene::forwardDFS
void SolverGene::backwardDFS(VI& predecessors, LI& path, VI& visited) {
  #ifdef CIC__DEBUG_INFO
    STR_L("start backwardDFS")
  #endif
  shuffle(predecessors);
  for (const auto pred : predecessors) {
    #ifdef CIC__DEBUG_INFO
      STR_L("start backwardDFS for predecessors")
      STR_VAR_L(pred)
    #endif
    if (visited[pred]) continue;
    #ifdef CIC__DEBUG_INFO
      STR_L("not continue")
    #endif
    path.emplace_front(pred);
    visited[pred] = 1;
    memoBiDFS(path, visited);
    path.pop_front();
    if (bet(recovery_ratio_)) visited[pred] = 0;
    #ifdef CIC__DEBUG_INFO
      STR_L("finish backwardDFS for predecessors")
      STR_VAR_L(pred)
    #endif
  }/// for
  #ifdef CIC__DEBUG_INFO
    STR_L("finish backwardDFS")
  #endif
}/// SolverGene::backwardDFS

void SolverGene::loadSeeds() {
  seeds_->init();
  seeds_->load(SEEDS_DIR);
}/// SolverGene::loadSeeds

void SolverGene::configIterNum(const int num) {
  iter_num_ = num;
}/// SolverGene::configIterNum
void SolverGene::configSeeds(const int capacity) {
  seeds_->capacity_ = capacity;
}/// SolverGene::configSeeds
void SolverGene::configRecoveryRatio(const float ratio) {
  recovery_ratio_ = ratio;
}/// SolverGene::configRecoveryRatio
void SolverGene::configSearchRatio(const float ratio) {
  search_ratio_ = ratio;
}/// SolverGene::configSearchRatio
void SolverGene::configExtensionSize(const int size) {
  extension_size_ = size;
}/// SolverGene::configExtensionSize
void SolverGene::configSnippets(const int energy) {
  snippets_forward_->energy_ = energy;
  snippets_backward_->energy_ = energy;
}/// SolverGene::configSnippets

void SolverGene::cacheSeeds() {
  #ifdef CIC__DEBUG_INFO
    STR_L("start cacheSeeds")
  #endif
  seeds_->cache(SEEDS_DIR);
  #ifdef CIC__DEBUG_INFO
    STR_L("finish cacheSeeds")
  #endif
}/// SolverGene::cacheSeeds

CIC__FUNC_SNIPPETS(load, Forward, forward, FORWARD)
CIC__FUNC_SNIPPETS(load, Backward, backward, BACKWARD)
CIC__FUNC_SNIPPETS(cache, Forward, forward, FORWARD)
CIC__FUNC_SNIPPETS(cache, Backward, backward, BACKWARD)

void SolverGene::updateSeeds(const LI& path) {
  const int N = seeds_->capacity_;
  const VI vec(idVec(N));
  VI freq(N, 0);
  for (int i = 0; i < freq.size(); ++i) {
    freq[i] = (seeds_->communities_[i])->size() + 1;/// cannot transform unique_ptr
  }
  inverseSharpen(freq);
  const int index = randomChoose(vec, freq);
  *((seeds_->communities_)[index]) = path;
}/// SolverGene::updateSeeds

void SolverGene::updateSnippets(const LI& path) {
  snippets_forward_->update(path);
  snippets_backward_->update(path);
}/// SolverGene::updateSnippets
}/// namespace ChineseIdiomChain
