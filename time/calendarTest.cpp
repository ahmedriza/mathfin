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
#include <test/catch.hpp>
#include <base/error.hpp>
#include <time/calendar.hpp>
#include <time/calendars/unitedkingdom.hpp>
#include <time/calendars/unitedstates.hpp>
#include <time/calendars/nullcalendar.hpp>

using namespace MathFin;

TEST_CASE("adjust with Unadjusted", "[calendar]") {
  Calendar cal;
  Date d(1, Month::January, 1970);
  Date da = cal.adjust(d, BusinessDayConvention::Unadjusted);
  REQUIRE(d == da);
}

TEST_CASE("adjust with Following", "[calendar]") {
  Calendar cal = UnitedKingdom::Settlement(); // default calendar for UK
  Date d(1, Month::January, 1970);
  Date da = cal.adjust(d, BusinessDayConvention::Following);
  REQUIRE(da == Date(2, Month::January, 1970));
}

TEST_CASE("adjust with ModifiedFollowing", "[calendar]") {
  Calendar cal = UnitedKingdom::Exchange();
  Date d(31, Month::May, 1970);
  Date da = cal.adjust(d, BusinessDayConvention::ModifiedFollowing);
  REQUIRE(da == Date(29, Month::May, 1970));
}

TEST_CASE("add holiday", "[calendar]") {
  Date d(2, Month::January, 1970);

  Calendar cal = UnitedKingdom::Settlement(); // default calendar for UK
  Calendar cal2 = cal.addHoliday(d);

  REQUIRE(cal.isHoliday(d) == false);
  REQUIRE(cal2.isHoliday(d) == true);
}

TEST_CASE("NYSE" "[calendar]") {
  Date d(1, Month::January, 1970);
  Calendar cal = UnitedStates::NYSE();
  REQUIRE(cal.isHoliday(d) == true);
  REQUIRE(cal.isWeekend(Weekday::Sunday) == true);
}

TEST_CASE("Null Calendar" "[calendar]") {
  Date d(1, Month::January, 1970);
  Calendar cal = NullCalendar();
  REQUIRE(cal.isHoliday(d) == false);
  REQUIRE(cal.isWeekend(Weekday::Sunday) == false);
}
