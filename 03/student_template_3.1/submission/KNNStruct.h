#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <unordered_map>
#include <vector>

/* returns a random float between 0.0f and 1.0f */
float random_float() {
  return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
}

/* returns a random float between bounds. bounds are inclusive */
float random_float_between(float min, float max) {
  // sanity check if bounds are correct
  if (max <= min) {
    if (max == min) {
      return min;
    } else {
      return NAN;
    }
  }

  // generate random number and map into range
  auto x = random_float();
  auto r = (max - min) * x + min;

  // in some edgecases, r might be larger than max. in this case, clamp r to max
  return r > max ? max : r;
}

struct DYNPoint {
  std::vector<float> data;

  // We use a static function to return a DYNPoint object (this pattern is
  // sometimes called a "factory method") We can mark functions as nodiscard to
  // indicate that we must use the return value in some way (e.g, it doesn't get
  // discarded as ).
  [[nodiscard]] static DYNPoint createRandomPoint(unsigned int size,
                                                  int minimum = -5000,
                                                  int maximum = 5000) {
    DYNPoint p;

    if (size == 0 || minimum > maximum) {
      return p;
    }

    p.data.reserve(size);

    for (unsigned int i = 0; i < size; ++i) {
      float point = random_float_between(static_cast<float>(minimum),
                                         static_cast<float>(maximum));
      p.data.push_back(point);
    }

    return p;
  }
};

struct KnnDistance {
  std::pair<DYNPoint, unsigned int> dataPoint;
  float distance;

  const static bool compare(KnnDistance lhs, KnnDistance rhs) {
    return lhs.distance < rhs.distance;
  }
};

struct KNN {
  KNN(float (*_function_ptr_Distance)(const DYNPoint &, const DYNPoint &))
      : function_ptr_Distance(_function_ptr_Distance) {}

  std::vector<std::pair<DYNPoint, unsigned int>>
      trainingData{}; // default initialize on creation

  float (*function_ptr_Distance)(const DYNPoint &, const DYNPoint &) = 0;

  // just sets the training data (no actual training required)
  void TrainKNN(const std::vector<std::pair<DYNPoint, unsigned int>> &dataset) {
    trainingData.clear();
    trainingData = dataset;
  }

  int classify(const unsigned int k, const DYNPoint &A) const {

    if (!k || !function_ptr_Distance || !trainingData.size()) {
      return -1;
    }

    // compute the distances
    std::vector<KnnDistance> distances;
    distances.reserve(trainingData.size());

    for (auto dataPoint : this->trainingData) {
      KnnDistance distance;
      distance.dataPoint = dataPoint;
      distance.distance = function_ptr_Distance(A, dataPoint.first);
      distances.push_back(distance);
    }

    // sort by distance
    std::sort(distances.begin(), distances.end(), KnnDistance::compare);

    // count classes
    std::unordered_map<unsigned int, size_t> classes; // <class, count>

    for (unsigned int i = 0; i < k; ++i) {
      auto c = distances[i].dataPoint.second;
      auto entry = classes.find(c);
      if (entry != classes.end()) {
        entry->second += 1;
      } else {
        classes.insert({c, 1});
      }
    }

    // find max
    auto it = classes.begin();
    unsigned int candidate = it->first;
    size_t max_count = it->second;
    for (++it; it != classes.end(); ++it) {
      if (it->second > max_count) {
        candidate = it->first;
        max_count = it->second;
      }
    }

    return static_cast<int>(candidate);
  }
};

float DistanceManhattan(const DYNPoint &A, const DYNPoint &B) {
  assert(A.data.size() == B.data.size());

  float sum = 0;

  for (size_t i = 0; i < A.data.size(); ++i) {
    sum += std::abs(A.data[i] - B.data[i]);
  }

  return sum / static_cast<float>(A.data.size());
}

float DistanceEuclid(const DYNPoint &A, const DYNPoint &B) {
  assert(A.data.size() == B.data.size());

  float sum = 0;

  for (size_t i = 0; i < A.data.size(); ++i) {
    float diff = A.data[i] - B.data[i];
    sum += diff * diff;
  }

  return std::sqrt(sum / static_cast<float>(A.data.size()));
}

void createDataset(std::vector<std::pair<DYNPoint, unsigned int>> &dataset,
                   const unsigned int amount, const unsigned int class_label,
                   const unsigned int point_size, const int minimum,
                   const int maximum) {

  if (amount > 0 && point_size > 0 && minimum <= maximum) {

    // STUDENT TODO: your code
  }
}

void evaluateKNN(const std::vector<std::pair<DYNPoint, unsigned int>> &dataset,
                 const KNN &Classifier, const unsigned int k) {
  if (!dataset.empty()) {
    float acc = 0;
    for (size_t i = 0; i < dataset.size(); i++) {
      if (static_cast<unsigned int>(Classifier.classify(k, dataset[i].first)) ==
          dataset[i].second)
        acc++;
    }
    std::cout << "Accuracy: " << acc / float(dataset.size()) << std::endl;
  }
}
