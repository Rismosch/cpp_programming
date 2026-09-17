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
  std::map<const std::string, size_t> word_counts;
  for (auto word : words) {
    word_counts[word] += 1;
  }

  // compute probabilities
  for (auto it = word_counts.begin(); it != word_counts.end(); ++it) {
    const std::string word = it->first;
    size_t count = it->second;
    double probability =
        static_cast<double>(count) / static_cast<double>(words.size());

    histogram[word] = probability;
    probabilities.insert({probability, word});
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

  auto it = probabilities.begin();
  for (unsigned int i = 0; it != probabilities.end() && i < n_words;
       ++it, ++i) {
    result.push_back(*it);
  }

  return result;
}

// TODO 5.1.c
// TODO 5.1.d
