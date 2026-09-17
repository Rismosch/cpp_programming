// Simon Sutoris 7542170
// Eric Berger 7064584

#include "histogram.h"

#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>

Histogram::Histogram(const std::vector<std::string> &words) {
  std::map<const std::string, size_t> count;
  for (auto word : words) {
    count[word] += 1;
  }

  for (auto it = count.begin(); it != count.end(); ++it) {
    auto word = it->first;
    auto count = it->second;
    histogram[word] =
        static_cast<double>(count) / static_cast<double>(words.size());
  }
}

size_t Histogram::size() const { return histogram.size(); }

bool Histogram::contains(const std::string &word) const {
  return histogram.find(word) != histogram.end();
}

double Histogram::probability(const std::string &word) const {
  auto entry = histogram.find(word);
  if (entry == histogram.end()) {
    return 0.0;
  } else {
    return entry->second;
  }
}

// TODO 5.1.b
// TODO 5.1.c
// TODO 5.1.d
