// Copyright 2025 NNTU-CS
#include "alg.h"
#include <cstdint>
#include <algorithm>
#include <unordered_map>

static std::unordered_map<uint64_t, unsigned int> len_cache;
static std::unordered_map<uint64_t, uint64_t> max_cache;

unsigned int collatzLen(uint64_t num) {
  if (num == 1) return 1;
  auto it = len_cache.find(num);
  if (it != len_cache.end()) return it->second;

  unsigned int len;
  if (num % 2 == 0) {
    len = 1 + collatzLen(num / 2);
  } else {
    len = 1 + collatzLen(3 * num + 1);
  }
  len_cache[num] = len;
  return len;
}

uint64_t collatzMaxValue(uint64_t num) {
  if (num == 1) return 1;
  auto it = max_cache.find(num);
  if (it != max_cache.end()) return it->second;

  uint64_t next;
  if (num % 2 == 0) {
    next = num / 2;
  } else {
    next = 3 * num + 1;
  }
  uint64_t max_val = std::max(num, collatzMaxValue(next));
  max_cache[num] = max_val;
  return max_val;
}

unsigned int seqCollatz(unsigned int *maxlen, uint64_t lbound,
                        uint64_t rbound) {
  unsigned int best_num = 0;
  unsigned int best_len = 0;
  for (uint64_t i = lbound; i <= rbound; ++i) {
    unsigned int len = collatzLen(i);
    if (len > best_len) {
      best_len = len;
      best_num = static_cast<unsigned int>(i);
    }
  }
  *maxlen = best_len;
  return best_num;
}
