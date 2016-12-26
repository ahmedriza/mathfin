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

#include <test/catch.hpp>
#include <base/error.h>

TEST_CASE( "Error constructor", "[error]") {
  FinMath::Error error("myfile", 1, "someFunction", "invalid input");
  std::string expected = std::string("myfile:1: in function `someFunction': invalid input");
  std::string actual = std::string(error.what());
  REQUIRE(actual == expected);
}
