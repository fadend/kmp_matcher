// Copyright (c) 2025 David Faden (revfad.com)
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#ifndef COM_REVFAD_KMP_MATCHER_H_
#define COM_REVFAD_KMP_MATCHER_H_

#include <string>
#include <vector>

namespace revfad {

// Allows for efficient matching of a pattern against a stream of characters.
//
// Uses the Knuth-Morris-Pratt Algorithm to achieve time linear in the length
// of the pattern and the stream of chars examined.
class KmpMatcher {
public:
  KmpMatcher(std::string pattern);

  // Consume a single char and return whether it completes a match.
  bool consume(char c);
  // Reset the matcher back to its original state, as before consuming any
  // chars.
  void reset();
  // Convenience method to return the length of the pattern being searched for.
  int size() const { return pattern_len_; }

private:
  const std::string pattern_;
  const int pattern_len_;
  std::vector<int> next_;
  int position_ = 0;

  void initialize_next_table();
};

} // namespace revfad

#endif // COM_REVFAD_KMP_MATCHER_H_