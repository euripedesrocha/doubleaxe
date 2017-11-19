#pragma once
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
template <typename State>
class Sponge {
  State state{{0}};
  void permutate(State& state);

 public:
  void absorb(State& data_in) {
    state ^= data_in;
    permutate(state);
  }
};
}  // namespace Sponge
