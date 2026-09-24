#include "random_walk_graph.h"

#include <algorithm>
#include <fstream>
#include <ios>
#include <numeric>
#include <random>
#include <iostream>
#include <stdexcept>

void RandomWalkGraph::simulate_random_walk(uint32_t num_steps) {
    if (size() == 0) {
        return;
    }
    std::uniform_int_distribution<uint32_t> pick_start{0, static_cast<uint32_t>(size() - 1)};
    uint32_t current = pick_start(prng);

    for (uint32_t step = 0; step < num_steps; ++step) {
        const auto& outgoing = get_edges_starting_at(current);

        const float weight_sum = std::accumulate(
            outgoing.begin(), outgoing.end(), 0.0f,
            [](float sum, const std::pair<uint32_t, float>& edge) { return sum + edge.second; });

        if (!outgoing.empty() && weight_sum > 0.0f) {
            std::uniform_real_distribution<float> pick_weight{0.0f, weight_sum};
            const float r = pick_weight(prng);

            float running_sum = 0.0f;
            uint32_t next = outgoing.back().first;
            for (const auto& [to, weight] : outgoing) {
                running_sum += weight;
                if (running_sum > r) {
                    next = to;
                    break;
                }
            }
            current = next;
        }
        ++(*this)[current];
    }
}

void RandomWalkGraph::write_histogram_pgm(const std::string& filename, uint32_t width, uint32_t height) const {
    const uint64_t num_pixels = static_cast<uint64_t>(width) * height;
    if (num_pixels == 0 || num_pixels != size()) {
        throw std::runtime_error("write_histogram_pgm: resolution does not match the number of nodes");
    }

    std::ofstream file(filename, std::ofstream::out | std::ofstream::trunc | std::ofstream::binary);
    if (!file) {
        throw std::runtime_error("write_histogram_pgm: could not open " + filename);
    }
    
    file << "P5\n" << width << " " << height << "\n255\n";
    const std::vector<unsigned char> pixels = compute_normalized_histogram<unsigned char>(255);
    file.write(reinterpret_cast<const char*>(pixels.data()),
               static_cast<std::streamsize>(pixels.size()));

    if (!file) {
        throw std::runtime_error("write_histogram_pgm: writing failed");
    }
}
