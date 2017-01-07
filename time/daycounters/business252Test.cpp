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
#include <boost/range/irange.hpp>

#include <test/catch.hpp>
#include <base/types.hpp>
#include <base/error.hpp>
#include <time/daycounters/business252.hpp>
#include <time/calendars/brazil.hpp>

using namespace MathFin;

#define EPS 1.0E-12

TEST_CASE("Business252", "[daycounters]") {
  std::vector<Date> testDates = {
    Date(1,  Month::February, 2002),
    Date(4,  Month::February, 2002),
    Date(16, Month::May, 2003),
    Date(17, Month::December, 2003),
    Date(17, Month::December, 2004),
    Date(19, Month::December, 2005),
    Date(2,  Month::January, 2006),
    Date(13, Month::March, 2006),
    Date(15, Month::May, 2006),
    Date(17, Month::March, 2006),
    Date(15, Month::May, 2006),
    Date(26, Month::July, 2006),
    Date(28, Month::June, 2007),
    Date(16, Month::September, 2009),
    Date(26, Month::July, 2016)
  };

  Time expected[] = {
     0.0039682539683,
     1.2738095238095,
     0.6031746031746,
     0.9960317460317,
     1.0000000000000,
     0.0396825396825,
     0.1904761904762,
     0.1666666666667,
    -0.1507936507937,
     0.1507936507937,
     0.2023809523810,
     0.9126984126980,
     2.2142857142860,
     6.8412698412700
  };

  DayCounter dayCounter1 = Business252(Brazil());

  Time calculated;

  for (Size i = 1; i < testDates.size(); ++i) {
    calculated = dayCounter1.yearFraction(testDates[i-1], testDates[i]);
    REQUIRE(std::fabs(calculated - expected[i-1]) <= EPS);
  }

  DayCounter dayCounter2 = Business252();

  for (Size i = 1; i < testDates.size(); ++i) {
    calculated = dayCounter2.yearFraction(testDates[i-1], testDates[i]);
    REQUIRE(std::fabs(calculated - expected[i-1]) <= EPS);
  }
}
