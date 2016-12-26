#define CATCH_CONFIG_MAIN

#include <test/catch.hpp>
#include <base/error.h>

TEST_CASE( "Error constructor", "[error]") {
  FinMath::Error error("myfile", 1, "someFunction", "invalid input");
  std::string expected = std::string("myfile:1: in function `someFunction': invalid input");
  std::string actual = std::string(error.what());
  REQUIRE(actual == expected);
}
