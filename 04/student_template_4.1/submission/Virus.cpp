#include "Virus.h"

Virus::Virus(double health_, double power_, double defence_)
    : Food(health_, power_, defence_, 400.0, 400.0) {}

Virus::~Virus() {}
// TODO: task k)
Food *Virus::clone() const {
  // Your Code
  return 0;
}
