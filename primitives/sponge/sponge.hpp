#pragma once
#include <type_traits>
namespace Sponge {
template <class Container>
void operator^=(Container& d0, const Container& d1) {
  auto CurrrentInput = std::begin(d1);
  auto IEnd = std::end(d1);
  auto CurrentOp = std::begin(d0);
  while (CurrrentInput != IEnd) {
    *CurrentOp ^= *CurrrentInput;
    ++CurrrentInput;
    ++CurrentOp;
  }
}
template <typename T>
using element_type = typename std::remove_reference<decltype(
    *std::begin(std::declval<T&>()))>::type;

template <typename State>
class Sponge {
  State state{{0}};
  decltype(std::begin(state)) currentState = std::begin(state);
  void permutate();
  void pad();
  const std::size_t bitRate;
  void inline verifyPermutate() {
    if (currentState == std::begin(state) + bitRate) {
      currentState = std::begin(state);
      permutate(state);
    }
  }

 public:
  constexpr Sponge(std::size_t bitRate) : bitRate(bitRate) {}
  void absorb(const element_type<State> data_in) {
    *currentState ^= data_in;
    ++currentState;
    verifyPermutate();
  }
  void switchToSqueeze() {
    pad();
    permutate();
    currentState = std::begin(state);
  }

  void sqeezeTo(element_type<State>& output, size_t amount) {
    for (auto i = 0; i < amount; ++i) {
      output[i] = *currentState;
      ++currentState;
      verifyPermutate();
    }
  }
};
}  // namespace Sponge
