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
----------------------------------------------------------------------------
Benchmark                                  Time             CPU   Iterations
----------------------------------------------------------------------------
BM_KmpMatcherFibonacci/4                48.1 ns         47.9 ns     15219476
BM_KmpMatcherFibonacci/8                 167 ns          167 ns      4146060
BM_KmpMatcherFibonacci/16               2586 ns         2584 ns       271122
BM_KmpMatcherFibonacci/32            5190927 ns      5102696 ns          138
BM_NaiveStringMatcherFibonacci/4        50.2 ns         48.2 ns     14820116
BM_NaiveStringMatcherFibonacci/8         193 ns          192 ns      3525702
BM_NaiveStringMatcherFibonacci/16       6579 ns         6541 ns       103718
BM_NaiveStringMatcherFibonacci/32   14795181 ns     14725915 ns           47
```

These numbers are from running on a MacBook M3 with
Apple clang version 17.0.0 (clang-1700.3.19.1).

## Requirements

Formatted with `clang-format`.

This project uses Bazel for builds: https://bazel.build/.

## Acknowledgments

Thank you to [Jakub Slys](https://github.com/jakub-k-slys) for the helpful
example on how to use [Google Benchmark](https://github.com/google/benchmark)
with Bazel: https://github.com/jakub-k-slys/bazel-cpp-sandbox/blob/main/benchmark/.

Thank you to Prof. Charras and Prof. Lecroq for the most helpful exposition of
KMP: https://www-igm.univ-mlv.fr/~lecroq/string/node8.html.