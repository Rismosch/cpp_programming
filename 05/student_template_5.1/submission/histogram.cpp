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

double Histogram::dissimilarity(const Histogram &other) const {
  auto &A = this->histogram;
  auto &B = other.histogram;

  double abs_A = static_cast<double>(A.size());
  double abs_B = static_cast<double>(B.size());
  double abs_S = 0.0; // computed below

  double sum = 0.0;
  for (const auto &[w, probability_A] : A) {
    auto entry_B = B.find(w);
    if (entry_B == B.end()) {
      continue;
    }

    double probability_B = entry_B->second;

    sum += std::abs(probability_A - probability_B);
    abs_S += 1;
  }

  return (1 - abs_S / abs_A) + (1 - abs_S / abs_B) + sum;
}

size_t Histogram::closest(const std::vector<Histogram> &candidates) const {
  if (candidates.empty()) {
    // candidates empty, return error value
    return ~size_t{0};
  }

  size_t lowest_index = 0;
  double lowest_dissimilarity = this->dissimilarity(candidates[0]);
  for (size_t i = 1; i < candidates.size(); ++i) {
    double dissimilarity = this->dissimilarity(candidates[i]);
    if (dissimilarity < lowest_dissimilarity) {
      lowest_index = i;
      lowest_dissimilarity = dissimilarity;
    }
  }

  return lowest_index;
}
