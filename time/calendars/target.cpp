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

#include <time/calendars/target.hpp>

namespace MathFin {

  TARGET::TARGET() :
    Calendar(std::shared_ptr<Calendar::Impl>(new TARGET::Impl))
  {}

  bool TARGET::Impl::isBusinessDay(const Date& date) const {
    Weekday w = date.weekday();
    Day d = date.dayOfMonth(), dd = date.dayOfYear();
    Month m = date.month();
    Year y = date.year();
    Day em = easterMonday(y);
    if (isWeekend(w)
        // New Year's Day
        || (d == 1  && m == Month::January)
        // Good Friday
        || (dd == em-3 && y >= 2000)
        // Easter Monday
        || (dd == em && y >= 2000)
        // Labour Day
        || (d == 1  && m == Month::May && y >= 2000)
        // Christmas
        || (d == 25 && m == Month::December)
        // Day of Goodwill
        || (d == 26 && m == Month::December && y >= 2000)
        // December 31st, 1998, 1999, and 2001 only
        || (d == 31 && m == Month::December &&
            (y == 1998 || y == 1999 || y == 2001)))
      return false;
    return true;
  }

}
