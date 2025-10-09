// Copyright (c) 2025 David Faden (revfad.com)
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include "gtest/gtest.h"

#include "naive_matcher.h"

namespace revfad {
namespace {
TEST(NaiveStringMatcherTest, EmptyPattern) {
  NaiveStringMatcher matcher("");
  ASSERT_EQ(0, matcher.size());
  ASSERT_TRUE(matcher.consume('x'));
  matcher.reset();
  ASSERT_TRUE(matcher.consume('y'));
}

TEST(NaiveStringMatcherTest, CharSequence) {
  NaiveStringMatcher matcher("abc");
  ASSERT_FALSE(matcher.consume('a'));
  ASSERT_FALSE(matcher.consume('b'));
  ASSERT_FALSE(matcher.consume('d'));
  ASSERT_FALSE(matcher.consume('a'));
  ASSERT_FALSE(matcher.consume('b'));
  ASSERT_TRUE(matcher.consume('c'));
  ASSERT_FALSE(matcher.consume('c'));
}

TEST(NaiveStringMatcherTest, MoveCtor) {
  NaiveStringMatcher matcher1("abc");
  ASSERT_FALSE(matcher1.consume('a'));
  ASSERT_FALSE(matcher1.consume('b'));
  NaiveStringMatcher matcher2(std::move(matcher1));
  ASSERT_EQ(3, matcher2.size());
  ASSERT_TRUE(matcher2.consume('c'));
}

TEST(NaiveStringMatcherTest, MoveOp) {
  NaiveStringMatcher matcher1("abc");
  ASSERT_FALSE(matcher1.consume('a'));
  ASSERT_FALSE(matcher1.consume('b'));
  NaiveStringMatcher matcher2 = std::move(matcher1);
  ASSERT_EQ(3, matcher2.size());
  ASSERT_TRUE(matcher2.consume('c'));
}

TEST(NaiveStringMatcherTest, CharSequenceWithReset) {
  NaiveStringMatcher matcher("abc");
  ASSERT_EQ(3, matcher.size());
  ASSERT_FALSE(matcher.consume('a'));
  ASSERT_FALSE(matcher.consume('b'));
  matcher.reset();
  ASSERT_FALSE(matcher.consume('c'));
  ASSERT_FALSE(matcher.consume('a'));
  ASSERT_FALSE(matcher.consume('b'));
  ASSERT_TRUE(matcher.consume('c'));
}

TEST(NaiveStringMatcherTest, Mama) {
  NaiveStringMatcher matcher("mama");
  ASSERT_EQ(4, matcher.size());
  ASSERT_FALSE(matcher.consume('a'));
  ASSERT_FALSE(matcher.consume('m'));
  ASSERT_FALSE(matcher.consume('m'));
  ASSERT_FALSE(matcher.consume('a'));
  ASSERT_FALSE(matcher.consume('m'));
  ASSERT_TRUE(matcher.consume('a'));
  ASSERT_FALSE(matcher.consume('a'));
}

TEST(NaiveStringMatcherTest, SingleChar) {
  NaiveStringMatcher matcher("x");
  ASSERT_EQ(1, matcher.size());
  ASSERT_FALSE(matcher.consume('a'));
  ASSERT_TRUE(matcher.consume('x'));
  ASSERT_FALSE(matcher.consume('d'));
  ASSERT_TRUE(matcher.consume('x'));
  ASSERT_FALSE(matcher.consume('b'));
  ASSERT_TRUE(matcher.consume('x'));
  ASSERT_FALSE(matcher.consume('c'));
}

TEST(NaiveStringMatcherTest, RepeatedChars) {
  NaiveStringMatcher matcher("aaa");
  ASSERT_EQ(3, matcher.size());
  ASSERT_FALSE(matcher.consume('a'));
  ASSERT_FALSE(matcher.consume('a'));
  ASSERT_TRUE(matcher.consume('a'));
  ASSERT_TRUE(matcher.consume('a'));
  ASSERT_TRUE(matcher.consume('a'));
}

} // namespace
} // namespace revfad