#include <algorithm>
#include <random>
#include "catch.hpp"
#include "gimli.hpp"
extern "C" {
#include "gimli.h"
}

void RandomState(Gimli::State& data) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uint32_t> rand_uint32;
  std::generate(std::begin(data), std::end(data),
                [&]() { return rand_uint32(gen); });
}
SCENARIO("Words for rotation") {
  REQUIRE(Gimli::rotate(0, 5) == 0);
  REQUIRE(Gimli::rotate(0xBADC0FFE, 0) == 0xBADC0FFE);
  REQUIRE(Gimli::rotate(0xBADC0FFE, 4) == 0xADC0FFEB);
  REQUIRE(Gimli::rotate(0xBADC0FFE, 24) == 0xFEBADC0F);
  REQUIRE(Gimli::rotate(0xBADC0FFE, 9) == 0xB81FFD75);
}

SCENARIO("A full state for rotation") {
  GIVEN("A randomly generated state") {
    Gimli::State InitialData;
    RandomState(InitialData);
    auto ReferenceData = InitialData;
    WHEN("The state is processed by my implementation") {
      gimli(std::begin(ReferenceData));
      Gimli::permutation(InitialData);
      THEN("The result should be the same of the reference") {
        REQUIRE(ReferenceData == InitialData);
      }
    }
  }
}
