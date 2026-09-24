#include "shortest_paths.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <iterator>
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
    size_t num_visited = 0;

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

  // heuristic for A*
  std::vector<float> h;
  h.reserve(adjacency_matrix.size());
  for (size_t i = 0; i < adjacency_matrix.size(); ++i) {
      Location a = adjacency_matrix[to];
      Location b = adjacency_matrix[i];
      float diff_x = a.pos_x - b.pos_x;
      float diff_y = a.pos_y - b.pos_y;
      float euclidian_distance = std::sqrt(diff_x * diff_x + diff_y * diff_y);
      h.push_back(euclidian_distance);
  }

  // we store the distance additionally to the node, as to check for stale
  // references later, as we might push some neighbors multiple times
  std::vector<std::pair<size_t, float>> Q{{from, 0.0f}}; // <index, distance>

  auto comp = [&](auto lhs, auto rhs){
      float dist_l = lhs.second;
      float dist_r = rhs.second;
      float h_l = h[lhs.first];
      float h_r = h[rhs.first];
      return (dist_l + h_l) > (dist_r + h_r);
  };
  std::make_heap(Q.begin(),Q.end(),comp);

  // main loop
  while (!Q.empty()) {
      std::pop_heap(Q.begin(), Q.end(), comp);
      auto [u, stored_distance] = Q.back();
      Q.pop_back();

      num_visited += 1;

      if (stored_distance != dist[u]) {
          // this is a stale reference for u, indicating it was already
          // processed with a better distance
          continue;
      }

      if (u == to) {
          // found the end! stop searching...
          break;
      }

      Location location_u = adjacency_matrix[u];
      for (size_t v = 0; v < adjacency_matrix.size(); ++v) {
          float dist_between = location_u[v].value_or(std::numeric_limits<float>::infinity());
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

  std::cout << "Nodes visited: " << num_visited << std::endl;

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
