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

template <class Algorithm, class StateType, size_t capacity>
class Sponge {
  static_assert(capacity % 32 == 0, "Capacity should be a multiple of 32 bits");
  static constexpr std::size_t bitRate =
      std::tuple_size<StateType>::value - capacity;
  decltype(std::begin(state)) currentState = std::begin(state);

 protected:
  void inline verifyPermutate() {
    if (currentState == std::begin(state) + bitRate) {
      currentState = std::begin(state);
      static_cast<Algorithm*>(this)->permutation(state);
    }
  }

  void absorb(StateType& state, const element_type<StateType> data_in) {
    *currentState ^= data_in;
    ++currentState;
    verifyPermutate();
  }
  void switchToSqueeze(StateType& state) {
    static_cast<Algorithm*>(this)->pad(state);
    static_cast<Algorithm*>(this)->permutation(state);
    currentState = std::begin(state);
  }

  uint32_t sqeeze(StateType& state, element_type<StateType>& output) {
    auto output = *currentState;
    ++currentState;
    verifyPermutate();
    return output;
  }

  void sqeezeTo(StateType& state, element_type<StateType>& output,
                size_t amount) {
    for (auto i = 0; i < amount; ++i) {
      output[i] = *currentState;
      ++currentState;
      verifyPermutate();
    }
  }
};
}  // namespace Sponge
