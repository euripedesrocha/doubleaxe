#pragma once
#include <array>
#include <cstdint>
namespace Gimli {
using State = std::array<uint32_t, 12>;

uint32_t rotate(uint32_t word, uint8_t nbits);
void permutation(State& state);
}  // namespace Gimli
