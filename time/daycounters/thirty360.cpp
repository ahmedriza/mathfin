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

#include <base/conversion.hpp>
#include <time/daycounters/thirty360.hpp>

namespace MathFin {

  std::shared_ptr<DayCounter::Impl> Thirty360::implementation(
    Thirty360::Convention c
    ) {
    switch (c) {
    case Convention::USA:
    case Convention::BondBasis:
      return std::shared_ptr<DayCounter::Impl>(new US_Impl);
    case Convention::European:
    case Convention::EurobondBasis:
      return std::shared_ptr<DayCounter::Impl>(new EU_Impl);
    case Convention::Italian:
      return std::shared_ptr<DayCounter::Impl>(new IT_Impl);
    default:
      MF_FAIL("Unknown 30/360 convention");
    }
  }

  Date::serial_type Thirty360::US_Impl::dayCount(
    const Date& d1,
    const Date& d2
    ) const {
    Day dd1 = d1.dayOfMonth();
    Day dd2 = d2.dayOfMonth();
    Integer mm1 = as_integer(d1.month());
    Integer mm2 = as_integer(d2.month());
    Year yy1 = d1.year();
    Year yy2 = d2.year();

    if (dd2 == 31 && dd1 < 30) {
      dd2 = 1;
      mm2++;
    }

    return 360 * (yy2 - yy1) + 30 * (mm2 - mm1 - 1)
      + std::max(Integer(0), 30 - dd1)
      + std::min(Integer(30), dd2);
  }

  Date::serial_type Thirty360::EU_Impl::dayCount(
    const Date& d1,
    const Date& d2
    ) const {
    Day dd1 = d1.dayOfMonth();
    Day dd2 = d2.dayOfMonth();
    Integer mm1 = as_integer(d1.month());
    Integer mm2 = as_integer(d2.month());
    Year yy1 = d1.year();
    Year yy2 = d2.year();

    return 360 * (yy2 - yy1) + 30 * (mm2 - mm1 - 1)
      + std::max(Integer(0), 30 - dd1)
      + std::min(Integer(30), dd2);
  }

  Date::serial_type Thirty360::IT_Impl::dayCount(
    const Date& d1,
    const Date& d2
    ) const {
    Day dd1 = d1.dayOfMonth();
    Day dd2 = d2.dayOfMonth();
    Integer mm1 = as_integer(d1.month());
    Integer mm2 = as_integer(d2.month());
    Year yy1 = d1.year();
    Year yy2 = d2.year();

    if (mm1 == 2 && dd1 > 27) dd1 = 30;
    if (mm2 == 2 && dd2 > 27) dd2 = 30;

    return 360 * (yy2 - yy1) + 30 * (mm2 - mm1 - 1)
      + std::max(Integer(0), 30 - dd1)
      + std::min(Integer(30), dd2);
  }

}
