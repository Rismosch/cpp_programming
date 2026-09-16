#include "Amoeba.h"

Amoeba::Amoeba() : Food(1000.0, 50.0, 50.0, 0.0, 0.0) { name = "Amoeba"; };

Amoeba::Amoeba(double health_, double power_, double defence_,
               double dna_level_th)
    : Food(health_, power_, defence_, 0, 0), dna_level_th(dna_level_th) {
  name = "Amoeba";
};

Amoeba::~Amoeba(){};
// TODO: task k)
Food *Amoeba::clone() const {
  return 0; // Your Code here
}

void Amoeba::eat(double health, double dna) {
  this->health += health;
  this->dna_level += dna;

  if (this->dna_level >= this->dna_level_th) {
    this->dna_level = 0;
    this->dna_level_th *= 2;
  }
}

void Amoeba::print_header() {
  std::cout << std::setw(10) << "name"
            << " | ";
  std::cout << std::setw(10) << "health"
            << " | ";
  std::cout << std::setw(10) << "power"
            << " | ";
  std::cout << std::setw(10) << "defence"
            << " | ";
  std::cout << std::setw(10) << "dna_level"
            << " | ";
  std::cout << std::setw(10) << "dna_level_th"
            << "\n";
}

void Amoeba::print() {
  std::cout << std::setw(10) << name << " | ";
  std::cout << std::setw(10) << health << " | ";
  std::cout << std::setw(10) << power << " | ";
  std::cout << std::setw(10) << defence << " | ";
  std::cout << std::setw(10) << dna_level << " | ";
  std::cout << std::setw(10) << dna_level_th << "\n";
}
