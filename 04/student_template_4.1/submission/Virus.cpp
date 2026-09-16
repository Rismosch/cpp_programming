#include "Virus.h"

Virus::Virus(double health_, double power_, double defence_)
    : Food(health_, power_, defence_, 400.0, 400.0) {
  name = "Virus";
}

Virus::~Virus() {}

Food *Virus::clone() const { return new Virus(*this); }
