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
        auto result =
            random_value() * player->get_power() - random_value() * defence;
        if (result > 0) {
          health -= result;
        }
      });

      // enemy attacks second
      player->attacked([enemy](double &health, double defence) {
        auto result =
            random_value() * enemy->get_power() - random_value() * defence;
        if (result > 0) {
          health -= result;
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

    std::vector<Food *> all_enemies{
        new DeadCell(random_value(difficulty) * 10.0,
                     random_value(difficulty) * 0.0,
                     random_value(difficulty) * 0.0),
        new Bacterium(random_value(difficulty) * 200.0,
                      random_value(difficulty) * 10.0,
                      random_value(difficulty) * 50.0),
        new Virus(random_value(difficulty) * 500.0,
                  random_value(difficulty) * 25.0,
                  random_value(difficulty) * 25.0),
    };
    // Your Code here
    if (all_enemies.empty()) {
      std::cout << "no enemies\n";
      return;
    }

    player.print_header();
    player.print();
    std::cout << "\n";

    // deep copy (one to three) random competitor the player can fight in this
    // round. Duplicates are allowed.
    auto max_competitors = std::min(3, static_cast<int>(all_enemies.size()));
    auto competitor_count = (std::rand() % 3) + 1;
    std::vector<size_t> competitor_indices;

    for (int i = 0; i < competitor_count; ++i) {
      while (true) {
        int candidate = std::rand() % all_enemies.size();

        bool candidate_exists = false;

        for (size_t existing_index : competitor_indices) {
          if (existing_index == candidate) {
            candidate_exists = true;
            break;
          }
        }

        if (!candidate_exists) {
          competitor_indices.push_back(candidate);
          break;
        }
      }
    }

    std::vector<Food *> enemies;
    enemies.reserve(competitor_count);
    for (auto index : competitor_indices) {
      enemies.push_back(all_enemies[index]->clone());
    }

    // print number of enemies selected for this round
    std::cout << std::setw(10) << "Select"
              << " : ";
    enemies[0]->print_header(); // only print header of first entry to reduce
                                // output in InfoMark
    for (size_t i = 0; i < enemies.size(); i++) {
      std::cout << std::setw(10) << i << " : ";
      enemies[i]->print();
    }
    std::cout << "Choose your enemy (0-" << enemies.size() - 1 << "): ";

    unsigned int selection;
    std::cin >> selection;

    selection = selection % enemies.size();

    combat(&player, enemies[selection]);

    difficulty += 1.0;

    // free copies
    for (auto enemy : all_enemies) {
      delete enemy;
    }

    for (auto enemy : enemies) {
      delete enemy;
    }
  }

  std::cout << "Player reached difficulty level (round): " << difficulty
            << std::endl;
}
