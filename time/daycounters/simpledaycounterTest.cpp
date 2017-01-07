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
#include <time/daycounters/simpledaycounter.hpp>

using namespace MathFin;

#define EPS 1.0E-12

TEST_CASE("SimpleDayCounter", "[daycounters]") {
  Period p[] = {
    Period(3, TimeUnit::Months),
    Period(6, TimeUnit::Months),
    Period(1, TimeUnit::Years)
  };

  Time expected[] = { 0.25, 0.5, 1.0 };
  Date first(1, Month::January, 2002);
  Date last(31, Month::December, 2005);

  // generate dates from [first, last]
  int days = last - first + 1;
  std::vector<Date> dates;
  for (auto i : boost::irange(0, days)) {
    dates.push_back(first + i);
  }

  REQUIRE(dates[dates.size() - 1] == last);

  DayCounter dayCounter = SimpleDayCounter();

  int n = sizeof(p) / sizeof(Period);
  for (Date& start : dates) {
    for (auto i : boost::irange(0, n)) {
      Date end = start + p[i];
      Time calcualted = dayCounter.yearFraction(start, end);
      REQUIRE(std::fabs(calcualted - expected[i]) <= EPS);
    }
  }
}
