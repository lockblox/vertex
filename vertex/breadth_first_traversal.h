#pragma once

#include <vertex/traversal.h>
#include <memory>
#include <queue>

namespace vertex {
/**@TODO Allow construction AT a given parent/child. Store child link pointer.
 * Ensure Iterator can be used to construct container of values */

/** Bredth first tree traversal */
template <typename Container,
          typename Predicate = NullaryPredicate<Container, true>>
class breadth_first_traversal
    : public traversal<Container, breadth_first_traversal<Container, Predicate>,
                       Predicate> {
 public:
  using self_type = breadth_first_traversal<Container, Predicate>;
  using base_type = traversal<Container, self_type, Predicate>;
  using base_type::base_type;
  using base_type::edge;
  using base_type::isTraversible;
  using base_type::position;
  using base_type::vertex;
  using base_type::vertices;

  bool next();

 private:
  std::queue<typename base_type::edge_type> to_visit_;
};

template <typename Container, typename Predicate>
breadth_first_traversal<Container, Predicate> makeBreadthFirstTraversal(
    Container container, Predicate predicate);

template <typename Container, typename Predicate>
bool breadth_first_traversal<Container, Predicate>::next() {
  auto result = false;
  if (position() != vertices().end()) {
    for (const auto& child : position()->second.links()) {
      auto e = std::make_pair(position()->first, child);
      if (isTraversible(e)) {
        to_visit_.push(e);
      }
    }
  } else {
    result = false;
  }
  while (!to_visit_.empty()) {
    auto edge = to_visit_.front();
    to_visit_.pop();
    base_type::position(vertices().find(edge.second));
    if (position() != vertices().end()) {
      result = true;
      break;
    }
  }
  return result;
}

template <typename Container, typename Predicate>
breadth_first_traversal<Container, Predicate> makeBreadthFirstTraversal(
    Container container, Predicate predicate) {
  return breadth_first_traversal<decltype(container), decltype(predicate)>(
      std::forward(container), std::forward(predicate));
}

}  // namespace vertex