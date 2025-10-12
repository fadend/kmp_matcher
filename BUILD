cc_library(
    name = "kmp_matcher",
    srcs = ["kmp_matcher.cc"],
    hdrs = ["kmp_matcher.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "naive_matcher",
    srcs = ["naive_matcher.cc"],
    hdrs = ["naive_matcher.h"],
)

# Tests

cc_test(
    name = "kmp_matcher_test",
    size = "small",
    srcs = ["kmp_matcher_test.cc"],
    deps = [
        ":kmp_matcher",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "naive_matcher_test",
    size = "small",
    srcs = ["naive_matcher_test.cc"],
    deps = [
        ":naive_matcher",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

# Benchmarks

cc_test(
    name = "kmp_matcher_benchmark",
    srcs = ["kmp_matcher_benchmark.cc"],
    deps = [
        ":kmp_matcher",
        ":naive_matcher",
        "@google_benchmark//:benchmark_main",
    ],
)
