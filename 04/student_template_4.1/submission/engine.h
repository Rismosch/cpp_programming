// Simon Sutoris 7542170
// Eric Berger 7064584
#pragma once

// own classes
#include "Amoeba.h"
#include "Bacterium.h"
#include "DeadCell.h"
#include "Virus.h"

// STL classes
#include <vector>

double random_value(double difficulty = 1.0) {
  return (double((std::rand() % 800) + 100) / 1000.0) *
         difficulty; // [0.1 .. 0.899] * difficulty
}

bool combat(Amoeba *player, Food *enemy) {
  std::cout
      << "\n+++++++++++++++++++++++++ new round ++++++++++++++++++++++++\n"
      << std::endl;

  unsigned int turn = 0;

  bool player_won{false};

  if (player && enemy) {
    // print enemy and player information
    enemy->print_header();
    enemy->print();
    player->print_header();
    player->print();

    // fight until either player or enemy lost
    while (player->is_alive() && enemy->is_alive()) {
      turn++;

      // player attacks first
      enemy->attacked([player](double &health, double defence) {
        double damage =
            random_value() * player->get_power() - random_value() * defence;
        if (damage > 0.0) {
          health -= damage;
        }
      });

      // enemy attacks second
      player->attacked([enemy](double &health, double defence) {
        double damage =
            random_value() * enemy->get_power() - random_value() * defence;
        if (damage > 0.0) {
          health -= damage; // player's health
        }
      });

      // print enemy and player information for this turn
      std::cout << "---------- turn: " << turn << " -----------" << std::endl;
      enemy->print_header();
      enemy->print();
      player->print_header();
      player->print();
    }

    player_won = (player->is_alive() && !enemy->is_alive());

    if (player_won) {
      player->eat(enemy->get_health_gain(), enemy->get_dna_gain());
    }
  }

  std::cout
      << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
      << std::endl;

  return player_won;
}

void engine() {
  std::cout << "Start game!" << std::endl;

  double difficulty{1.0};

  // create the player
  Amoeba player;

  // while player is still alive: fight!
  while (player.is_alive()) {
    std::cout << "Difficulty: " << difficulty << std::endl;

    // define a vector with distinct enemies (DeadCell, Bacterium, ...) which
    // are the competitors and available to fight in this round
    std::vector<Food *> all_enemies;
    all_enemies.push_back(new DeadCell(random_value(difficulty) * 10.0,
                                       random_value(difficulty) * 0.0,
                                       random_value(difficulty) * 0.0));

    all_enemies.push_back(new Bacterium(random_value(difficulty) * 200.0,
                                        random_value(difficulty) * 10.0,
                                        random_value(difficulty) * 50.0));

    all_enemies.push_back(new Virus(random_value(difficulty) * 500.0,
                                    random_value(difficulty) * 25.0,
                                    random_value(difficulty) * 25.0));
    if (all_enemies.empty())
      return;

    player.print_header();
    player.print();
    std::cout << "\n";

    // deep copy (one to three) random competitor the player can fight in this
    // round. Duplicates are allowed.
    std::vector<Food *> enemy;
    int count = std::rand() % 3 + 1;
    for (int i = 0; i < count; i++) {
      size_t index = std::rand() % all_enemies.size();
      enemy.push_back(all_enemies[index]->clone());
    }

    // print number of enemies selected for this round
    std::cout << std::setw(10) << "Select"
              << " : ";
    enemy[0]->print_header(); // only print header of first entry to reduce
                              // output in InfoMark
    for (size_t i = 0; i < enemy.size(); i++) {
      std::cout << std::setw(10) << i << " : ";
      enemy[i]->print();
    }
    std::cout << "Choose your enemy (0-" << enemy.size() - 1 << "): ";

    unsigned int selection;
    std::cin >> selection;

    selection = selection % enemy.size();

    combat(&player, enemy[selection]);

    difficulty += 1.0;

    for (Food *e : all_enemies) {
      delete e;
    }
    all_enemies.clear();

    for (Food *e : enemy) {
      delete e;
    }
    enemy.clear();
  }
  std::cout << "Player reached difficulty level (round): " << difficulty
            << std::endl;
}
