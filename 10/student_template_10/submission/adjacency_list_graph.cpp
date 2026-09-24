// Simon Sutoris 7542170
// Eric Berger 7064584

##include "adjacency_list_graph.h"

#include <algorithm>
#include <stdexcept>
#include <string>

    void detail::AdjacencyListGraphBase::add_edge(uint32_t from, uint32_t to,
                                                  float weight) {
  const size_t num_nodes = get_num_nodes();
  if (from >= num_nodes) {
    throw std::runtime_error("add_edge: not a valid node index");
  }

  if (edges.size() < num_nodes) {
    edges.resize(num_nodes);
  }

  std::vector<std::pair<uint32_t, float>> &edge_list = edges[from];
  for (const auto &pair : edge_list) {
    if (pair.first == to) {
      throw std::runtime_error("add_edge: edge already exists");
    }
  }

  edge_list.push_back(std::pair<uint32_t, float>(to, weight));
}

void detail::AdjacencyListGraphBase::remove_edge(uint32_t from, uint32_t to) {
  if (from >= edges.size()) {
    throw std::runtime_error("remove_edge: edge does not exist");
  }

  std::vector<std::pair<uint32_t, float>> &edge_list = edges[from];
  for (size_t i = 0; i < edge_list.size(); i++) {
    if (edge_list[i].first == to) {
      edge_list.erase(edge_list.begin() + i);
      return;
    }
  }
  throw std::runtime_error("remove_edge: edge does not exist");
}

std::optional<float>
detail::AdjacencyListGraphBase::get_edge(uint32_t from, uint32_t to) const {
  if (from >= edges.size()) {
    return std::optional<float>{};
  }

  const std::vector<std::pair<uint32_t, float>> &edge_list = edges[from];
  for (size_t i = 0; i < edge_list.size(); i++) {
    if (edge_list[i].first == to) {
      return edge_list[i].second;
    }
  }
  return std::optional<float>{};
}

const std::vector<std::pair<uint32_t, float>> &
detail::AdjacencyListGraphBase::get_edges_starting_at(uint32_t node) const {
  static const std::vector<std::pair<uint32_t, float>> no_edges;

  if (node >= edges.size()) {
    return no_edges;
  }
  return edges[node];
}
