// Eric Berger      7064584
// Simon Sutoris    7542170

#include "selection_sort.h"

#include <chrono>
#include <iostream>
#include <ratio>

using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>;
using duration_ms = std::chrono::duration<double, std::milli>;

///* Constant array size of n = 5000 elements for testing purpose */
// const int num_array_elements = 5000;

/* Generates an integer array with constant n=5000 elements */
int *generateArray(int start, int step, size_t count) {
  int *arr = new int[count];
  for (size_t i = 0; i < count; i++) {
    arr[i] = start + step * static_cast<int>(i);
  }
  return arr;
}

/* Prints an integer array with n Elements to the console */
void printArray(int arr[], size_t nElements) {
  for (size_t i = 0; i < nElements; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << "\n";
}

/// Selection sort algorithm sorts given integer array ascending with n
/// elements.
void selectionSort(int arr[], int nElements) {
  // implementation taken from:
  // https://en.wikipedia.org/wiki/Selection_sort#Implementations

  for (int i = 0; i < nElements; ++i) {
    int j_min = i;

    for (int j = i + 1; j < nElements; ++j) {
      if (arr[j] < arr[j_min]) {
        j_min = j;
      }
    }

    if (j_min != i) {
      std::swap(arr[i], arr[j_min]);
    }
  }
}

/* Test selection sort with two arrays containing 5000 elements ascending and
descending and print out the required time in ms.*/
void testSelectionSort() {
  size_t count = 50;
  int *array1 = generateArray(1, 1, count);
  int *array2 = generateArray(static_cast<int>(count), -1, count);

  std::cout << "array 1: ";
  printArray(array1, count);
  std::cout << "array 2: ";
  printArray(array2, count);

  const time_point start = std::chrono::high_resolution_clock::now();
  selectionSort(array1, static_cast<int>(count));
  const time_point middle = std::chrono::high_resolution_clock::now();
  selectionSort(array2, static_cast<int>(count));
  const time_point end = std::chrono::high_resolution_clock::now();

  double time1 = duration_ms(middle - start).count();
  double time2 = duration_ms(end - middle).count();

  std::cout << "Selection sorting time for n = " << count << ":\n";
  std::cout << "Sorted ascending in " << time1 << " ms.\n";
  std::cout << "Sorted descending in " << time2 << " ms.\n";

  std::cout << "array 1: ";
  printArray(array1, count);
  std::cout << "array 2: ";
  printArray(array2, count);

  delete[] array1;
  delete[] array2;
}
