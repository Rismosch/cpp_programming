// Simon Sutoris 7542170
// Eric Berger 7064584

#include "exercise_09_1.h"

#include <cstdint>
#include <iostream>
#include <map>
#include <mutex>
#include <random>
#include <stdexcept>
#include <thread>


// This are the item types
enum class Item { BOOK = 0, TOY = 1 };

/**
 * @brief Makes a random choice between Book and Toy.
 * A Book has 5x the chance to be sold compared to a toy.
 *
 * @return Item The item that should be sold.
 *
 * @thread_safety This function is fully threadsafe. No modifications were necessary. It only uses variable local to it's thread. It does not share memory, not even globally. Therefore, this method is safe to call in any thread without any synchronisation mechanisms.
 */
Item choose_what_to_sell() {
  static thread_local std::default_random_engine generator; // only local to this thread
  std::discrete_distribution<int> distribution({5, 1}); // local variable
  int choice = distribution(generator); // local variable
  return static_cast<Item>(choice);     // cast and return copy of the local variable
}

// please use these three mutexes to protect access to shared variables
std::mutex item_mutex;
std::mutex book_mutex;
std::mutex toy_mutex;

/**
 * @brief Sell a book
 *
 * @thread_safety This function is now full threadsafe. A mutex was added, to protect read-modify-write operations on shared memory. Due to the mutex, read-writes are now done synchronously, avoiding data races.
 */
void sell_book(Shop &shop) {
  const std::lock_guard<std::mutex> lock(item_mutex); // lock

  // shared read
  if (shop.books_on_stock <= 0) {
    throw std::runtime_error("Books are out of stock!");
  }

  // shared read-modify-write
  ++shop.sold_books;
  --shop.books_on_stock;
  ++shop.sold_items;
}

/**
 * @brief Sell a toy
 *
 * @thread_safety This function is now full threadsafe. A mutex was added, to protect read-modify-write operations on shared memory. Due to the mutex, read-writes are now done synchronously, avoiding data races.
 */
void sell_toy(Shop &shop) {
  const std::lock_guard<std::mutex> lock(item_mutex); // lock

  // shared read
  if (shop.toys_on_stock <= 0) {
    throw std::runtime_error("Toys are out of stock!");
  }

  // shared read-modify-write
  ++shop.sold_toys;
  --shop.toys_on_stock;
  ++shop.sold_items;
}

/**
 * @brief A salesperson keeps selling items.
 * When the store runs out of items she gets frustrated and quits.
 *
 * @thread_safety This function is now full threadsafe. On each loop, it only sells one item. Each operation (sell_toy, or sell_book) is already threadsafe, thus each iteration of the loop is threadsafe as well.
 */
void sell_stuff(Shop &shop) {
  while (true) {
    // randomly select what to sell
    try {
      //const std::lock_guard<std::mutex> lock(item_mutex); // lock is not required, because all following operations are threadsafe already
      if (choose_what_to_sell() == Item::TOY) { // threadsafe, generate random choice
        sell_toy(shop); // threadsafe
      } else {
        sell_book(shop); // threadsafe
      }
    } catch (std::runtime_error &exception) {
      std::cout << exception.what() << " Salesperson is frustrated and quits!"
                << std::endl;
      break;
    }
  }
}
