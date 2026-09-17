// Simon Sutoris 7542170
// Eric Berger 7064584

#include "histogram.h"

#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>

Histogram::Histogram(const std::vector<std::string> &words) {

  // count words
  std::map<const std::string, size_t> count;
  for (auto word : words) {
    count[word] += 1;
  }

  // compute probabilities
  for (auto it = count.begin(); it != count.end(); ++it) {
    auto word = it->first;
    auto count = it->second;
    auto probability =
        static_cast<double>(count) / static_cast<double>(words.size());

    histogram[word] = probability;
    sorted_probabilities.push_back({probability, word});
  }

  // sort probabilities for fast retreival, using insertion sort
  int n = sorted_probabilities.size();
  int i = 1;
  while (i < n) {
    int j = i;
    while (j > 0 && sorted_probabilities[j - 1] < sorted_probabilities[j]) {
      std::swap(sorted_probabilities[j], sorted_probabilities[j - 1]);
      j -= 1;
    }

    i += 1;
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

std::vector<std::pair<double, std::string>>
Histogram::most_common_words(unsigned int n_words) const {
  std::vector<std::pair<double, std::string>> result;

  int max =
      std::min(n_words, static_cast<unsigned int>(sorted_probabilities.size()));
  for (int i = 0; i < max; ++i) {
    result.push_back(sorted_probabilities[i]);
  }

  return result;
}

// TODO 5.1.c
// TODO 5.1.d
