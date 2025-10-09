// Copyright (c) 2025 David Faden (revfad.com)
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

// Example run:
//   bazel run -c opt :kmp_matcher_benchmark

#include <algorithm>
#include <array>
#include <iostream>
#include <string>

#include "benchmark/benchmark.h"
#include "kmp_matcher.h"
#include "naive_matcher.h"

std::array<std::string, 3> last_3_fibonacci(int n) {
  // We'll use this as a circular buffer while building up the strings,
  // then
  std::array<std::string, 3> result = {"a", "b", ""};
  // Pre-condition: i (mod 3) = last index written to.
  int i = 1;
  do {
    ++i;
    std::string &next = result[i % 3];
    const std::string &minus1 = result[(i - 1) % 3];
    const std::string &minus2 = result[(i - 2) % 3];
    next.clear();
    next.reserve(minus1.size() + minus2.size());
    next.append(minus1);
    next.append(minus2);
  } while (i < n - 1);
  // Rearrange the result array to be ordered increasing by index in the
  // sequence.
  std::rotate(result.begin(), result.begin() + ((i - 2) % 3), result.end());
  return result;
}

static void BM_KmpMatcherFibonacci(benchmark::State &state) {
  for (auto _ : state) {
    auto fib = last_3_fibonacci(state.range(0));
    revfad::KmpMatcher matcher(fib[0]);
    for (const auto c : fib[2]) {
      matcher.consume(c);
    }
  }
}

static void BM_NaiveStringMatcherFibonacci(benchmark::State &state) {
  for (auto _ : state) {
    auto fib = last_3_fibonacci(state.range(0));
    revfad::NaiveStringMatcher matcher(fib[0]);
    for (const auto c : fib[2]) {
      matcher.consume(c);
    }
  }
}

BENCHMARK(BM_KmpMatcherFibonacci)->RangeMultiplier(2)->Range(4, 32);
BENCHMARK(BM_NaiveStringMatcherFibonacci)->RangeMultiplier(2)->Range(4, 32);;

BENCHMARK_MAIN();