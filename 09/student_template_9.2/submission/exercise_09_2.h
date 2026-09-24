// Simon Sutoris 7542170
// Eric Berger 7064584

#pragma once

#include <cstdlib>
#include <map>

void slow_producer();
void fast_producer();
void consumer(std::map<unsigned long, size_t> *diff_count);
