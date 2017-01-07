/*
  Copyright (C) 2017 Ahmed Riza

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

#include <iostream>
#include <vector>

#include <test/catch.hpp>
#include <base/types.hpp>
#include <base/error.hpp>
#include <time/daycounters/thirty360.hpp>

using namespace MathFin;

#define EPS 1.0E-12

TEST_CASE("Thirty360 BondBasis", "[daycounters]") {
  // http://www.isda.org/c_and_a/docs/30-360-2006ISDADefs.xls
  // Source: 2006 ISDA Definitions, Sec. 4.16 (f)
  // 30/360 (or Bond Basis)

  DayCounter dayCounter = Thirty360(Thirty360::Convention::BondBasis);
  std::vector<Date> testStartDates;
  std::vector<Date> testEndDates;

  // ISDA - Example 1: End dates do not involve the last day of February
  testStartDates.push_back(Date(20, Month::August, 2006));
  testEndDates.push_back(Date(20, Month::February, 2007));

  testStartDates.push_back(Date(20, Month::February, 2007));
  testEndDates.push_back(Date(20, Month::August, 2007));

  testStartDates.push_back(Date(20, Month::August, 2007));
  testEndDates.push_back(Date(20, Month::February, 2008));

  testStartDates.push_back(Date(20, Month::February, 2008));
  testEndDates.push_back(Date(20, Month::August, 2008));

  testStartDates.push_back(Date(20, Month::August, 2008));
  testEndDates.push_back(Date(20, Month::February, 2009));

  testStartDates.push_back(Date(20, Month::February, 2009));
  testEndDates.push_back(Date(20, Month::August, 2009));

  // ISDA - Example 2: End dates include some end-February dates
  testStartDates.push_back(Date(31, Month::August, 2006));
  testEndDates.push_back(Date(28, Month::February, 2007));

  testStartDates.push_back(Date(28, Month::February, 2007));
  testEndDates.push_back(Date(31, Month::August, 2007));

  testStartDates.push_back(Date(31, Month::August, 2007));
  testEndDates.push_back(Date(29, Month::February, 2008));

  testStartDates.push_back(Date(29, Month::February, 2008));
  testEndDates.push_back(Date(31, Month::August, 2008));

  testStartDates.push_back(Date(31, Month::August, 2008));
  testEndDates.push_back(Date(28, Month::February, 2009));

  testStartDates.push_back(Date(28, Month::February, 2009));
  testEndDates.push_back(Date(31, Month::August, 2009));

  //// ISDA - Example 3: Miscellaneous calculations
  testStartDates.push_back(Date(31, Month::January, 2006));
  testEndDates.push_back(Date(28, Month::February, 2006));

  testStartDates.push_back(Date(30, Month::January, 2006));
  testEndDates.push_back(Date(28, Month::February, 2006));

  testStartDates.push_back(Date(28, Month::February, 2006));
  testEndDates.push_back(Date(3, Month::March, 2006));

  testStartDates.push_back(Date(14, Month::February, 2006));
  testEndDates.push_back(Date(28, Month::February, 2006));

  testStartDates.push_back(Date(30, Month::September, 2006));
  testEndDates.push_back(Date(31, Month::October, 2006));

  testStartDates.push_back(Date(31, Month::October, 2006));
  testEndDates.push_back(Date(28, Month::November, 2006));

  testStartDates.push_back(Date(31, Month::August, 2007));
  testEndDates.push_back(Date(28, Month::February, 2008));

  testStartDates.push_back(Date(28, Month::February, 2008));
  testEndDates.push_back(Date(28, Month::August, 2008));

  testStartDates.push_back(Date(28, Month::February, 2008));
  testEndDates.push_back(Date(30, Month::August, 2008));

  testStartDates.push_back(Date(28, Month::February, 2008));
  testEndDates.push_back(Date(31, Month::August, 2008));

  testStartDates.push_back(Date(26, Month::February, 2007));
  testEndDates.push_back(Date(28, Month::February, 2008));

  testStartDates.push_back(Date(26, Month::February, 2007));
  testEndDates.push_back(Date(29, Month::February, 2008));

  testStartDates.push_back(Date(29, Month::February, 2008));
  testEndDates.push_back(Date(28, Month::February, 2009));

  testStartDates.push_back(Date(28, Month::February, 2008));
  testEndDates.push_back(Date(30, Month::March, 2008));

  testStartDates.push_back(Date(28, Month::February, 2008));
  testEndDates.push_back(Date(31, Month::March, 2008));

  int expected[] = { 180, 180, 180, 180, 180, 180,
                     178, 183, 179, 182, 178, 183,
                     28,  28,   5,  14,  30,  28,
                     178, 180, 182, 183, 362, 363,
                     359,  32,  33};

  Time calculated;
  for (Size i = 0; i < testStartDates.size(); ++i) {
    calculated = dayCounter.dayCount(testStartDates[i], testEndDates[i]);
    REQUIRE(calculated == expected[i]);
  }
}

TEST_CASE("Thirty360 EuroBondBasis", "[daycounters]") {

  // Source: ISDA 2006 Definitions 4.16 (g)
  // 30E/360 (or Eurobond Basis)
  // Based on ICMA (Rule 251) and FBF; this is the version of 30E/360 used by Excel

  DayCounter dayCounter = Thirty360(Thirty360::Convention::EurobondBasis);
  std::vector<Date> testStartDates;
  std::vector<Date> testEndDates;

  // ISDA - Example 1: End dates do not involve the last day of February
  testStartDates.push_back(Date(20, Month::August, 2006));
  testEndDates.push_back(Date(20, Month::February, 2007));

  testStartDates.push_back(Date(20, Month::February, 2007));
  testEndDates.push_back(Date(20, Month::August, 2007));

  testStartDates.push_back(Date(20, Month::August, 2007));
  testEndDates.push_back(Date(20, Month::February, 2008));

  testStartDates.push_back(Date(20, Month::February, 2008));
  testEndDates.push_back(Date(20, Month::August, 2008));

  testStartDates.push_back(Date(20, Month::August, 2008));
  testEndDates.push_back(Date(20, Month::February, 2009));

  testStartDates.push_back(Date(20, Month::February, 2009));
  testEndDates.push_back(Date(20, Month::August, 2009));

  //// ISDA - Example 2: End dates include some end-February dates
  testStartDates.push_back(Date(28, Month::February, 2006));
  testEndDates.push_back(Date(31, Month::August, 2006));

  testStartDates.push_back(Date(31, Month::August, 2006));
  testEndDates.push_back(Date(28, Month::February, 2007));

  testStartDates.push_back(Date(28, Month::February, 2007));
  testEndDates.push_back(Date(31, Month::August, 2007));

  testStartDates.push_back(Date(31, Month::August, 2007));
  testEndDates.push_back(Date(29, Month::February, 2008));

  testStartDates.push_back(Date(29, Month::February, 2008));
  testEndDates.push_back(Date(31, Month::August, 2008));

  testStartDates.push_back(Date(31, Month::August, 2008));
  testEndDates.push_back(Date(28, Month::Feb, 2009));

  testStartDates.push_back(Date(28, Month::February, 2009));
  testEndDates.push_back(Date(31, Month::August, 2009));

  testStartDates.push_back(Date(31, Month::August, 2009));
  testEndDates.push_back(Date(28, Month::Feb, 2010));

  testStartDates.push_back(Date(28, Month::February, 2010));
  testEndDates.push_back(Date(31, Month::August, 2010));

  testStartDates.push_back(Date(31, Month::August, 2010));
  testEndDates.push_back(Date(28, Month::Feb, 2011));

  testStartDates.push_back(Date(28, Month::February, 2011));
  testEndDates.push_back(Date(31, Month::August, 2011));

  testStartDates.push_back(Date(31, Month::August, 2011));
  testEndDates.push_back(Date(29, Month::Feb, 2012));

  //// ISDA - Example 3: Miscellaneous calculations
  testStartDates.push_back(Date(31, Month::January, 2006));
  testEndDates.push_back(Date(28, Month::February, 2006));

  testStartDates.push_back(Date(30, Month::January, 2006));
  testEndDates.push_back(Date(28, Month::February, 2006));

  testStartDates.push_back(Date(28, Month::February, 2006));
  testEndDates.push_back(Date(3, Month::March, 2006));

  testStartDates.push_back(Date(14, Month::February, 2006));
  testEndDates.push_back(Date(28, Month::February, 2006));

  testStartDates.push_back(Date(30, Month::September, 2006));
  testEndDates.push_back(Date(31, Month::October, 2006));

  testStartDates.push_back(Date(31, Month::October, 2006));
  testEndDates.push_back(Date(28, Month::November, 2006));

  testStartDates.push_back(Date(31, Month::August, 2007));
  testEndDates.push_back(Date(28, Month::February, 2008));

  testStartDates.push_back(Date(28, Month::February, 2008));
  testEndDates.push_back(Date(28, Month::August, 2008));

  testStartDates.push_back(Date(28, Month::February, 2008));
  testEndDates.push_back(Date(30, Month::August, 2008));

  testStartDates.push_back(Date(28, Month::February, 2008));
  testEndDates.push_back(Date(31, Month::August, 2008));

  testStartDates.push_back(Date(26, Month::February, 2007));
  testEndDates.push_back(Date(28, Month::February, 2008));

  testStartDates.push_back(Date(26, Month::February, 2007));
  testEndDates.push_back(Date(29, Month::February, 2008));

  testStartDates.push_back(Date(29, Month::February, 2008));
  testEndDates.push_back(Date(28, Month::February, 2009));

  testStartDates.push_back(Date(28, Month::February, 2008));
  testEndDates.push_back(Date(30, Month::March, 2008));

  testStartDates.push_back(Date(28, Month::February, 2008));
  testEndDates.push_back(Date(31, Month::March, 2008));

  int expected[] = { 180, 180, 180, 180, 180, 180,
                     182, 178, 182, 179, 181, 178,
                     182, 178, 182, 178, 182, 179,
                     28,  28,   5,  14,  30,  28,
                     178, 180, 182, 182, 362, 363,
                     359,  32,  32 };

  Time calculated;
  for (Size i = 0; i < testStartDates.size(); i++) {
    calculated = dayCounter.dayCount(testStartDates[i], testEndDates[i]);
    REQUIRE(calculated == expected[i]);
  }
}
