#include "submission/adjacency_list_graph.h"
#include "submission/random_walk_graph.h"

#include <cstdint>
#include <cstdlib>

#include <array>
#include <cassert>
#include <cstring>
#include <fstream>
#include <ios>
#include <iostream>

int main() {
  try {
    RandomWalkGraph graph =
        RandomWalkGraph::deserialize("../student_template_10/secret.graph");
    std::cout << "Loaded graph with " << graph.size() << " nodes\n";

    const uint32_t num_walks = 1000;
    const uint32_t num_steps = 100000;
    for (uint32_t i = 0; i < num_walks; ++i) {
      graph.simulate_random_walk(num_steps);
    }

    graph.write_histogram_pgm("histogram.pgm", 270, 354);
    std::cout << "Wrote histogram.pgm\n";
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
  return 0;
}
