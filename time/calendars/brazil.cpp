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
  Copyright (C) 2005, 2006 Piter Dias
  Copyright (C) 2007 Richard Gomes

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

#include <time/calendars/brazil.hpp>
#include <base/error.hpp>

namespace MathFin {

  // ---------------------------------------------------------------------------

  Brazil::Brazil() :
    Brazil(std::shared_ptr<Calendar::Impl>(new Brazil::SettlementImpl))
  {}

  Brazil::Brazil(const std::shared_ptr<Calendar::Impl>& impl) :
    Calendar(impl)
  {}

  // ---------------------------------------------------------------------------

  Brazil Brazil::Settlement() {
    return Brazil(std::shared_ptr<Calendar::Impl>(new Brazil::SettlementImpl));
  }

  Brazil Brazil::Exchange() {
    return Brazil(std::shared_ptr<Calendar::Impl>(new Brazil::ExchangeImpl));
  }

  // ---------------------------------------------------------------------------

  bool Brazil::SettlementImpl::isBusinessDay(const Date& date) const {
    Weekday w = date.weekday();
    Day d = date.dayOfMonth();
    Month m = date.month();
    Year y = date.year();
    Day dd = date.dayOfYear();
    Day em = easterMonday(y);

    if (isWeekend(w)
        // New Year's Day
        || (d == 1 && m == Month::January)
        // Tiradentes Day
        || (d == 21 && m == Month::April)
        // Labor Day
        || (d == 1 && m == Month::May)
        // Independence Day
        || (d == 7 && m == Month::September)
        // Nossa Sra. Aparecida Day
        || (d == 12 && m == Month::October)
        // All Souls Day
        || (d == 2 && m == Month::November)
        // Republic Day
        || (d == 15 && m == Month::November)
        // Christmas
        || (d == 25 && m == Month::December)
        // Passion of Christ
        || (dd == em-3)
        // Carnival
        || (dd == em-49 || dd == em-48)
        // Corpus Christi
        || (dd == em+59)
      )
      return false;
    return true;
  }

  bool Brazil::ExchangeImpl::isBusinessDay(const Date& date) const {
    Weekday w = date.weekday();
    Day d = date.dayOfMonth();
    Month m = date.month();
    Year y = date.year();
    Day dd = date.dayOfYear();
    Day em = easterMonday(y);

    if (isWeekend(w)
        // New Year's Day
        || (d == 1 && m == Month::January)
        // Sao Paulo City Day
        || (d == 25 && m == Month::January)
        // Tiradentes Day
        || (d == 21 && m == Month::April)
        // Labor Day
        || (d == 1 && m == Month::May)
        // Revolution Day
        || (d == 9 && m == Month::July)
        // Independence Day
        || (d == 7 && m == Month::September)
        // Nossa Sra. Aparecida Day
        || (d == 12 && m == Month::October)
        // All Souls Day
        || (d == 2 && m == Month::November)
        // Republic Day
        || (d == 15 && m == Month::November)
        // Black Consciousness Day
        || (d == 20 && m == Month::November && y >= 2007)
        // Christmas Eve
        || (d == 24 && m == Month::December)
        // Christmas
        || (d == 25 && m == Month::December)
        // Passion of Christ
        || (dd == em-3)
        // Carnival
        || (dd == em-49 || dd == em-48)
        // Corpus Christi
        || (dd == em+59)
        // last business day of the year
        || (m == Month::December && (d == 31 || (d >= 29
                                                 && w == Weekday::Friday)))
      )
      return false;
    return true;
  }


}
