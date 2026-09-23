// Simon Sutoris 7542170
// Eric Berger 7064584

#include "exercise_09_2.h"

// IO
#include <iostream>

// random number generators
#include <random>

// threading
#include <thread>
#include <mutex>
#include <condition_variable>

// data structures
#include <map>
#include <queue>

using namespace std;

std::mt19937 delay_generator;
std::mt19937 slow_generator{}, fast_generator{};
std::mutex slow_mutex{}, fast_mutex{};
std::queue<long unsigned int> slow_queue{}, fast_queue{};
std::condition_variable fast_cond, slow_cond;

thread_local unsigned int execution_count = 0;

// every 0 to 200 ms, slow_producer generates a random number and notifies other threads via condition variable.
void slow_producer() {
  while (execution_count < 20) { // every thread generates 20 numbers
	{
		std::scoped_lock<std::mutex> ul(slow_mutex);
		slow_queue.push(slow_generator() % 100 + 1);
	} // end of scope releases lock
    execution_count++;
    slow_cond.notify_one();
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_generator() % 200));
  }
}

// every 0 to 20 ms, fast_producer generates a random number and notifies other threads via condition variable.
void fast_producer() {
  while (execution_count < 20) { // every thread generates 20 numbers
	{
		std::scoped_lock<std::mutex> ul(fast_mutex);
		fast_queue.push(fast_generator() % 100 + 1);
	} // end of scope releases lock
    execution_count++;
    fast_cond.notify_one();
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_generator() % 20));
  }
}

// consumer thread function processes input once it get's available
void consumer(std::map<unsigned long, size_t> *diff_count) {
  while (execution_count < 20) {

  long unsigned int slow_data;
  long unsigned int fast_data;

  {
    std::unique_lock<std::mutex> lock(slow_mutex);
    slow_cond.wait(lock, [](){return !slow_queue.empty();});
    slow_data = slow_queue.front();
    slow_queue.pop();
  }

  {
    std::unique_lock<std::mutex> lock(fast_mutex);
    fast_cond.wait(lock, [](){return !fast_queue.empty();});
	  fast_data = fast_queue.front();
	  fast_queue.pop();
  }

    // count how often differences between a and b occur
    (*diff_count)[slow_data - fast_data]++;
    execution_count++;
  }
}
