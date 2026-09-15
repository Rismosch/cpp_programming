#include "selection_sort.h"

#include <chrono>
#include <iostream>
#include <ratio>

using namespace std;

using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>;
using duration_ms = std::chrono::duration<double, std::milli>;

/* Constant array size of n = 5000 elements for testing purpose */
const int num_array_elements = 5000;

/* Generates an integer array with constant n=5000 elements */
int *generateArray(int from, int multStepFactor) {
  int *arr = new int[num_array_elements];
  for (int i = 0; i < num_array_elements; i++)
    arr[i] = from + multStepFactor * i;
  return arr;
}

/* Prints an integer array with n Elements to the console */
void printArray(int arr[], int nElements) {
  for (int i = 0; i < nElements; i++)
    cout << arr[i] << " ";
  cout << endl;
}

/// Selection sort algorithm sorts given integer array ascending with n
/// elements.
void selectionSort(int arr[], int nElements) {
  // TODO: implement selection sort with the use of the std::swap function
}

/* Test selection sort with two arrays containing 5000 elements ascending and
descending and print out the required time in ms.*/
void testSelectionSort() {
  int *ascSelectionTest = generateArray(1, 1);
  int *descSelectionTest = generateArray(num_array_elements, -1);

  const time_point start = std::chrono::high_resolution_clock::now();
  selectionSort(ascSelectionTest, num_array_elements);
  const time_point middle = std::chrono::high_resolution_clock::now();
  selectionSort(descSelectionTest, num_array_elements);
  const time_point end = std::chrono::high_resolution_clock::now();

  double ascSelectionTime = duration_ms(middle - start).count();
  double descSelectionTime = duration_ms(end - middle).count();

  cout << "Selection sorting time for n = " << num_array_elements << ":"
       << endl;
  cout << "Sorted ascending in " << ascSelectionTime << " ms." << endl;
  cout << "Sorted descending in " << descSelectionTime << " ms." << endl;

  delete[] ascSelectionTest;
  delete[] descSelectionTest;
}
