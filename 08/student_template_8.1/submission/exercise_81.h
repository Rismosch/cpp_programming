// Simon Sutoris 7542170
// Eric Berger 7064584

#pragma once
#include <algorithm>
#include <vector>

/**
 * @brief Comutes the Mean Squared Error.
 * You can assume that ground_truth.size() == prediction.size()
 *
 * @param ground_truth Vector of ground truth values.
 * @param prediction Vector or predictions.
 * @return float The MSE value.
 */
float MSE(const std::vector<float> &ground_truth,
          const std::vector<float> &prediction);

/**
 * @brief Comutes the Mean Absolute Error.
 * You can assume that ground_truth.size() == prediction.size()
 *
 * @param ground_truth Vector of ground truth values.
 * @param prediction Vector or predictions.
 * @return float The MAE value.
 */
float MAE(const std::vector<float> &ground_truth,
          const std::vector<float> &prediction);

template <typename T, typename U>
std::vector<std::pair<T, U>> zip(const std::vector<T> &vec1,
                                 const std::vector<U> &vec2) {
  std::vector<std::pair<T, U>> result(vec1.size());
  std::transform(vec1.begin(), vec1.end(), vec2.begin(), result.begin(),
                 [](const T &x, const U &y) { return std::pair<T, U>(x, y); });
  return result;
}

/**
 * @brief Generates a vector with integer values in the range [start, end[
 * Note: The list must be empty if start >= end
 *
 * @param start The first value in the returned vector
 * @param end The upper limit of the range. This value is not included.
 * @return std::vector<int> The generated vector.
 */
std::vector<int> range(int start, int end);
