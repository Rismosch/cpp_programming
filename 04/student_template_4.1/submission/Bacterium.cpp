#include "Bacterium.h"

Bacterium::Bacterium(double health_, double power_, double defence_)
    : Food(health_, power_, defence_, 10.0, 200.0) {}

Bacterium::~Bacterium() {}
// TODO: task k)
Food *Bacterium::clone() const {
  // Your Code
  return 0;
}
