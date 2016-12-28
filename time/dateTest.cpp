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


#include <time.h>
#include <iostream>
#include <test/catch.hpp>
#include <time/date.hpp>
#include <base/error.hpp>

namespace MathFin {

  Date todaysDate() {
    struct tm newtime;
    std::time_t t;
    if (std::time(&t) == std::time_t(-1)) // -1 means time() didn't work
      return Date();
    std::tm *lt = localtime_r(&t, &newtime);
    return Date(Day(lt->tm_mday), Month(lt->tm_mon+1), Year(lt->tm_year+1900));
  }

  TEST_CASE("Default constructor", "[date]") {
    Date d;
    REQUIRE(d.year() == 1899);
    REQUIRE(d.month() == Month::December);
    REQUIRE(d.dayOfMonth() == 30);
  }

  TEST_CASE("Serial number constructor", "[date]") {
    Date d(39448);
    REQUIRE(d.year() == 2008);
    REQUIRE(d.month() == Month::January);
    REQUIRE(d.dayOfMonth() == 1);
  }

  TEST_CASE("Day Month Year Constructor", "[date]") {
    Date d(31, Month::December, 2016);
    REQUIRE(d.year() == 2016);
    REQUIRE(d.month() == Month::December);
    REQUIRE(d.dayOfMonth() == 31);
  }

  TEST_CASE("Construct from ptime", "[date]") {
    boost::gregorian::date gd(2016, boost::gregorian::Dec, 31);
    boost::posix_time::ptime t1(gd, boost::posix_time::hours(5) + boost::posix_time::minutes(4) +
             boost::posix_time::seconds(2) + boost::posix_time::millisec(1)
                                + boost::posix_time::microsec(2)
      );
    Date d(t1);
    REQUIRE(d.year() == 2016);
    REQUIRE(d.month() == Month::December);
    REQUIRE(d.dayOfMonth() == 31);
    REQUIRE(d.hours() == 5);
    REQUIRE(d.minutes() == 4);
    REQUIRE(d.seconds() == 2);
    REQUIRE(d.milliseconds() == 1);
    REQUIRE(d.microseconds() == 2);
  }

  TEST_CASE("Full constructor", "[date]") {
    Date d(
      31, // day
      Month::December, // month
      2016,
      21,
      15,
      30,
      15,
      10
      );
    REQUIRE(d.year() == 2016);
    REQUIRE(d.month() == Month::December);
    REQUIRE(d.dayOfMonth() == 31);
    REQUIRE(d.hours() == 21);
    REQUIRE(d.minutes() == 15);
    REQUIRE(d.seconds() == 30);
    REQUIRE(d.milliseconds() == 15);
    REQUIRE(d.microseconds() == 10);
    REQUIRE(d.weekday() == Weekday::Saturday);
    REQUIRE(d.dayOfYear() == 366);
    REQUIRE(d.serialNumber() == 42735);
    REQUIRE(d.fractionOfDay() - 0.8857640626 < 1.0E-6);
    REQUIRE(d.fractionOfSecond() - 0.01501 < 1.0E-12);
  }

  // static public methods

  TEST_CASE("Today's date", "[date]") {
    Date today = Date::todaysDate();
    Date expected = todaysDate();
    REQUIRE(today == expected);
  }

  TEST_CASE("Local date time", "[date]") {
    Date today = Date::localDateTime();
    Date expected = todaysDate();
    REQUIRE(today.year() == expected.year());
    REQUIRE(today.month() == expected.month());
    REQUIRE(today.dayOfMonth() == expected.dayOfMonth());
  }

  TEST_CASE("Difference in days", "[date]") {
    Date d1(30, Month::December, 2016);
    Date d2(31, Month::December, 2016);
    Date::serial_type diff = d2 - d1;
    REQUIRE(diff == 1);
  }
}
