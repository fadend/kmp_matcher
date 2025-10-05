cc_library(
  name="kmp_matcher",
  srcs=["kmp_matcher.cc"],
  hdrs=["kmp_matcher.h"],
)

# Tests

cc_test(
  name="kmp_matcher_test",
  srcs=["kmp_matcher_test.cc"],
  deps=[
    ":kmp_matcher",
    "@googletest//:gtest",
    "@googletest//:gtest_main",
    ],
  size="small"
)
