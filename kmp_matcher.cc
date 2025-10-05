// Copyright (c) 2025 David Faden (revfad.com)
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

// The code here follows:
// https://www-igm.univ-mlv.fr/~lecroq/string/node8.html
// and https://www.brics.dk/RS/02/32/BRICS-RS-02-32.pdf.

#include "kmp_matcher.h"

#include <algorithm>

namespace revfad {

KmpMatcher::KmpMatcher(std::string pattern)
    : pattern_(std::move(pattern)),
      pattern_len_(static_cast<int>(pattern_.size())), next_(pattern_len_ + 1) {
  initialize_next_table();
}

KmpMatcher::KmpMatcher(const KmpMatcher &&other)
    : pattern_(std::move(other.pattern_)), pattern_len_(other.pattern_len_),
      next_(std::move(other.next_)), position_(other.position_) {}

KmpMatcher &KmpMatcher::operator=(const KmpMatcher &&other) {
  if (this != &other) {
    this->pattern_ = std::move(other.pattern_);
    this->pattern_len_ = other.pattern_len_;
    this->next_ = std::move(other.next_);
  }
  return *this;
}

void KmpMatcher::initialize_next_table() {
  if (pattern_len_ == 0) {
    return;
  }
  next_[0] = -1;
  int i = 0;
  int t = -1;
  while (i < pattern_len_) {
    while (t > -1 && pattern_[i] != pattern_[t]) {
      t = next_[t];
    }
    ++t;
    ++i;
    next_[i] = (i < pattern_len_ && pattern_[i] == pattern_[t]) ? next_[t] : t;
  }
}

bool KmpMatcher::consume(char c) {
  if (pattern_len_ == 0) {
    return true;
  }
  while (position_ >= 0 && pattern_[position_] != c) {
    position_ = next_[position_];
  }
  ++position_;
  if (position_ == pattern_len_) {
    position_ = next_[position_];
    return true;
  }
  return false;
}

void KmpMatcher::reset() { position_ = 0; }

} // namespace revfad