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

/*
  Copyright (C) 2004, 2009 Ferdinando Ametrano
  Copyright (C) 2006 Katiuscia Manzoni
  Copyright (C) 2003 RiskMap srl
  Copyright (C) 2015 Maddalena Zanzi
  Copyright (c) 2015 Klaus Spanderen

  QuantLib is free software: you can redistribute it and/or modify it
  under the terms of the QuantLib license.  You should have received a
  copy of the license along with this program; if not, please email
  <quantlib-dev@lists.sf.net>. The license is also available online at
  <http://quantlib.org/license.shtml>.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <time.h>
#include <iostream>
#include <test/catch.hpp>
#include <time/date.hpp>
#include <base/error.hpp>
#include <base/conversion.hpp>

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
      2016, // year
      21,   // hour
      15,   // minute
      30,   // seconds
      15,   // milliseconds
      10    // microseconds
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

    if (Date::ticksPerSecond() >= 1000000) {
      REQUIRE(d.fractionOfSecond() - 0.01501 < 1.0E-12);
    }

    Date d2(
      28, // day
      Month::February, // month
      2015, // year
      50,   // hour
      165,  // minute
      476,  // seconds
      1234, // milliseconds
      253   // microseconds
      );
    REQUIRE(d2.year() == 2015);
    REQUIRE(d2.month() == Month::March);
    REQUIRE(d2.dayOfMonth() == 2);
    REQUIRE(d2.hours() == 4);
    REQUIRE(d2.minutes() == 52);
    REQUIRE(d2.seconds() == 57);
    if (Date::ticksPerSecond() >= 1000) {
      REQUIRE(d2.milliseconds() == 234);
    }
    if (Date::ticksPerSecond() >= 1000000) {
      REQUIRE(d2.microseconds() == 253);
    }
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

  TEST_CASE("Consistency checks", "[date]") {
    Date::serial_type minDate = Date::minDate().serialNumber() + 1; // 02 Jan 1901
    Date::serial_type maxDate = Date::maxDate().serialNumber(); // 31 Dec 2199

    Day dayOfYearOld = Date(minDate - 1).dayOfYear();
    Day dayOfMonthOld = Date(minDate - 1).dayOfMonth();
    Month monthOld = Date(minDate - 1).month();
    Year yearOld = Date(minDate - 1).year();
    Weekday weekdayOld = Date(minDate - 1).weekday();

    for (Date::serial_type i = minDate; i <= maxDate; ++i) {
      Date t(i);
      REQUIRE(t.serialNumber() == i);

      Day dayOfYear = t.dayOfYear();
      Day dayOfMonth = t.dayOfMonth();
      Month month = t.month();
      Year year = t.year();
      Weekday weekday = t.weekday();

      if (!((dayOfYear == dayOfYearOld + 1) ||
            (dayOfYear == 1 && dayOfYearOld == 365 && !Date::isLeap(yearOld)) ||
            (dayOfYear == 1 && dayOfYearOld == 366 && Date::isLeap(yearOld)))) {
        FAIL("wrong day of year increment: \n"
             << "    date: " << t << "\n"
             << "    day of year: " << dayOfYear << "\n"
             << "    previous:    " << dayOfYearOld);
      }

      dayOfYearOld = dayOfYear;

      if (!((dayOfMonth == dayOfMonthOld + 1 && month == monthOld  && year == yearOld) ||
            (dayOfMonth == 1  && as_integer(month) == as_integer(monthOld) + 1 && year == yearOld) ||
            (dayOfMonth == 1  && month == Month::January && year == yearOld +1 ))) {
        FAIL("wrong day,month,year increment: \n"
             << "    date: " << t << "\n"
             << "    day,month,year: "
             << dayOfMonth << "," << month << "," << year << "\n"
             << "    previous:       "
             << dayOfMonthOld << "," << monthOld << "," << yearOld);
      }

      dayOfMonthOld = dayOfMonth;
      monthOld = month;
      yearOld = year;

      // check month definition
      if (as_integer(month) < 1 || as_integer(month) > 12) {
        FAIL("invalid month: \n"
             << "    date:  " << t << "\n"
             << "    month: " << month);
      }

      // check day definition
      if (dayOfMonth < 1) {
        FAIL("invalid day of month: \n"
             << "    date:  " << t << "\n"
             << "    day: " << dayOfMonth);
      }

      if (!((month == Month::January    && dayOfMonth <= 31) ||
            (month == Month::February   && dayOfMonth <= 28) ||
            (month == Month::February   && dayOfMonth == 29 && Date::isLeap(year)) ||
            (month == Month::March      && dayOfMonth <= 31) ||
            (month == Month::April      && dayOfMonth <= 30) ||
            (month == Month::May        && dayOfMonth <= 31) ||
            (month == Month::June       && dayOfMonth <= 30) ||
            (month == Month::July       && dayOfMonth <= 31) ||
            (month == Month::August     && dayOfMonth <= 31) ||
            (month == Month::September  && dayOfMonth <= 30) ||
            (month == Month::October    && dayOfMonth <= 31) ||
            (month == Month::November   && dayOfMonth <= 30) ||
            (month == Month::December   && dayOfMonth <= 31))) {
        FAIL("invalid day of month: \n"
             << "    date:  " << t << "\n"
             << "    day: " << dayOfMonth);
      }

      // check weekday definition
      if (!((as_integer(weekday) == as_integer(weekdayOld) + 1) ||
            (as_integer(weekday) == 1 && as_integer(weekdayOld) == 7))) {
        FAIL("invalid weekday: \n"
             << "    date:  " << t << "\n"
             << "    weekday:  " << as_integer(weekday) << "\n"
             << "    previous: " << as_integer(weekdayOld));
      }

      weekdayOld = weekday;

      // create the same date with a different constructor
      Date s(dayOfMonth, month, year);
      // check serial number consistency
      Date::serial_type serial = s.serialNumber();
      if (serial != i) {
        FAIL("inconsistent serial number:\n"
             << "    date:          " << t << "\n"
             << "    serial number: " << i << "\n"
             << "    cloned date:   " <<  s << "\n"
             << "    serial number: " << serial);
      }
    } // end for loop
  }
}
