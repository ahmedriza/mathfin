#define CATCH_CONFIG_MAIN

#include <iostream>
#include <test/catch.hpp>
#include <base/error.h>
#include <time/businessdayconvention.h>

TEST_CASE( "Following outputs 'Following'", "[businessdayconvention]") {
  FinMath::BusinessDayConvention convention = FinMath::BusinessDayConvention::Following;
  std::ostringstream stream;
  stream << convention;
  REQUIRE(stream.str() == "Following");
}

TEST_CASE( "ModifiedFollowing outputs 'Modified Following'", "[businessdayconvention]") {
  FinMath::BusinessDayConvention convention = FinMath::BusinessDayConvention::ModifiedFollowing;
  std::ostringstream stream;
  stream << convention;
  REQUIRE(stream.str() == "Modified Following");
}

TEST_CASE( "HalfMonthModifiedFollowing outputs 'Half-Month Modified Following'", "[businessdayconvention]") {
  FinMath::BusinessDayConvention convention = FinMath::BusinessDayConvention::HalfMonthModifiedFollowing;
  std::ostringstream stream;
  stream << convention;
  REQUIRE(stream.str() == "Half-Month Modified Following");
}

TEST_CASE( "Preceding outputs 'Preceding'", "[businessdayconvention]") {
  FinMath::BusinessDayConvention convention = FinMath::BusinessDayConvention::Preceding;
  std::ostringstream stream;
  stream << convention;
  REQUIRE(stream.str() == "Preceding");
}

TEST_CASE( "ModifiedPreceding outputs 'Modified Preceding'", "[businessdayconvention]") {
  FinMath::BusinessDayConvention convention = FinMath::BusinessDayConvention::ModifiedPreceding;
  std::ostringstream stream;
  stream << convention;
  REQUIRE(stream.str() == "Modified Preceding");
}

TEST_CASE( "Nearest outputs 'Nearest'", "[businessdayconvention]") {
  FinMath::BusinessDayConvention convention = FinMath::BusinessDayConvention::Nearest;
  std::ostringstream stream;
  stream << convention;
  REQUIRE(stream.str() == "Nearest");
}

TEST_CASE( "Uknown should throw", "[businessdayconvention]") {
  FinMath::BusinessDayConvention convention = FinMath::BusinessDayConvention::Unknown;
  std::ostringstream stream;
  CHECK_THROWS_AS(stream << convention, FinMath::Error);
}
