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
  Copyright (C) 2003 RiskMap srl

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

#include <time/daycounters/simpledaycounter.hpp>
#include <time/daycounters/thirty360.hpp>

namespace MathFin {

  namespace { DayCounter fallback = Thirty360(); }

  Date::serial_type SimpleDayCounter::Impl::dayCount(
    const Date& d1,
    const Date& d2) const {
    return fallback.dayCount(d1,d2);
  }

  Time SimpleDayCounter::Impl::yearFraction(
    const Date& d1,
    const Date& d2,
    const Date&,
    const Date&
    ) const {
    Day dm1 = d1.dayOfMonth();
    Day dm2 = d2.dayOfMonth();

    if (dm1 == dm2 ||
        // e.g., Aug 30 -> Feb 28 ?
        (dm1 > dm2 && Date::isEndOfMonth(d2)) ||
        // e.g., Feb 28 -> Aug 30 ?
        (dm1 < dm2 && Date::isEndOfMonth(d1))) {
      return (d2.year()-d1.year()) +
        (Integer(d2.month())-Integer(d1.month()))/12.0;
    } else {
      return fallback.yearFraction(d1,d2);
    }
  }

}
