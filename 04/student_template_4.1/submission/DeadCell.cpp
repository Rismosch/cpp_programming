#include "DeadCell.h"
// TODO: task c)
DeadCell::DeadCell(double health_, double power_, double defence_)
    : Food(health_, power_, defence_, 0, 0)
// Your Code
{
  // Your Code
}

DeadCell::~DeadCell() {}
// TODO: task k)
Food *DeadCell::clone() const {
  // Your Code
  return 0;
}
