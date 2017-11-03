#include "gimli.hpp"

namespace Gimli {
uint32_t rotate(uint32_t word, uint8_t nbits) {
  return (word << nbits) | (word >> (32 - nbits));
}
void permutation(GimliState& state);
}  // namespace Gimli
