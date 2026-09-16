// Simon Sutoris 7542170
// Eric Berger 7064584
#pragma once

#include "Food.h"
class DeadCell : public Food {

public:
  DeadCell(double health_, double power_, double defence_);
  ~DeadCell();

  virtual Food *clone() const override;
};
