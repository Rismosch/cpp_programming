// Simon Sutoris 7542170
// Eric Berger 7064584

#include "exercise_81.h"
#include <algorithm>
#include <vector>
#include <numeric>


float MSE(const std::vector<float>& ground_truth,
          const std::vector<float>& prediction) {
  std::vector<float> result(prediction.size());
  std::transform(ground_truth.begin(), ground_truth.end(),
    prediction.begin(),
    result.begin(),
    [](float gt, float pred) {return (gt - pred) * (gt - pred);}
  );
  float total = std::accumulate(result.begin(), result.end(), 0.0f);
  return total / static_cast<float>(prediction.size());
}

float MAE(const std::vector<float>& ground_truth,
          const std::vector<float>& prediction) {
  std::vector<float> result(prediction.size());
  std::transform(ground_truth.begin(), ground_truth.end(),
    prediction.begin(),
    result.begin(),
    [](float gt, float pred) {return std::abs(gt - pred);}
  );
  float total = std::accumulate(result.begin(), result.end(), 0.0f);
  return total / static_cast<float>(prediction.size());
}

std::vector<int> range(int start, int end) {
  if (start >= end) return {};
  std::vector<int> integer_range(end-start);
  std::generate(integer_range.begin(), integer_range.end(),
    [start]() mutable {
      return start++;
    });
    return integer_range;
}

