// Copyright (c) 2025 David Faden (revfad.com)
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include "naive_matcher.h"

#include <algorithm>
#include <cstring>

namespace revfad {

NaiveStringMatcher::NaiveStringMatcher(std::string pattern)
    : pattern_(std::move(pattern)),
      pattern_len_(static_cast<int>(pattern_.size())) {
  buffer_.reserve(pattern_len_);
}

NaiveStringMatcher::NaiveStringMatcher(const NaiveStringMatcher &&other)
    : pattern_(std::move(other.pattern_)), pattern_len_(other.pattern_len_),
      buffer_(std::move(other.buffer_)), position_(other.position_),
      full_(other.full_) {}

NaiveStringMatcher &
NaiveStringMatcher::operator=(const NaiveStringMatcher &&other) {
  if (this != &other) {
    this->pattern_ = std::move(other.pattern_);
    this->pattern_len_ = other.pattern_len_;
    this->buffer_ = std::move(other.buffer_);
    this->position_ = other.position_;
    this->full_ = other.full_;
  }
  return *this;
}

bool NaiveStringMatcher::consume(char c) {
  if (pattern_len_ == 0) {
    return true;
  }
  position_ = (position_ + 1) % pattern_len_;
  if (!full_) {
    buffer_.push_back(c);
    full_ = position_ + 1 == pattern_len_;
    if (!full_) {
      return false;
    }
  } else {
    buffer_[position_] = c;
  }
  int first = (position_ + 1) % pattern_len_;
  if (first == 0) {
    return pattern_ == buffer_;
  } else {
    int n = pattern_len_ - first;
    const char *pattern_data = pattern_.data();
    const char *buffer_data = buffer_.data();
    // Note: first = position_ + 1 so that n = pattern_len_ - position_ - 1.
    // So, the two segments being compared have total length = pattern_len_.
    return (std::strncmp(pattern_data, buffer_data + first, n) == 0) &&
           (std::strncmp(pattern_data + n, buffer_data, position_ + 1) == 0);
  }
}

void NaiveStringMatcher::reset() {
  position_ = -1;
  buffer_.clear();
  full_ = false;
}

} // namespace revfad