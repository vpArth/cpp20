#pragma once

#include "generator.hpp"

#include <iterator>
using std::incrementable;


template <incrementable T>
Generator<T> range(const T start, const T stop, const int step = 1) {
  const int dir = step > 0 ? 1 : -1;
  for (auto value = start, _stop = dir*stop; dir*value < _stop; value += step) {
    co_yield value;
  }
}
template <incrementable T>
Generator<T> range(const T stop) { return range<T>(T{0}, stop); }
