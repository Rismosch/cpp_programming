// Simon Sutoris 7542170
// Eric Berger 7064584

#pragma once
#include <vector>
#include <functional>

// TODO 7.1.a: Implement the square function
template<typename T>
T square(T x) {
    return x * x;
}

// TODO 7.1.b: Implement the halve function
template<typename T>
double halve(T x) {
    return static_cast<double>(x) / 2.0;
}

// TODO 7.1.c: Implement the add function
template<typename T>
T add(T x, T y) {
    return x + y;
}

// TODO 7.1.d: Implement the multiply function
template<typename T>
T multiply(T x, T y) {
    return x * y;
}

// TODO 7.1.d: Implement the reduce function
template<typename T>
T reduce(std::function<T(T, T)> f, std::vector<T> vec, T neutral) {
    T value = neutral;
    for (const T& element : vec) {
        value = f(value, element);
    }
    return value;
}

// TODO 7.1.f: Implement the map function
template<typename T>
std::vector<T> map(std::function<T(T)> f, std::vector<T> vec) {
    std::vector<T> result_vec;
    for (const T& element : vec) {
        result_vec.push_back(f(element));
    }
    return result_vec;
}