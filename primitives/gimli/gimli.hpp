#pragma once
#include <array>
#include <cstdint>
namespace Gimli {
using GimliState = std::array<uint32_t, 12>;
template <class Algorithm, typename StateType, size_t n_rounds>
class Gimli {
  uint32_t rotate(uint32_t word, uint8_t nbits) {
    return (word << nbits) | (word >> (32 - nbits));
  }

 public:
  void permutation(StateType& state) {
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t z = 0;

    for (auto round = n_rounds; round > 0; --round) {
      for (auto column = 0; column < 4; ++column) {
        x = rotate(state[column], 24);
        y = rotate(state[4 + column], 9);
        z = state[8 + column];
        state[8 + column] = x ^ (z << 1) ^ ((y & z) << 2);
        state[4 + column] = y ^ x ^ ((x | z) << 1);
        state[column] = z ^ y ^ ((x & y) << 3);
      }
      if ((round & 3) == 0) {
        x = state[0];
        state[0] = state[1];
        state[1] = x;
        x = state[2];
        state[2] = state[3];
        state[3] = x;
      }
      if ((round & 3) == 2) {
        x = state[0];
        state[0] = state[2];
        state[2] = x;
        x = state[1];
        state[1] = state[3];
        state[3] = x;
      }
      if ((round & 3) == 0) {
        state[0] ^= (0x9e377900 | round);
      }
    }
  }
};
}  // namespace Gimli
