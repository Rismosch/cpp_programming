// Eric Berger      7064584
// Simon Sutoris    7542170

#include "insertion_sort.h"

#include <chrono>
#include <iostream>
#include <memory>
#include <ratio>

using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>;
using duration_ms = std::chrono::duration<double, std::milli>;

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

/// Insertion sort algorithm sorts given integer array ascending with n
/// elements.
void insertionSort(int arr[], int nElements) {
  int i = 1;
  while (i < nElements) {
    int j = i;
    while (j > 0 && arr[j - 1] > arr[j]) {
      std::swap(arr[j], arr[j - 1]);
      j -= 1;
    }

    i += 1;
  }
}

/* Test insertion sort with two arrays containing 5000 elements ascending and
descending and print out the required time in ms.*/
void testInsertionSort() {
  size_t count = 50;
  int *array1 = generateArray(1, 1, count);
  int *array2 = generateArray(static_cast<int>(count), -1, count);

  std::cout << "array 1: ";
  printArray(array1, count);
  std::cout << "array 2: ";
  printArray(array2, count);

  const time_point start = std::chrono::high_resolution_clock::now();
  insertionSort(array1, static_cast<int>(count));
  const time_point middle = std::chrono::high_resolution_clock::now();
  insertionSort(array2, static_cast<int>(count));
  const time_point end = std::chrono::high_resolution_clock::now();

  double time1 = duration_ms(middle - start).count();
  double time2 = duration_ms(end - middle).count();

  std::cout << "Insertion sorting time for n = " << count << ":\n";
  std::cout << "Sorted ascending in " << time1 << " ms.\n";
  std::cout << "Sorted descending in " << time2 << " ms.\n";

  std::cout << "array 1: ";
  printArray(array1, count);
  std::cout << "array 2: ";
  printArray(array2, count);

  delete[] array1;
  delete[] array2;
}
