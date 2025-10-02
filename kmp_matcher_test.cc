// Copyright (c) 2025 David Faden (revfad.com)
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include "kmp_matcher.h"

namespace revfad {
namespace {
TEST(KmpMatcherTest, EmptyPattern) {
  KmpMatcher matcher("");
  ASSERT_EQ(0, matcher.size());
  ASSERT_TRUE(matcher.consume('x'));
  matcher.reset();
  ASSERT_TRUE(matcher.consume('y'));
}

TEST(KmpMatcherTest, CharSequence) {
  KmpMatcher matcher("abc");
  ASSERT_FALSE(matcher.consume('a'));
  ASSERT_FALSE(matcher.consume('b'));
  ASSERT_FALSE(matcher.consume('d'));
  ASSERT_FALSE(matcher.consume('a'));
  ASSERT_FALSE(matcher.consume('b'));
  ASSERT_TRUE(matcher.consume('c'));
  ASSERT_FALSE(matcher.consume('c'));
}

TEST(KmpMatcherTest, CharSequenceWithReset) {
  KmpMatcher matcher("abc");
  ASSERT_EQ(3, matcher.size());
  ASSERT_FALSE(matcher.consume('a'));
  ASSERT_FALSE(matcher.consume('b'));
  matcher.reset();
  ASSERT_FALSE(matcher.consume('c'));
  ASSERT_FALSE(matcher.consume('a'));
  ASSERT_FALSE(matcher.consume('b'));
  ASSERT_TRUE(matcher.consume('c'));
}

TEST(KmpMatcherTest, Mama) {
  KmpMatcher matcher("mama");
  ASSERT_EQ(4, matcher.size());
  ASSERT_FALSE(matcher.consume('a'));
  ASSERT_FALSE(matcher.consume('m'));
  ASSERT_FALSE(matcher.consume('m'));
  ASSERT_FALSE(matcher.consume('a'));
  ASSERT_FALSE(matcher.consume('m'));
  ASSERT_TRUE(matcher.consume('a'));
  ASSERT_FALSE(matcher.consume('a'));
}

TEST(KmpMatcherTest, SingleChar) {
  KmpMatcher matcher("x");
  ASSERT_EQ(1, matcher.size());
  ASSERT_FALSE(matcher.consume('a'));
  ASSERT_TRUE(matcher.consume('x'));
  ASSERT_FALSE(matcher.consume('d'));
  ASSERT_TRUE(matcher.consume('x'));
  ASSERT_FALSE(matcher.consume('b'));
  ASSERT_TRUE(matcher.consume('x'));
  ASSERT_FALSE(matcher.consume('c'));
}

TEST(KmpMatcherTest, RepeatedChars) {
  KmpMatcher matcher("aaa");
  ASSERT_EQ(3, matcher.size());
  ASSERT_FALSE(matcher.consume('a'));
  ASSERT_FALSE(matcher.consume('a'));
  ASSERT_TRUE(matcher.consume('a'));
  ASSERT_TRUE(matcher.consume('a'));
  ASSERT_TRUE(matcher.consume('a'));
}

} // namespace
} // namespace revfad