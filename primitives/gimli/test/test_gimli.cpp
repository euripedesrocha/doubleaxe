#include <algorithm>
#include <random>
#include "catch.hpp"
#include "gimli.hpp"
extern "C" {
#include "gimli.h"
}

using GimliState = std::array<uint32_t, 12>;
void RandomState(GimliState& data) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uint32_t> rand_uint32;
  std::generate(std::begin(data), std::end(data),
                [&]() { return rand_uint32(gen); });
}
class HasGimli : Gimli::Gimli<HasGimli, GimliState, 24> {
 public:
  void permutation(GimliState& state) {
    static_cast<Gimli*>(this)->permutation(state);
  }
};

SCENARIO("A full state for rotation") {
  GIVEN("A randomly generated state") {
    HasGimli MyGimli;
    GimliState InitialData;
    RandomState(InitialData);
    auto ReferenceData = InitialData;
    WHEN("The state is processed by my implementation") {
      gimli(std::begin(ReferenceData));
      MyGimli.permutation(InitialData);
      THEN("The result should be the same of the reference") {
        REQUIRE(ReferenceData == InitialData);
      }
    }
  }
}
