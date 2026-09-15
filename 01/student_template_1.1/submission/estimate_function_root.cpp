// estimate_function_root.cpp - student template:
// Estimate the root (or x) of a given linear function, that is, f(x) = 0 using
// intervall bisection.
#include <cmath>
#include <iostream>
#include <stdio.h>

/* Given: increasing linear function to test f(x)=32*x-1 */
float exampleIncreasingLinearFunc(float x) { return 32 * x - 1; }

/* Given: decreasing linear function to test f(x)=-32*x-1 */
float exampleDecreasingLinearFunc(float x) { return -32 * x - 1; }

/* returns increasing numbers */
float verticalFunc(float) {
  static float y = 1.0f;
  y += 1;
  return y;
}

/* returns a constant */
float horizontalFunc(float) { return 5.0f; }

/* Rounds a float value to n decimal places. E.g. val=1.555, n=2 returns 1.56*/
float roundValToNDecimals(float val, unsigned int n) {
  double t = std::pow(10, n);
  double promoted = static_cast<double>(val);
  double result = std::round(t * promoted) / t;
  return static_cast<float>(result);
}

/* Returns true if the absolute difference of x1 and x2 is smaller or equal than
a given epsilon, otherwise returns false. Default epsilon checks for 5 decimal
precision.*/
bool isAlmostEqual(float x1, float x2, float epsilon = 1.0e-5f) {
  return std::abs(x1 - x2) <= epsilon;
}

/* Estimates the root, the x, of the linear function that is f(x)=0 within the
specified interval [xLower, xUpper]. If the root is equal to the interval bounds
or the midpoint it returns the corresponding x-value. If the root is estimated
(the intervall becomes small enough) the resulting x-value is rounded to n
decimal places. If linear function in the specified interval does not have a
root, it returns NAN. */
float estimateFunctionRoot(float (*linearFunc)(float), float xLower,
                           float xUpper, unsigned int nDecimals) {
  float x1 = std::min(xLower, xUpper);
  float x2 = std::max(xLower, xUpper);
  float y1 = linearFunc(x1);
  float y2 = linearFunc(x2);

  // check if the interval boundaries are the root
  if (isAlmostEqual(y1, 0.0f)) {
    return x1;
  }

  if (isAlmostEqual(y2, 0.0f)) {
    return x2;
  }

  // interval boundaries are not the root. estimate...
  // visualization: https://www.desmos.com/calculator/xuu37bzi8v

  // sanity checks
  if (isAlmostEqual(x1, x2)) {
    // the interval is degenerate
    return NAN;
  }

  if (isAlmostEqual(y1, y2)) {
    // the line is horizontal: it does not intersect the x axis
    return NAN;
  }

  // find `m` and `c` for `y = m * x + c`
  float m = (y2 - y1) / (x2 - x1);
  float c = y1 - m * x1;

  // find root `0 = m * x + c <=> - c / m = x`
  float root = -c / m;

  // if the root is outside the range, return NAN
  if (root < x1 || root > x2) {
    return NAN;
  }

  // round
  float result = roundValToNDecimals(root, nDecimals);
  return result;
}

/* Calls estimateFunctionRoot of increasing example function with the specified
 * interval [lowerBound; upperBound] and prints out the result. */
void testAndPrintIncreasing(float xLower, float xUpper,
                            unsigned int nDecimals = 5) {
  float result = estimateFunctionRoot(&exampleIncreasingLinearFunc, xLower,
                                      xUpper, nDecimals);
  std::cout << "interval [" << xLower << ", " << xUpper
            << "], \t result = " << result << "\n";
}

/* Calls estimateFunctionRoot of decreasing example function with the specified
 * interval [lowerBound; upperBound] and prints out the result. */
void testAndPrintDecreasing(float xLower, float xUpper,
                            unsigned int nDecimals = 5) {
  float result = estimateFunctionRoot(&exampleDecreasingLinearFunc, xLower,
                                      xUpper, nDecimals);
  std::cout << "interval [" << xLower << ", " << xUpper
            << "], \t result = " << result << "\n";
}

/* Test your implementation */
void testEstimateFunctionRoot() {
  // Test 1a) Round up with 1 decimal, round down with 1 decimal, round with 4
  // decimal precision
  std::cout << "1a)\n";
  std::cout << "Round 1.55 to 1 decimal: " << roundValToNDecimals(1.55f, 1)
            << ", expected: " << 1.6 << "\n";
  std::cout << "Round 1.54 to 1 decimal: " << roundValToNDecimals(1.54f, 1)
            << ", expected: " << 1.5 << "\n\n";

  // Test 1b) abs(x1 - x2) <= epsilon
  // x1 = 0.1, x2 = 0.11, decimal precision (epsilon) varies
  std::cout << "1b)\n";
  std::cout
      << "Is x1 = 0.1 almost equal to x2 = 0.11 with 1 decimal precision?: "
      << isAlmostEqual(0.1f, 0.11f, 0.1f) << ", expected: "
      << "1"
      << "\n";
  std::cout
      << "Is x1 = 0.1 almost equal to x2 = 0.11 with 2 decimal precision?: "
      << isAlmostEqual(0.1f, 0.11f, 1e-2f) << ", expected: "
      << "1"
      << "\n";
  std::cout
      << "Is x1 = 0.1 almost equal to x2 = 0.11 with 3 decimal precision?: "
      << isAlmostEqual(0.1f, 0.11f, 1e-3f) << ", expected: "
      << "0"
      << "\n\n";

  // Precision with 5 decimals (default of function)
  std::cout << "Is x1 = 0.00001 almost equal to x2 = 0.000019 with 5 decimal "
               "precision?: "
            << isAlmostEqual(0.00001f, 0.000019f) << ", expected: "
            << "1"
            << "\n";
  std::cout << "Is x1 = 0.00001 almost equal to x2 = 0.00002 with 5 decimal "
               "precision?: "
            << isAlmostEqual(0.00001f, 0.00002f) << ", expected: "
            << "1"
            << "\n";
  std::cout << "Is x1 = 0.00001 almost equal to x2 = 0.000021 with 5 decimal "
               "precision?: "
            << isAlmostEqual(0.00001f, 0.000021f) << ", expected: "
            << "0"
            << "\n\n";

  // Test 1c) Estimate rounded
  std::cout << "1c)\n";
  testAndPrintIncreasing(0.01f, 1.5f);
  std::cout << "check inverted parameters...\n";
  testAndPrintIncreasing(0.15f, 0.01f);
  std::cout << "\n";

  // Test 1d) Special cases: xUpper, xLower, midPoint (no rounding necessary)
  // f(x) = 0 for x = xUpper
  std::cout << "1d)\n";
  testAndPrintIncreasing(0.0f, 0.03125f);

  // f(x) = 0 for x = xLower
  testAndPrintIncreasing(0.03125f, 1.0f);

  // f(x) = 0 for x = midpoint = (xUpper - xLower)/2
  testAndPrintIncreasing(0.0f, 0.03125f * 2.0f);
  std::cout << "\n";

  // Test 1e) Special case: no root found, return NAN
  std::cout << "1e)\n";
  testAndPrintIncreasing(0.0f, 0.02f);
  std::cout << "\n";

  // Test 1f) Test decreasing function as well
  std::cout << "1f)\n";
  testAndPrintDecreasing(-1.0f, 1.0f);
  std::cout << "\n";

  // Test rounding
  std::cout << "1f)\n";
  testAndPrintIncreasing(0.01f, 1.5f, 2);
  testAndPrintDecreasing(-1.0f, 1.0f, 2);
  std::cout << "\n";

  // Test horizontal line
  std::cout << "horizontal)\n";
  float horizontal_result = estimateFunctionRoot(horizontalFunc, 1.0f, 1.0f, 5);
  std::cout << "result: " << horizontal_result << "\n";
  std::cout << "\n";

  // Test vertical line
  std::cout << "vertical)\n";
  float vertical_result = estimateFunctionRoot(verticalFunc, 0.0f, 2.0f, 5);
  std::cout << "result: " << vertical_result << "\n";
  std::cout << "\n";
}
