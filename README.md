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

## Requirements

Formatted with `clang-format`.

This project uses Bazel for builds: https://bazel.build/.
