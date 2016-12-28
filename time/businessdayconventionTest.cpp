/*
  Copyright (C) 2016 Ahmed Riza

  This file is part of MathFin.

  This program is free software: you  can redistribute it and/or modify it
  under the  terms of the GNU  General Public License as  published by the
  Free Software Foundation,  either version 3 of the License,  or (at your
  option) any later version.

  This  program  is distributed  in  the  hope  that  it will  be  useful,
  but  WITHOUT  ANY  WARRANTY;  without   even  the  implied  warranty  of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
  Public License for more details.

  You should have received a copy  of the GNU General Public License along
  with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#define CATCH_CONFIG_MAIN

#include <iostream>
#include <test/catch.hpp>
#include <base/error.hpp>
#include <time/businessdayconvention.hpp>

TEST_CASE( "Following outputs 'Following'", "[businessdayconvention]") {
  MathFin::BusinessDayConvention convention = MathFin::BusinessDayConvention::Following;
  std::ostringstream stream;
  stream << convention;
  REQUIRE(stream.str() == "Following");
}

TEST_CASE( "ModifiedFollowing outputs 'Modified Following'", "[businessdayconvention]") {
  MathFin::BusinessDayConvention convention = MathFin::BusinessDayConvention::ModifiedFollowing;
  std::ostringstream stream;
  stream << convention;
  REQUIRE(stream.str() == "Modified Following");
}

TEST_CASE( "HalfMonthModifiedFollowing outputs 'Half-Month Modified Following'", "[businessdayconvention]") {
  MathFin::BusinessDayConvention convention = MathFin::BusinessDayConvention::HalfMonthModifiedFollowing;
  std::ostringstream stream;
  stream << convention;
  REQUIRE(stream.str() == "Half-Month Modified Following");
}

TEST_CASE( "Preceding outputs 'Preceding'", "[businessdayconvention]") {
  MathFin::BusinessDayConvention convention = MathFin::BusinessDayConvention::Preceding;
  std::ostringstream stream;
  stream << convention;
  REQUIRE(stream.str() == "Preceding");
}

TEST_CASE( "ModifiedPreceding outputs 'Modified Preceding'", "[businessdayconvention]") {
  MathFin::BusinessDayConvention convention = MathFin::BusinessDayConvention::ModifiedPreceding;
  std::ostringstream stream;
  stream << convention;
  REQUIRE(stream.str() == "Modified Preceding");
}

TEST_CASE( "Nearest outputs 'Nearest'", "[businessdayconvention]") {
  MathFin::BusinessDayConvention convention = MathFin::BusinessDayConvention::Nearest;
  std::ostringstream stream;
  stream << convention;
  REQUIRE(stream.str() == "Nearest");
}

TEST_CASE( "Uknown should throw", "[businessdayconvention]") {
  MathFin::BusinessDayConvention convention = MathFin::BusinessDayConvention::Unknown;
  std::ostringstream stream;
  CHECK_THROWS_AS(stream << convention, MathFin::Error);
}
