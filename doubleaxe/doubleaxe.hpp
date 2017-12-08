#include "gimli.hpp"
#include "sponge.hpp"

namespace DoubleAxe {
constexpr size_t Capacity = 128;
constexpr size_t Rounds = 24;
class DoubleAxe
    : public Gimli::Gimli<DoubleAxe, Gimli::GimliState, Rounds>,
      public Sponge::Sponge<DoubleAxe, Gimli::GimliState, Capacity> {
  using StateIt = Gimli::GimliState::iterator;
  void pad(GimliState& state);
  StateType stateEnc{{0}};
  StateType stateDec{{0}};

 public:
  void set_key(StateIt keyStart, StateIt keyEND) {
    auto currentKey = keyStart;
    while (CurrrentKey != keyEnd) {
      absorb(stateEnc, *currentKey);
      absorb(stateDec, *currentKey);
      ++currentKey;
    }
    switchToSqueeze();
  };
  void encrypt(StateIt start, StateIt end);
  void decrypt(StateIt start, StateIt end);
};
}  // namespace DoubleAxe
