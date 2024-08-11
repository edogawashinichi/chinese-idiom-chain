/// path.cpp

#include "path.h"

namespace ChineseIdiomChain {

Path::Path(const LI& list) : vertices_(list) {
}/// Path::Path

void Path::assign(const LI& list) {
  vertices_ = list;
}/// Path::assign

int Path::getForwardMaxUniqueIndex(const VI& memo, const VI& visited) const {
  /// assume that vertices_.back() == memo.front()
  /// visited is superset of vertices_
  SI vis_set(vertices_.begin(), vertices_.end());
  for (int i = 0; i < visited.size(); ++i) {
    if (visited[i]) vis_set.insert(i);
  }
  int max_index = 1;
  for (; max_index < memo.size(); ++max_index) {
    if (vis_set.count(memo[max_index])) break;
  }
  return max_index - 1;
}/// Path::getForwardMaxUniqueIndex
int Path::getBackwardMinUniqueIndex(const VI& memo, const VI& visited) const {
  /// assume that vertices_.front() == memo.back()
  /// visited is superset of vertices_
  SI vis_set(vertices_.begin(), vertices_.end());
  for (int i = 0; i < visited.size(); ++i) {
    if (visited[i]) vis_set.insert(i);
  }
  int min_index = memo.size() - 2;
  for (; min_index >= 0; --min_index) {
    if (vis_set.count(memo[min_index])) break;
  }
  return min_index + 1;
}/// Path::getBackwardMinUniqueIndex

void Path::show(const Mapper& mapper) const {
  for (const auto vertex : vertices_) {
    cout << mapper.code2idiom_.at(vertex) << "  ";
  }
  cout << "\nsize: " << vertices_.size() << "\n";
}/// Path::show

}/// namespace ChineseIdiomChain
