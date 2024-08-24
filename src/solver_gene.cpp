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
  loadSeeds();
  loadSnippetsForward();
  loadSnippetsBackward();
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

  LI path;
  VI visited(graph_->maxVertex() + 1, 0);
  const int C = 1.3 * seeds_->capacity_ + 1;
  const int index = randomChoose(C);
  if (index < seeds_->capacity_) {
    const int sz = (seeds_->communities_)[index]->size();
    if (sz != 0) {
      const auto pair = randomChooseInterval(sz);
      LI::iterator it_start = (seeds_->communities_)[index]->begin();
      std::advance(it_start, pair.first);
      LI::iterator it_end = (seeds_->communities_)[index]->begin();
      std::advance(it_end, pair.second + 1);
      path.splice(path.begin(), *((seeds_->communities_)[index]), it_start, it_end);
      for (const auto vertex : path) {
        visited[vertex] = 1;
      }/// for path
    }/// if sz != 0
  }/// if index != C - 1

  if (path.size() == 0) {
    const int index = randomChoose(graph_->order());/// order: vertex size; size: edge size
    const int vertex = (graph_->vertices_)[index];
    path.emplace_back(vertex);
    visited[vertex] = 1;
  }

  instant_ret_ = 0;
  memoBiDFS(path, visited);
  
  cacheSeeds();
  cacheSnippetsForward();
  cacheSnippetsBackward(); 

}/// SolverGene::runOnce

int SolverGene::instantRet(const LI& path, const VI& visited) {
  const int visited_cnt = count(visited.begin(), visited.end(), 1);
  const int size_upper_bound = path.size() + graph_->order() - visited_cnt;
  if (size_upper_bound < best_path_.size()) {
    instant_ret_ = 1;
    return 1;
  }
  const float ratio = 0.005f;
  if (path.size() < best_path_.size() * (1 - ratio) && visited_cnt > best_path_.size() * (1 + 40 * ratio)) {
    instant_ret_ = 1;
    return 1;
  }
  return instant_ret_;
}/// SolverGene::instantRet

void SolverGene::memoBiDFS(LI& path, VI& visited) {
  /// condition -> immediately return from recursive stack
  if (instant_ret_ || instantRet(path, visited)) return;

    const int visited_cnt = std::count(visited.begin(), visited.end(), 1);
    STR_VAR_2_L(path.size(), visited_cnt)

  updateSolution(path);
  updateSeeds(path);
  updateSnippets(path);

  VI unvisitedPredecessors;
  graph_->getUnvisitedPredecessors(path.front(), visited, &unvisitedPredecessors);
  VI unvisitedSuccessors;
  graph_->getUnvisitedSuccessors(path.back(), visited, &unvisitedSuccessors);
  if (unvisitedPredecessors.empty() && unvisitedSuccessors.empty()) {
    return;
  }

  bool ward = decideDirection(unvisitedSuccessors.empty(), unvisitedPredecessors.empty());

  /// TODO: consider class Searcher
  if (ward) {/// forward
    if (!bet(search_ratio_)) {
      memoForwardDFS(path, visited);
    }
    forwardDFS(unvisitedSuccessors, path, visited);
  } else {/// backward
    if (!bet(search_ratio_)) {
      memoBackwardDFS(path, visited);
    }
    backwardDFS(unvisitedPredecessors, path, visited);
  }/// else backward
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
  const int back = path.back();
  if (false == (snippets_forward_->end2path_).count(back)) return;
  const auto& memo = (snippets_forward_->end2path_).at(back);
  const int max_unique_index = Path(path).getForwardMaxUniqueIndex(memo, visited);
  if (max_unique_index < extension_size_) return;
  const int index = randomChoose(extension_size_, max_unique_index);
  for (int i = 1; i <= index; ++i) {
    const int vertex = memo[i];
    path.emplace_back(vertex);
    visited[vertex] = 1;
  }
  const int size_actual_extend = index;
  memoBiDFS(path, visited);
  /*const auto& memo2 = (snippets_forward_->end2path_).at(back);
  for (int i = 1; i <= index; ++i) {
    path.pop_back();
    visited[memo2[i]] = 0;
  }*/
  for (int i = 0; i < size_actual_extend; ++i) {
    const int vertex = path.back();
    path.pop_back();
    visited[vertex] = 0;
  }
}/// SolverGene::memoForwardDFS
void SolverGene::memoBackwardDFS(LI& path, VI& visited) {
  const int front = path.front();
  if (false == (snippets_backward_->end2path_).count(front)) return;
  const auto& memo = (snippets_backward_->end2path_).at(front);
  const int min_unique_index = Path(path).getBackwardMinUniqueIndex(memo, visited);
  const int max_extension_size = memo.size() - 1 - min_unique_index;
  if (max_extension_size < extension_size_) return;
  const int index = randomChoose(min_unique_index, memo.size() - 2);
  for (int i = memo.size() - 2; i >= index; --i) {
    const int vertex = memo[i];
    path.emplace_front(vertex);
    visited[vertex] = 1;
  }
  const int size_actual_extend = memo.size() - 1 -index;
  memoBiDFS(path, visited);
  ///memo变化导致index失效
  /*for (int i = memo.size() - 2; i >= index; --i) {
    path.pop_back();
    visited[memo[i]] = 0;
  }*/
  for (int i = 0; i < size_actual_extend; ++i) {
    const int vertex = path.front();
    path.pop_front();
    visited[vertex] = 0;
  }
}/// SolverGene::memoBackwardDFS

void SolverGene::forwardDFS(VI& successors, LI& path, VI& visited) {
  shuffle(successors);
  for (const auto succ : successors) {
    if (visited[succ]) continue;/// shall check visited due to recovery_ratio_
    path.emplace_back(succ);
    visited[succ] = 1;
    memoBiDFS(path, visited);
    path.pop_back();
    if (bet(recovery_ratio_)) visited[succ] = 0;
  }/// for
}/// SolverGene::forwardDFS
void SolverGene::backwardDFS(VI& predecessors, LI& path, VI& visited) {
  shuffle(predecessors);
  for (const auto pred : predecessors) {
    if (visited[pred]) continue;
    path.emplace_front(pred);
    visited[pred] = 1;
    memoBiDFS(path, visited);
    path.pop_front();
    if (bet(recovery_ratio_)) visited[pred] = 0;
  }/// for
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
  seeds_->cache(SEEDS_DIR);
}/// SolverGene::cacheSeeds

CIC__FUNC_SNIPPETS(load, Forward, forward, FORWARD)
CIC__FUNC_SNIPPETS(load, Backward, backward, BACKWARD)
CIC__FUNC_SNIPPETS(cache, Forward, forward, FORWARD)
CIC__FUNC_SNIPPETS(cache, Backward, backward, BACKWARD)

void SolverGene::updateSeeds(const LI& path) {
  const int N = seeds_->capacity_;
  VI freq(N, 0);
  for (int i = 0; i < freq.size(); ++i) {
    freq[i] = (seeds_->communities_[i])->size() + 1;/// cannot transform unique_ptr
  }
  inverseSharpen(freq);
  const int index = randomChoose(freq);
  *((seeds_->communities_)[index]) = path;
}/// SolverGene::updateSeeds

void SolverGene::updateSnippets(const LI& path) {
  snippets_forward_->update(path);
  snippets_backward_->update(path);
}/// SolverGene::updateSnippets
}/// namespace ChineseIdiomChain
