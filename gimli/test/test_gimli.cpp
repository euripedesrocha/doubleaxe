#include "catch.hpp"
#include "gimli.hpp"

SCENARIO("Words for rotation") {
  REQUIRE(Gimli::rotate(0, 5) == 0);
  REQUIRE(Gimli::rotate(0xBADC0FFE, 0) == 0xBADC0FFE);
  REQUIRE(Gimli::rotate(0xBADC0FFE, 4) == 0xADC0FFEB);
}
