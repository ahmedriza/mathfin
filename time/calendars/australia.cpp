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

#include <time/calendars/australia.hpp>

namespace MathFin {

  Australia::Australia() :
    Calendar(std::shared_ptr<Calendar::Impl>(new Australia::Impl))
  {}

  bool Australia::Impl::isBusinessDay(const Date& date) const {
    Weekday w = date.weekday();
    Day d = date.dayOfMonth(), dd = date.dayOfYear();
    Month m = date.month();
    Year y = date.year();
    Day em = easterMonday(y);
    if (isWeekend(w)
        // New Year's Day (possibly moved to Monday)
        || (d == 1  && m == Month::January)
        // Australia Day, January 26th (possibly moved to Monday)
        || ((d == 26 || ((d == 27 || d == 28) && w == Weekday::Monday)) &&
            m == Month::January)
        // Good Friday
        || (dd == em-3)
        // Easter Monday
        || (dd == em)
        // ANZAC Day, April 25th (possibly moved to Monday)
        || ((d == 25 || (d == 26 && w == Weekday::Monday)) && m == Month::April)
        // Queen's Birthday, second Monday in June
        || ((d > 7 && d <= 14) && w == Weekday::Monday && m == Month::June)
        // Bank Holiday, first Monday in August
        || (d <= 7 && w == Weekday::Monday && m == Month::August)
        // Labour Day, first Monday in October
        || (d <= 7 && w == Weekday::Monday && m == Month::October)
        // Christmas, December 25th (possibly Monday or Tuesday)
        || ((d == 25 || (d == 27 && (w == Weekday::Monday
                                     || w == Weekday::Tuesday)))
            && m == Month::December)
        // Boxing Day, December 26th (possibly Monday or Tuesday)
        || ((d == 26 || (d == 28 && (w == Weekday::Monday
                                     || w == Weekday::Tuesday)))
            && m == Month::December))
      return false;
    return true;
  }

}
