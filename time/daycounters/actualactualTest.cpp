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
#include <time/daycounters/actualactual.hpp>

using namespace MathFin;

TEST_CASE("Actual/Actual AFB", "[daycounters]") {
  // This example is from:
  // https://en.wikipedia.org/wiki/Day_count_convention#Actual.2FActual_AFB
  ActualActual dc(ActualActual::Convention::AFB);
  Date d1 = Date(10, Month::February, 1994);
  Date d2 = Date(30, Month::June, 1997);
  Time yf = dc.yearFraction(d1, d2, Date(), Date());
  REQUIRE(yf - 3.38356 < 1.0E-5);
}
