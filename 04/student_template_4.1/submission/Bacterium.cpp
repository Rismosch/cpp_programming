// Simon Sutoris 7542170
// Eric Berger 7064584
#include "Bacterium.h"
Bacterium::Bacterium(double health_, double power_, double defence_)
    : Food(health_, power_, defence_, 10.0, 200.0) {
  name = "Bacterium";
}

Bacterium::~Bacterium() {}
Food *Bacterium::clone() const { return new Bacterium(*this); }
