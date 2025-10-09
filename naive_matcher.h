// Copyright (c) 2025 David Faden (revfad.com)
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#ifndef COM_REVFAD_NAIVE_MATCHER_H_
#define COM_REVFAD_NAIVE_MATCHER_H_

#include <string>
#include <vector>

namespace revfad {

// Matches against a stream of chars using a naive string matching algorithm.
class NaiveStringMatcher {
public:
  explicit NaiveStringMatcher(std::string pattern);

  // Supports copying and moving.
  NaiveStringMatcher(const NaiveStringMatcher &) = default;
  NaiveStringMatcher &operator=(const NaiveStringMatcher &) = default;
  NaiveStringMatcher(const NaiveStringMatcher &&);
  NaiveStringMatcher &operator=(const NaiveStringMatcher &&);

  // Consume a single char and return whether it completes a match.
  bool consume(char c);
  // Reset the matcher back to its original state, as before consuming any
  // chars.
  void reset();
  // Convenience method to return the length of the pattern being searched for.
  int size() const { return pattern_len_; }

private:
  std::string pattern_;
  int pattern_len_;
  // Used as a circular buffer.
  std::string buffer_;
  // Most recent position inserted into.
  int position_ = -1;
  // Whether the buffer is full.
  bool full_ = false;
};

} // namespace revfad

#endif // COM_REVFAD_NAIVE_MATCHER_H_