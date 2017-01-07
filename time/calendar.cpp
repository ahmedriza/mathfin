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

/*
  Copyright (C) 2000, 2001, 2002, 2003 RiskMap srl
  Copyright (C) 2003, 2004, 2005, 2006, 2007 StatPro Italia srl
  Copyright (C) 2004 Jeff Yu
  Copyright (C) 2014 Paolo Mazzocchi

  This file is part of QuantLib, a free-software/open-source library
  for financial quantitative analysts and developers - http://quantlib.org/

  QuantLib is free software: you can redistribute it and/or modify it
  under the terms of the QuantLib license.  You should have received a
  copy of the license along with this program; if not, please email
  <quantlib-dev@lists.sf.net>. The license is also available online at
  <http://quantlib.org/license.shtml>.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <base/error.hpp>
#include <time/calendar.hpp>

using boost::posix_time::ptime;

namespace MathFin {

  Calendar Calendar::addHoliday(const Date& d) const {
    MF_REQUIRE(impl_, "no implementation provided");
    std::set<Date> addedHolidays(addedHolidays_);
    std::set<Date> removedHolidays(removedHolidays_);

    // if d was a genuine holiday previously removed, revert the change
    removedHolidays.erase(d);
    // if it's already a holiday, leave the calendar alone.
    // Otherwise, add it.
    if (impl_->isBusinessDay(d)) {
      addedHolidays.insert(d);
    }

    return Calendar(impl_, addedHolidays, removedHolidays);
  }

  Calendar Calendar::removeHoliday(const Date& d) const {
    MF_REQUIRE(impl_, "no implementation provided");
    std::set<Date> addedHolidays(addedHolidays_);
    std::set<Date> removedHolidays(removedHolidays_);

    // if d was an artificially-added holiday, revert the change
    addedHolidays.erase(d);
    // if it's already a business day, leave the calendar alone.
    // Otherwise, add it.
    if (!impl_->isBusinessDay(d)) {
      removedHolidays.insert(d);
    }

    return Calendar(impl_, addedHolidays, removedHolidays);
  }

  Date Calendar::adjust(
    const Date& d,
    BusinessDayConvention c) const {
    MF_REQUIRE(d != Date(), "null date");

    if (c == BusinessDayConvention::Unadjusted) {
      return d;
    }

    ptime pt1 = d.dateTime();

    if (
      c == BusinessDayConvention::Following
      || c == BusinessDayConvention::ModifiedFollowing
      || c == BusinessDayConvention::HalfMonthModifiedFollowing) {

      while (isHoliday(pt1)) {
        pt1 += boost::gregorian::days(1);
      }

      if (
        c == BusinessDayConvention::ModifiedFollowing
        || c == BusinessDayConvention::HalfMonthModifiedFollowing) {

        Date tmp = Date(pt1);

        if (tmp.month() != d.month()) {
          return adjust(d, BusinessDayConvention::Preceding);
        }

        if (c == BusinessDayConvention::HalfMonthModifiedFollowing) {
          if (d.dayOfMonth() <= 15 && tmp.dayOfMonth() > 15) {
            return adjust(d, BusinessDayConvention::Preceding);
          }
        }
      }

    } else if (
      c == BusinessDayConvention::Preceding
      || c == BusinessDayConvention::ModifiedPreceding) {

      while (isHoliday(pt1)) {
        pt1 -= boost::gregorian::days(1);
      }

      Date tmp = Date(pt1);
      if (c == BusinessDayConvention::ModifiedPreceding
          && tmp.month() != d.month()) {
        return adjust(d, BusinessDayConvention::Following);
      }

    } else if (c == BusinessDayConvention::Nearest) {
      ptime pt2 = d.dateTime();

      while (isHoliday(pt1) && isHoliday(pt2)) {
        pt1 += boost::gregorian::days(1);
        pt2 -= boost::gregorian::days(1);
      }
      if (isHoliday(pt1)) {
        return Date(pt2);
      } else {
        return Date(pt1);
      }
    } else {
      MF_FAIL("Unknown business-day convention");
    }

    return Date(pt1);
  }

  Date Calendar::advance(
    const Date& d,
    Integer n,
    TimeUnit unit,
    BusinessDayConvention c,
    bool endOfMonth
    ) const {
    MF_REQUIRE(d != Date(), "null date");

    if (n == 0) {
      return adjust(d, c);
    } else if (unit == TimeUnit::Days) {
      ptime pt = d.dateTime();
      if (n > 0) {
        while (n > 0) {
          pt +=  boost::gregorian::days(1);
          while (isHoliday(pt)) {
            pt +=  boost::gregorian::days(1);
          }
          n--;
        }
      } else {
        while (n < 0) {
          pt -=  boost::gregorian::days(1);
          while(isHoliday(pt)) {
            pt -=  boost::gregorian::days(1);
          }
          n++;
        }
      }
      return Date(pt);
    } else if (unit == TimeUnit::Weeks) {
      Date d1 = d + n * unit;
      return adjust(d1, c);
    } else {
      Date d1 = d + n * unit;
      // we are sure the unit is Months or Years
      if (endOfMonth && isEndOfMonth(d)) {
        return Calendar::endOfMonth(d1);
      }
      return adjust(d1, c);
    }
  }


  Date Calendar::advance(
    const Date & d,
    const Period & p,
    BusinessDayConvention c,
    bool endOfMonth
    ) const {
    return advance(d, p.length(), p.units(), c, endOfMonth);
  }

  Date::serial_type Calendar::businessDaysBetween(
    const Date& from,
    const Date& to,
    bool includeFirst,
    bool includeLast
    ) const {
    Date::serial_type wd = 0;
    if (from != to) {
      if (from < to) {

        // the last one is treated separately to avoid
        // incrementing Date::maxDate()
        ptime ptFrom = from.dateTime();
        ptime ptTo = to.dateTime();

        for (ptime pt = from.dateTime(); pt < to.dateTime();
             pt += boost::gregorian::days(1)) {
          if (isBusinessDay(pt)) {
            ++wd;
          }
        }

        if (isBusinessDay(to)) {
          ++wd;
        }
      } else if (from > to) {

        for (ptime pt = to.dateTime(); pt < from.dateTime();
             pt += boost::gregorian::days(1)) {
          if (isBusinessDay(pt)) {
            ++wd;
          }
        }
        if (isBusinessDay(from)) {
          ++wd;
        }
      }

      if (isBusinessDay(from) && !includeFirst) {
        wd--;
      }
      if (isBusinessDay(to) && !includeLast) {
        wd--;
      }
      if (from > to) {
        wd = -wd;
      }
    }

    return wd;
  }


  // Western calendars

  bool Calendar::WesternImpl::isWeekend(Weekday w) const {
    return w == Weekday::Saturday || w == Weekday::Sunday;
  }

  Day Calendar::WesternImpl::easterMonday(Year y) {
    static const Day EasterMonday[] = {
       98,  90, 103,  95, 114, 106,  91, 111, 102,       // 1901-1909
       87, 107,  99,  83, 103,  95, 115,  99,  91, 111,  // 1910-1919
       96,  87, 107,  92, 112, 103,  95, 108, 100,  91,  // 1920-1929
      111,  96,  88, 107,  92, 112, 104,  88, 108, 100,  // 1930-1939
       85, 104,  96, 116, 101,  92, 112,  97,  89, 108,  // 1940-1949
      100,  85, 105,  96, 109, 101,  93, 112,  97,  89,  // 1950-1959
      109,  93, 113, 105,  90, 109, 101,  86, 106,  97,  // 1960-1969
       89, 102,  94, 113, 105,  90, 110, 101,  86, 106,  // 1970-1979
       98, 110, 102,  94, 114,  98,  90, 110,  95,  86,  // 1980-1989
      106,  91, 111, 102,  94, 107,  99,  90, 103,  95,  // 1990-1999
      115, 106,  91, 111, 103,  87, 107,  99,  84, 103,  // 2000-2009
       95, 115, 100,  91, 111,  96,  88, 107,  92, 112,  // 2010-2019
      104,  95, 108, 100,  92, 111,  96,  88, 108,  92,  // 2020-2029
      112, 104,  89, 108, 100,  85, 105,  96, 116, 101,  // 2030-2039
       93, 112,  97,  89, 109, 100,  85, 105,  97, 109,  // 2040-2049
      101,  93, 113,  97,  89, 109,  94, 113, 105,  90,  // 2050-2059
      110, 101,  86, 106,  98,  89, 102,  94, 114, 105,  // 2060-2069
       90, 110, 102,  86, 106,  98, 111, 102,  94, 114,  // 2070-2079
       99,  90, 110,  95,  87, 106,  91, 111, 103,  94,  // 2080-2089
      107,  99,  91, 103,  95, 115, 107,  91, 111, 103,  // 2090-2099
       88, 108, 100,  85, 105,  96, 109, 101,  93, 112,  // 2100-2109
       97,  89, 109,  93, 113, 105,  90, 109, 101,  86,  // 2110-2119
      106,  97,  89, 102,  94, 113, 105,  90, 110, 101,  // 2120-2129
       86, 106,  98, 110, 102,  94, 114,  98,  90, 110,  // 2130-2139
       95,  86, 106,  91, 111, 102,  94, 107,  99,  90,  // 2140-2149
      103,  95, 115, 106,  91, 111, 103,  87, 107,  99,  // 2150-2159
       84, 103,  95, 115, 100,  91, 111,  96,  88, 107,  // 2160-2169
       92, 112, 104,  95, 108, 100,  92, 111,  96,  88,  // 2170-2179
      108,  92, 112, 104,  89, 108, 100,  85, 105,  96,  // 2180-2189
      116, 101,  93, 112,  97,  89, 109, 100,  85, 105   // 2190-2199
    };
    return EasterMonday[y-1901];
  }

  // Orthodox calendars

  bool Calendar::OrthodoxImpl::isWeekend(Weekday w) const {
    return w == Weekday::Saturday || w == Weekday::Sunday;
  }

  Day Calendar::OrthodoxImpl::easterMonday(Year y) {
    static const Day EasterMonday[] = {
      105, 118, 110, 102, 121, 106, 126, 118, 102,        // 1901-1909
      122, 114,  99, 118, 110,  95, 115, 106, 126, 111,   // 1910-1919
      103, 122, 107,  99, 119, 110, 123, 115, 107, 126,   // 1920-1929
      111, 103, 123, 107,  99, 119, 104, 123, 115, 100,   // 1930-1939
      120, 111,  96, 116, 108, 127, 112, 104, 124, 115,   // 1940-1949
      100, 120, 112,  96, 116, 108, 128, 112, 104, 124,   // 1950-1959
      109, 100, 120, 105, 125, 116, 101, 121, 113, 104,   // 1960-1969
      117, 109, 101, 120, 105, 125, 117, 101, 121, 113,   // 1970-1979
       98, 117, 109, 129, 114, 105, 125, 110, 102, 121,   // 1980-1989
      106,  98, 118, 109, 122, 114, 106, 118, 110, 102,   // 1990-1999
      122, 106, 126, 118, 103, 122, 114,  99, 119, 110,   // 2000-2009
       95, 115, 107, 126, 111, 103, 123, 107,  99, 119,   // 2010-2019
      111, 123, 115, 107, 127, 111, 103, 123, 108,  99,   // 2020-2029
      119, 104, 124, 115, 100, 120, 112,  96, 116, 108,   // 2030-2039
      128, 112, 104, 124, 116, 100, 120, 112,  97, 116,   // 2040-2049
      108, 128, 113, 104, 124, 109, 101, 120, 105, 125,   // 2050-2059
      117, 101, 121, 113, 105, 117, 109, 101, 121, 105,   // 2060-2069
      125, 110, 102, 121, 113,  98, 118, 109, 129, 114,   // 2070-2079
      106, 125, 110, 102, 122, 106,  98, 118, 110, 122,   // 2080-2089
      114,  99, 119, 110, 102, 115, 107, 126, 118, 103,   // 2090-2099
      123, 115, 100, 120, 112,  96, 116, 108, 128, 112,   // 2100-2109
      104, 124, 109, 100, 120, 105, 125, 116, 108, 121,   // 2110-2119
      113, 104, 124, 109, 101, 120, 105, 125, 117, 101,   // 2120-2129
      121, 113,  98, 117, 109, 129, 114, 105, 125, 110,   // 2130-2139
      102, 121, 113,  98, 118, 109, 129, 114, 106, 125,   // 2140-2149
      110, 102, 122, 106, 126, 118, 103, 122, 114,  99,   // 2150-2159
      119, 110, 102, 115, 107, 126, 111, 103, 123, 114,   // 2160-2169
       99, 119, 111, 130, 115, 107, 127, 111, 103, 123,   // 2170-2179
      108,  99, 119, 104, 124, 115, 100, 120, 112, 103,   // 2180-2189
      116, 108, 128, 119, 104, 124, 116, 100, 120, 112    // 2190-2199
    };
    return EasterMonday[y-1901];
  }

  std::vector<Date> Calendar::holidayList(
    const Calendar& calendar,
    const Date& from,
    const Date& to,
    bool includeWeekEnds
    ) {

    MF_REQUIRE(to > from, "'from' date ("
               << from << ") must be earlier than 'to' date ("
               << to << ")");
    std::vector<Date> result;

    for (ptime pt = from.dateTime(); pt <= to.dateTime();
         pt += boost::gregorian::days(1)) {
      Date d = Date(pt);
      if (calendar.isHoliday(d) &&
          (includeWeekEnds || !calendar.isWeekend(d.weekday()))) {
        result.push_back(d);
      }
    }

    return result;
  }

}
