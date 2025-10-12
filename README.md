# Efficient matching of a stream of chars

This package provides `KmpMatcher`, which uses the
[Knuth-Morris-Pratt algorithm](https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm)
to provide efficient matching of a given pattern (linear in the length of the
pattern and stream of chars).

For example, this might be useful when looking for a match for a pattern in a
stream of chars from a file too large to fit within memory.

This software is released under an MIT license courtesy of
"Reverse Fad Productions" (revfad.com, aka David Faden).

## Running tests

```
bazel test :kmp_matcher_test --test_output=all
```

## Benchmarks

These are still a work-in-progress but still hopefully give a useful baseline.
Comparing agaist a naive implementation of naive matching:

```
% bazel run -c opt :kmp_matcher_benchmark
...
--------------------------------------------------------------------------------
Benchmark                                      Time             CPU   Iterations
--------------------------------------------------------------------------------
BM_KmpMatcherFibonacci/4                    41.2 ns         41.2 ns     16723806
BM_KmpMatcherFibonacci/8                     135 ns          135 ns      5084586
BM_KmpMatcherFibonacci/16                   2236 ns         2236 ns       315236
BM_KmpMatcherFibonacci/32                4164735 ns      4164732 ns          168
BM_NaiveStringMatcherFibonacci/4            41.5 ns         41.5 ns     17155433
BM_NaiveStringMatcherFibonacci/8             173 ns          173 ns      3991948
BM_NaiveStringMatcherFibonacci/16           5947 ns         5947 ns       113192
BM_NaiveStringMatcherFibonacci/32       13197689 ns     13197686 ns           51
BM_KmpMatcherAaaaaaaa/4                     40.1 ns         40.1 ns     20411912
BM_KmpMatcherAaaaaaaa/128                    200 ns          200 ns      3477138
BM_KmpMatcherAaaaaaaa/16384                20489 ns        20489 ns        34258
BM_KmpMatcherAaaaaaaa/1048576            1306258 ns      1306259 ns          536
BM_NaiveStringMatcherAaaaaaaa/4             18.4 ns         18.4 ns     38011251
BM_NaiveStringMatcherAaaaaaaa/128            701 ns          700 ns      1001316
BM_NaiveStringMatcherAaaaaaaa/16384        87924 ns        87924 ns         7940
BM_NaiveStringMatcherAaaaaaaa/1048576    5621758 ns      5621766 ns          124
```

These numbers are from running on a MacBook M3 with
Apple clang version 17.0.0 (clang-1700.3.19.1).

## Requirements

Formatted with `clang-format` and [`buildifier`](https://github.com/bazelbuild/buildtools/blob/main/buildifier/README.md).

This project uses Bazel for builds: https://bazel.build/.

## Acknowledgments

Thank you to [Jakub Slys](https://github.com/jakub-k-slys) for the helpful
example on how to use [Google Benchmark](https://github.com/google/benchmark)
with Bazel: https://github.com/jakub-k-slys/bazel-cpp-sandbox/blob/main/benchmark/.

Thank you to Prof. Charras and Prof. Lecroq for the most helpful exposition of
KMP: https://www-igm.univ-mlv.fr/~lecroq/string/node8.html.