#include "shortest_paths.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <utility>

size_t ShortestPaths::getNodeIdByName(const std::string &name) const {
  // NOTE: if you like, you can make this more efficient by caching the mapping
  // in a mutable hash map that gets reset when calling non-const functions
  const auto it = std::find_if(
      adjacency_matrix.begin(), adjacency_matrix.end(),
      [=](const Location &row) -> bool { return row.name == name; });
  if (it == adjacency_matrix.end())
    throw std::runtime_error("Location " + name + " not found");
  return static_cast<size_t>(std::distance(adjacency_matrix.begin(), it));
}

std::vector<size_t> ShortestPaths::compute_shortest_path(size_t from,
                                                     size_t to) const {
  // unkown distance function from source to v
  std::vector<float> dist(
          adjacency_matrix.size(),
          std::numeric_limits<float>::infinity()
  );

  // previous node in optimal path from source
  const size_t undefined = ~static_cast<size_t>(0);
  std::vector<size_t> previous(
    adjacency_matrix.size(),
    undefined
  );

  // distance from source to source
  dist[from] = 0;

  // we store the distance additionally to the node, as to check for stale
  // references later, as we might push some neighbors multiple times
  std::vector<std::pair<size_t, float>> Q{{from, 0.0f}}; // <index, distance>

  auto comp = [&](auto lhs, auto rhs){return lhs.second > rhs.second;};
  std::make_heap(Q.begin(),Q.end(),comp);

  // main loop
  while (!Q.empty()) {
      std::pop_heap(Q.begin(), Q.end(), comp);
      auto [u, stored_distance] = Q.back();
      Q.pop_back();

      if (stored_distance != dist[u]) {
          // this is a stale reference for u, indicating it was already
          // processed with a better distance
          continue;
      }

      if (u == to) {
          // found the end! stop searching...
          break;
      }

      Location location = adjacency_matrix[u];
      for (size_t v = 0; v < adjacency_matrix.size(); ++v) {
          float dist_between = location[v].value_or(std::numeric_limits<float>::infinity());
          if (std::isinf(dist_between)) {
              continue; // u and v are not neighbors
          }

          float alt = dist[u] + dist_between;
          if (alt < dist[v]) {
              dist[v] = alt;
              previous[v] = u;
              Q.push_back({v, alt});
              std::push_heap(Q.begin(), Q.end(), comp);
          }
      }
  }

  // return path
  std::vector<size_t> path;
  size_t current = to;
  while (true) {
      if (current == undefined) {
          return {};
      }

      path.push_back(current);
      if (current == from) {
          std::reverse(path.begin(), path.end());
          return path;
      }

      current = previous[current];
  }
}
