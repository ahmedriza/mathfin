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

#include <iostream>
#include <test/catch.hpp>
#include <base/error.hpp>
#include <time/period.hpp>

namespace MathFin {

  void reset(std::ostringstream& stream) {
    stream.str("");
    stream.clear();
  }

  TEST_CASE("Period constructor", "[period]") {
    Period oneYear(1, TimeUnit::Years);
    Period sixMonths(6, TimeUnit::Months);
    Period threeMonths(3, TimeUnit::Months);

    std::ostringstream stream;
    stream << oneYear;
    REQUIRE(stream.str() == "1Y");

    reset(stream);
    stream << sixMonths;
    REQUIRE(stream.str() == "6M");

    reset(stream);
    stream << threeMonths;
    REQUIRE(stream.str() == "3M");
  }

  TEST_CASE("Copy constructor", "[period]") {
    Period oneYear(1, TimeUnit::Years);
    Period tmp = oneYear;
    REQUIRE(oneYear == tmp);
  }

  TEST_CASE("Divide a period by n", "[period]") {
    Period sixMonths(6, TimeUnit::Months);
    Period threeMonths = sixMonths / 2;
    REQUIRE(threeMonths.length() == 3);
    REQUIRE(threeMonths.units() == TimeUnit::Months);
  }

  TEST_CASE("Add two periods", "[period]") {
    Period sixMonths(6, TimeUnit::Months);
    Period threeMonths = sixMonths / 2;
    Period nineMonths = sixMonths + threeMonths;
    REQUIRE(nineMonths.length() == 9);
    REQUIRE(nineMonths.units() == TimeUnit::Months);
  }

  TEST_CASE("Subtract two periods", "[period]") {
    Period sixMonths(6, TimeUnit::Months);
    Period twoMonths = sixMonths / 3;
    Period fourMonths = sixMonths - twoMonths;
    REQUIRE(fourMonths.length() == 4);
    REQUIRE(fourMonths.units() == TimeUnit::Months);
  }

  // ---------------------------------------------------------------------------
  // TODO
  // relation operators
  // output operator

  // ---------------------------------------------------------------------------

  TEST_CASE("Add Periods of Years and Seconds should throw", "[period]") {
    Period oneYear(1, TimeUnit::Years);
    Period twoSeconds(2, TimeUnit::Seconds);

    CHECK_THROWS_AS(oneYear + twoSeconds, MathFin::Error);
  }

  TEST_CASE("Subtract Periods of Years and Seconds should throw", "[period]") {
    Period oneYear(1, TimeUnit::Years);
    Period twoSeconds(2, TimeUnit::Seconds);

    CHECK_THROWS_AS(oneYear - twoSeconds, MathFin::Error);
  }

  TEST_CASE("Years months algebra", "[period]") {
    Period oneYear(1, TimeUnit::Years);
    Period sixMonths(6, TimeUnit::Months);
    Period threeMonths(3, TimeUnit::Months);
    Period twelveMonths(12, TimeUnit::Months);
    Period fifteenMonths(15, TimeUnit::Months);

    REQUIRE(oneYear / 4 == threeMonths);
    REQUIRE(oneYear / 2 == sixMonths);

    Period sum1 = threeMonths + sixMonths;
    REQUIRE(sum1 == Period(9, TimeUnit::Months));

    Period sum2  = sum1 + oneYear;
    REQUIRE(sum2 == Period(21, TimeUnit::Months));

    REQUIRE(twelveMonths.length() == 12);
    REQUIRE(twelveMonths.units() == TimeUnit::Months);

    Period normalizedTwelveMonths = twelveMonths.normalize();
    REQUIRE(normalizedTwelveMonths.length() == 1);
    REQUIRE(normalizedTwelveMonths.units() == TimeUnit::Years);

    // Odd number of months cannot be normalized
    Period normalizedFifteenMonths = fifteenMonths.normalize();
    REQUIRE(normalizedFifteenMonths == Period(15, TimeUnit::Months));
  }

  TEST_CASE("Weeks days algebra", "[period]") {
    Period twoWeeks(2, TimeUnit::Weeks);
    Period oneWeek(1, TimeUnit::Weeks);
    Period threeDays(3, TimeUnit::Days);
    Period oneDay(1, TimeUnit::Days);

    REQUIRE(twoWeeks / 2 == oneWeek);
    REQUIRE(oneWeek / 7 == oneDay);

    Period sum = threeDays + oneDay;
    REQUIRE(sum == Period(4, TimeUnit::Days));

    Period sevenDays(7, TimeUnit::Days);
    REQUIRE(sevenDays.length() == 7);
    REQUIRE(sevenDays.units() == TimeUnit::Days);
  }
}
