#include <algorithm>
#include <random>
#include "catch.hpp"
#include "sponge.hpp"

using DummyState = std::array<uint32_t, 12>;
using StateIt = DummyState::iterator;
template <class CryptograficAlgorithm, class StateType, size_t n_rounds>
class DummyPermutation {
  friend CryptograficAlgorithm;

 public:
  void permutation([[maybe_unused]] StateType& state) {}
};

constexpr std::size_t capacity = 128;
class SpongeTest : public DummyPermutation<SpongeTest, DummyState, 24>,
                   public Sponge::Sponge<SpongeTest, DummyState, capacity> {
 public:
  void absorbData(StateIt data_start, StateIt data_end) {
    auto current = data_start;
    while (current != data_end) {
      absorb(*current);
      ++current;
    }
  };
  void squeezeData(StateIt data_start, StateIt data_end) {
    auto current = data_start;
    while (current != data_end) {
      absorb(*current);
      ++current;
    }
  };
};

void fillAndPad(DummyState& data) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uint32_t> rand_uint32;
  std::generate(std::begin(data), std::end(data),
                [&]() { return rand_uint32(gen); });
}

SCENARIO("A sponge will be used with an arbitrary permutation", "[SPONGE]") {
  SpongeTest sponge;
  GIVEN("Data with the same size as the state") {
    DummyState test_data{{0}};
    fillAndPad(test_data);
    WHEN("The data is absorbed") {
      sponge.absorbData(std::begin(test_data), std::end(test_data));
      THEN("The state is updated") {}
    }
  }
}
