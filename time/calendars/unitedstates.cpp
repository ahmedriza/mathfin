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
  Copyright (C) 2004, 2005 Ferdinando Ametrano
  Copyright (C) 2000, 2001, 2002, 2003 RiskMap srl
  Copyright (C) 2003, 2004, 2005, 2006 StatPro Italia srl

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

#include <time/calendars/unitedstates.hpp>
#include <base/error.hpp>

namespace MathFin {

  namespace {

    // a few rules used by multiple calendars

    bool isWashingtonBirthday(Day d, Month m, Year y, Weekday w) {
      if (y >= 1971) {
        // third Monday in February
        return (d >= 15 && d <= 21) && w == Weekday::Monday
          && m == Month::February;
      } else {
        // February 22nd, possily adjusted
        return (d == 22 || (d == 23 && w == Weekday::Monday)
                || (d == 21 && w == Weekday::Friday)) && m == Month::February;
      }
    }

    bool isMemorialDay(Day d, Month m, Year y, Weekday w) {
      if (y >= 1971) {
        // last Monday in May
        return d >= 25 && w == Weekday::Monday && m == Month::May;
      } else {
        // May 30th, possibly adjusted
        return (d == 30 || (d == 31 && w == Weekday::Monday)
                || (d == 29 && w == Weekday::Friday)) && m == Month::May;
      }
    }

    bool isLaborDay(Day d, Month m, Year y, Weekday w) {
      // first Monday in September
      return d <= 7 && w == Weekday::Monday && m == Month::September;
    }

    bool isColumbusDay(Day d, Month m, Year y, Weekday w) {
      // second Monday in October
      return (d >= 8 && d <= 14) && w == Weekday::Monday && m == Month::October
        && y >= 1971;
    }

    bool isVeteransDay(Day d, Month m, Year y, Weekday w) {
      if (y <= 1970 || y >= 1978) {
        // November 11th, adjusted
        return (d == 11 || (d == 12 && w == Weekday::Monday) ||
                (d == 10 && w == Weekday::Friday)) && m == Month::November;
      } else {
        // fourth Monday in October
        return (d >= 22 && d <= 28) && w == Weekday::Monday
          && m == Month::October;
      }
    }

  }

  // ---------------------------------------------------------------------------
  UnitedStates::UnitedStates() :
    UnitedStates(
      std::shared_ptr<Calendar::Impl>(new UnitedStates::SettlementImpl))
  {
  }

  UnitedStates::UnitedStates(
    const std::shared_ptr<Calendar::Impl>& impl) : Calendar(impl)
  {}

  // ---------------------------------------------------------------------------

  UnitedStates UnitedStates::Settlement() {
    return UnitedStates(
      std::shared_ptr<Calendar::Impl>(new UnitedStates::SettlementImpl));
  }

  UnitedStates UnitedStates::NYSE() {
    return UnitedStates(
      std::shared_ptr<Calendar::Impl>(new UnitedStates::NyseImpl));
  }

  UnitedStates UnitedStates::GovernmentBond() {
    return UnitedStates(
      std::shared_ptr<Calendar::Impl>(new UnitedStates::GovernmentBondImpl));
  }

  UnitedStates UnitedStates::NERC() {
    return UnitedStates(
      std::shared_ptr<Calendar::Impl>(new UnitedStates::NercImpl));
  }

  // ---------------------------------------------------------------------------

  bool UnitedStates::SettlementImpl::isBusinessDay(const Date& date) const {
    Weekday w = date.weekday();
    Day d = date.dayOfMonth();
    Month m = date.month();
    Year y = date.year();
    if (isWeekend(w)
        // New Year's Day (possibly moved to Monday if on Sunday)
        || ((d == 1 || (d == 2 && w == Weekday::Monday)) && m == Month::January)
        // (or to Friday if on Saturday)
        || (d == 31 && w == Weekday::Friday && m == Month::December)
        // Martin Luther King's birthday (third Monday in January)
        || ((d >= 15 && d <= 21) && w == Weekday::Monday && m == Month::January
            && y >= 1983)
        // Washington's birthday (third Monday in February)
        || isWashingtonBirthday(d, m, y, w)
        // Memorial Day (last Monday in May)
        || isMemorialDay(d, m, y, w)
        // Independence Day (Monday if Sunday or Friday if Saturday)
        || ((d == 4 || (d == 5 && w == Weekday::Monday) ||
             (d == 3 && w == Weekday::Friday)) && m == Month::July)
        // Labor Day (first Monday in September)
        || isLaborDay(d, m, y, w)
        // Columbus Day (second Monday in October)
        || isColumbusDay(d, m, y, w)
        // Veteran's Day (Monday if Sunday or Friday if Saturday)
        || isVeteransDay(d, m, y, w)
        // Thanksgiving Day (fourth Thursday in November)
        || ((d >= 22 && d <= 28) && w == Weekday::Thursday
            && m == Month::November)
        // Christmas (Monday if Sunday or Friday if Saturday)
        || ((d == 25 || (d == 26 && w == Weekday::Monday) ||
             (d == 24 && w == Weekday::Friday)) && m == Month::December))
      return false;
    return true;
  }

  bool UnitedStates::NyseImpl::isBusinessDay(const Date& date) const {
    Weekday w = date.weekday();
    Day d = date.dayOfMonth(), dd = date.dayOfYear();
    Month m = date.month();
    Year y = date.year();
    Day em = easterMonday(y);
    if (isWeekend(w)
        // New Year's Day (possibly moved to Monday if on Sunday)
        || ((d == 1 || (d == 2 && w == Weekday::Monday)) && m == Month::January)
        // Washington's birthday (third Monday in February)
        || isWashingtonBirthday(d, m, y, w)
        // Good Friday
        || (dd == em-3)
        // Memorial Day (last Monday in May)
        || isMemorialDay(d, m, y, w)
        // Independence Day (Monday if Sunday or Friday if Saturday)
        || ((d == 4 || (d == 5 && w == Weekday::Monday) ||
             (d == 3 && w == Weekday::Friday)) && m == Month::July)
        // Labor Day (first Monday in September)
        || isLaborDay(d, m, y, w)
        // Thanksgiving Day (fourth Thursday in November)
        || ((d >= 22 && d <= 28) && w == Weekday::Thursday
            && m == Month::November)
        // Christmas (Monday if Sunday or Friday if Saturday)
        || ((d == 25 || (d == 26 && w == Weekday::Monday) ||
             (d == 24 && w == Weekday::Friday)) && m == Month::December)
      ) return false;

    if (y >= 1998 && (d >= 15 && d <= 21) && w == Weekday::Monday
        && m == Month::January)
      // Martin Luther King's birthday (third Monday in January)
      return false;

    if ((y <= 1968 || (y <= 1980 && y % 4 == 0)) && m == Month::November
        && d <= 7 && w == Weekday::Tuesday)
      // Presidential election days
      return false;

    // Special closings
    if (// Hurricane Sandy
      (y == 2012 && m == Month::October && (d == 29 || d == 30))
      // President Ford's funeral
      || (y == 2007 && m == Month::January && d == 2)
      // President Reagan's funeral
      || (y == 2004 && m == Month::June && d == 11)
      // September 11-14, 2001
      || (y == 2001 && m == Month::September && (11 <= d && d <= 14))
      // President Nixon's funeral
      || (y == 1994 && m == Month::April && d == 27)
      // Hurricane Gloria
      || (y == 1985 && m == Month::September && d == 27)
      // 1977 Blackout
      || (y == 1977 && m == Month::July && d == 14)
      // Funeral of former President Lyndon B. Johnson.
      || (y == 1973 && m == Month::January && d == 25)
      // Funeral of former President Harry S. Truman
      || (y == 1972 && m == Month::December && d == 28)
      // National Day of Participation for the lunar exploration.
      || (y == 1969 && m == Month::July && d == 21)
      // Funeral of former President Eisenhower.
      || (y == 1969 && m == Month::March && d == 31)
      // Closed all day - heavy snow.
      || (y == 1969 && m == Month::February && d == 10)
      // Day after Independence Day.
      || (y == 1968 && m == Month::July && d == 5)
      // June 12-Dec. 31, 1968
      // Four day week (closed on Wednesdays) - Paperwork Crisis
      || (y == 1968 && dd >= 163 && w == Weekday::Wednesday)
      // Day of mourning for Martin Luther King Jr.
      || (y == 1968 && m == Month::April && d == 9)
      // Funeral of President Kennedy
      || (y == 1963 && m == Month::November && d == 25)
      // Day before Decoration Day
      || (y == 1961 && m == Month::May && d == 29)
      // Day after Christmas
      || (y == 1958 && m == Month::December && d == 26)
      // Christmas Eve
      || ((y == 1954 || y == 1956 || y == 1965)
          && m == Month::December && d == 24)
      ) return false;

    return true;
  }


  bool UnitedStates::GovernmentBondImpl::isBusinessDay(const Date& date)
    const {
    Weekday w = date.weekday();
    Day d = date.dayOfMonth(), dd = date.dayOfYear();
    Month m = date.month();
    Year y = date.year();
    Day em = easterMonday(y);
    if (isWeekend(w)
        // New Year's Day (possibly moved to Monday if on Sunday)
        || ((d == 1 || (d == 2 && w == Weekday::Monday)) && m == Month::January)
        // Martin Luther King's birthday (third Monday in January)
        || ((d >= 15 && d <= 21) && w == Weekday::Monday && m == Month::January
            && y >= 1983)
        // Washington's birthday (third Monday in February)
        || isWashingtonBirthday(d, m, y, w)
        // Good Friday
        || (dd == em-3)
        // Memorial Day (last Monday in May)
        || isMemorialDay(d, m, y, w)
        // Independence Day (Monday if Sunday or Friday if Saturday)
        || ((d == 4 || (d == 5 && w == Weekday::Monday) ||
             (d == 3 && w == Weekday::Friday)) && m == Month::July)
        // Labor Day (first Monday in September)
        || isLaborDay(d, m, y, w)
        // Columbus Day (second Monday in October)
        || isColumbusDay(d, m, y, w)
        // Veteran's Day (Monday if Sunday or Friday if Saturday)
        || isVeteransDay(d, m, y, w)
        // Thanksgiving Day (fourth Thursday in November)
        || ((d >= 22 && d <= 28) && w == Weekday::Thursday
            && m == Month::November)
        // Christmas (Monday if Sunday or Friday if Saturday)
        || ((d == 25 || (d == 26 && w == Weekday::Monday) ||
             (d == 24 && w == Weekday::Friday)) && m == Month::December))
      return false;
    return true;
  }


  bool UnitedStates::NercImpl::isBusinessDay(const Date& date) const {
    Weekday w = date.weekday();
    Day d = date.dayOfMonth();
    Month m = date.month();
    Year y = date.year();
    if (isWeekend(w)
        // New Year's Day (possibly moved to Monday if on Sunday)
        || ((d == 1 || (d == 2 && w == Weekday::Monday)) && m == Month::January)
        // Memorial Day (last Monday in May)
        || isMemorialDay(d, m, y, w)
        // Independence Day (Monday if Sunday)
        || ((d == 4 || (d == 5 && w == Weekday::Monday)) && m == Month::July)
        // Labor Day (first Monday in September)
        || isLaborDay(d, m, y, w)
        // Thanksgiving Day (fourth Thursday in November)
        || ((d >= 22 && d <= 28) && w == Weekday::Thursday && m == Month::November)
        // Christmas (Monday if Sunday)
        || ((d == 25 || (d == 26 && w == Weekday::Monday)) && m == Month::December))
      return false;
    return true;
  }


} /* end namespace MathFin */
