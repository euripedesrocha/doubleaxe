#include <algorithm>
#include <random>
#include "catch.hpp"
#include "sponge.hpp"

using SwapState = std::array<uint32_t, 12>;
template <>
void Sponge::Sponge<SwapState>::permutate() {}

void fillAndPad(SwapState& data) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uint32_t> rand_uint32;
  std::generate(std::begin(data), std::end(data),
                [&]() { return rand_uint32(gen); });
}

SCENARIO("A sponge will be used with an arbitrary permutation", "[SPONGE]") {
  constexpr std::size_t bitRate = 6 * 32;
  Sponge::Sponge<SwapState> sponge{bitRate};
  GIVEN("Data with the same size as the state") {
    // SwapState test_data{{0}};
    // fillAndPad(test_data);
    WHEN("The data is absorbed") {
      uint64_t test_data = 0;
      sponge.absorb(test_data);
      THEN("The state is updated") {}
    }
  }
}
