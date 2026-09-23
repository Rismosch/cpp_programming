// Simon Sutoris 7542170
// Eric Berger 7064584

#include "exercise_82.h"
#include "point.h"
#include <algorithm>
#include <vector>

std::vector<Point> sort_x(const std::vector<Point> &points) {
  std::vector<Point> sorted = points;
  std::sort(sorted.begin(), sorted.end(),
          [](const Point& a, const Point& b) {
            if (a.x != b.x) return a.x < b.x;
            return a.y < b.y;
          });
  return sorted;
}

std::vector<Point> sort_y(const std::vector<Point> &points) {
  std::vector<Point> sorted = points;
  std::sort(sorted.begin(), sorted.end(),
          [](const Point& a, const Point& b) {
            if (a.y != b.y) return a.y < b.y;
            return a.x < b.x;
          });
  return sorted;
}

Point median(const std::vector<Point> &points) {
  std::vector<Point> by_x = sort_x(points);
  std::vector<Point> by_y = sort_y(points);
  std::size_t n = points.size();
  float median_x;
  float median_y;

  if (n % 2 == 1) {
    median_x = by_x[n / 2].x;
    median_y = by_y[n / 2].y;
  } else {
    median_x = (by_x[n / 2 - 1].x + by_x[n / 2].x) / 2.0f;
    median_y = (by_y[n / 2 - 1].y + by_y[n / 2].y) / 2.0f;
  }
  return Point(median_x, median_y);
}