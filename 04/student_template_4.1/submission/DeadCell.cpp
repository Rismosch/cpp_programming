#include "DeadCell.h"

DeadCell::DeadCell(double health_, double power_, double defence_)
    : Food(health_, power_, defence_, 10.0, 100.0) {}

DeadCell::~DeadCell() {}
// TODO: task k)
Food *DeadCell::clone() const {
  // Your Code
  return 0;
}
