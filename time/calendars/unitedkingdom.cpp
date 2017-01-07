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
  Copyright (C) 2004 Ferdinando Ametrano
  Copyright (C) 2000, 2001, 2002, 2003 RiskMap srl

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

#include <time/calendars/unitedkingdom.hpp>
#include <base/error.hpp>

namespace MathFin {

  UnitedKingdom::UnitedKingdom() :
    UnitedKingdom(
      std::shared_ptr<Calendar::Impl>(new UnitedKingdom::SettlementImpl))
  {}

  UnitedKingdom::UnitedKingdom(
    const std::shared_ptr<Calendar::Impl>& impl) : Calendar(impl)
  {}

  // ---------------------------------------------------------------------------

  UnitedKingdom UnitedKingdom::Settlement() {
    return UnitedKingdom(
      std::shared_ptr<Calendar::Impl>(new UnitedKingdom::SettlementImpl));
  }

  UnitedKingdom UnitedKingdom::Exchange() {
    return UnitedKingdom(std::shared_ptr<Calendar::Impl>(
                           new UnitedKingdom::ExchangeImpl));
  }

  UnitedKingdom UnitedKingdom::Metals() {
    return UnitedKingdom(
      std::shared_ptr<Calendar::Impl>(new UnitedKingdom::MetalsImpl));
  }

  bool UnitedKingdom::SettlementImpl::isBusinessDay(const Date& date) const {
    Weekday w = date.weekday();
    Day d = date.dayOfMonth(), dd = date.dayOfYear();
    Month m = date.month();
    Year y = date.year();
    Day em = easterMonday(y);
    if (isWeekend(w)
        // New Year's Day (possibly moved to Monday)
        || ((d == 1 || ((d == 2 || d == 3) && w == Weekday::Monday))
            && m == Month::January)
        // Good Friday
        || (dd == em-3)
        // Easter Monday
        || (dd == em)
        // first Monday of May (Early May Bank Holiday)
        || (d <= 7 && w == Weekday::Monday && m == Month::May)
        // last Monday of May (Spring Bank Holiday)
        || (d >= 25 && w == Weekday::Monday && m == Month::May && y != 2002
            && y != 2012)
        // last Monday of August (Summer Bank Holiday)
        || (d >= 25 && w == Weekday::Monday && m == Month::August)
        // Christmas (possibly moved to Monday or Tuesday)
        || ((d == 25 || (d == 27
                         && (w == Weekday::Monday
                             || w == Weekday::Tuesday)))
            && m == Month::December)
        // Boxing Day (possibly moved to Monday or Tuesday)
        || ((d == 26 || (d == 28 && (w == Weekday::Monday
                                     || w == Weekday::Tuesday)))
            && m == Month::December)
        // June 3rd, 2002 only (Golden Jubilee Bank Holiday)
        // June 4rd, 2002 only (special Spring Bank Holiday)
        || ((d == 3 || d == 4) && m == Month::June && y == 2002)
        // April 29th, 2011 only (Royal Wedding Bank Holiday)
        || (d == 29 && m == Month::April && y == 2011)
        // June 4th, 2012 only (Diamond Jubilee Bank Holiday)
        // June 5th, 2012 only (Special Spring Bank Holiday)
        || ((d == 4 || d == 5) && m == Month::June && y == 2012)
        // December 31st, 1999 only
        || (d == 31 && m == Month::December && y == 1999)) {
      return false;
    }

    return true;
  }

  bool UnitedKingdom::ExchangeImpl::isBusinessDay(const Date& date) const {
    Weekday w = date.weekday();
    Day d = date.dayOfMonth(), dd = date.dayOfYear();
    Month m = date.month();
    Year y = date.year();
    Day em = easterMonday(y);
    if (isWeekend(w)
        // New Year's Day (possibly moved to Monday)
        || ((d == 1 || ((d == 2 || d == 3) && w == Weekday::Monday)) &&
            m == Month::January)
        // Good Friday
        || (dd == em-3)
        // Easter Monday
        || (dd == em)
        // first Monday of May (Early May Bank Holiday)
        || (d <= 7 && w == Weekday::Monday && m == Month::May)
        // last Monday of May (Spring Bank Holiday)
        || (d >= 25 && w == Weekday::Monday && m == Month::May && y != 2002
            && y != 2012)
        // last Monday of August (Summer Bank Holiday)
        || (d >= 25 && w == Weekday::Monday && m == Month::August)
        // Christmas (possibly moved to Monday or Tuesday)
        || ((d == 25 || (d == 27 && (w == Weekday::Monday
                                     || w == Weekday::Tuesday)))
            && m == Month::December)
        // Boxing Day (possibly moved to Monday or Tuesday)
        || ((d == 26 || (d == 28 && (w == Weekday::Monday
                                     || w == Weekday::Tuesday)))
            && m == Month::December)
        // June 3rd, 2002 only (Golden Jubilee Bank Holiday)
        // June 4rd, 2002 only (special Spring Bank Holiday)
        || ((d == 3 || d == 4) && m == Month::June && y == 2002)
        // April 29th, 2011 only (Royal Wedding Bank Holiday)
        || (d == 29 && m == Month::April && y == 2011)
        // June 4th, 2012 only (Diamond Jubilee Bank Holiday)
        // June 5th, 2012 only (Special Spring Bank Holiday)
        || ((d == 4 || d == 5) && m == Month::June && y == 2012)
        // December 31st, 1999 only
        || (d == 31 && m == Month::December && y == 1999)) {
      return false;
    }

    return true;
  }


  bool UnitedKingdom::MetalsImpl::isBusinessDay(const Date& date) const {
    Weekday w = date.weekday();
    Day d = date.dayOfMonth(), dd = date.dayOfYear();
    Month m = date.month();
    Year y = date.year();
    Day em = easterMonday(y);
    if (isWeekend(w)
        // New Year's Day (possibly moved to Monday)
        || ((d == 1 || ((d == 2 || d == 3) && w == Weekday::Monday)) &&
            m == Month::January)
        // Good Friday
        || (dd == em-3)
        // Easter Monday
        || (dd == em)
        // first Monday of May (Early May Bank Holiday)
        || (d <= 7 && w == Weekday::Monday && m == Month::May)
        // last Monday of May (Spring Bank Holiday)
        || (d >= 25 && w == Weekday::Monday && m == Month::May && y != 2002
            && y != 2012)
        // last Monday of August (Summer Bank Holiday)
        || (d >= 25 && w == Weekday::Monday && m == Month::August)
        // Christmas (possibly moved to Monday or Tuesday)
        || ((d == 25 || (d == 27 && (w == Weekday::Monday
                                     || w == Weekday::Tuesday)))
            && m == Month::December)
        // Boxing Day (possibly moved to Monday or Tuesday)
        || ((d == 26 || (d == 28 && (w == Weekday::Monday
                                     || w == Weekday::Tuesday)))
            && m == Month::December)
        // June 3rd, 2002 only (Golden Jubilee Bank Holiday)
        // June 4rd, 2002 only (special Spring Bank Holiday)
        || ((d == 3 || d == 4) && m == Month::June && y == 2002)
        // April 29th, 2011 only (Royal Wedding Bank Holiday)
        || (d == 29 && m == Month::April && y == 2011)
        // June 4th, 2012 only (Diamond Jubilee Bank Holiday)
        // June 5th, 2012 only (Special Spring Bank Holiday)
        || ((d == 4 || d == 5) && m == Month::June && y == 2012)
        // December 31st, 1999 only
        || (d == 31 && m == Month::December && y == 1999)) {
      return false;
    }

    return true;
  }
}
