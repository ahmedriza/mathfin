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
  Copyright (C) 2013 BGC Partners L.P.

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

#ifndef MATHFIN_ACTUAL_365NL_HPP
#define MATHFIN_ACTUAL_365NL_HPP

#include <string>
#include <time/daycounter.hpp>

namespace MathFin {

  /**
   *  Actual/365 (No Leap) day count convention.
   * "Actual/365 (No Leap)" day count convention, also known as
   * "Act/365 (NL)", "NL/365", or "Actual/365 (JGB)".
   *
   * @ingroup daycounters
  */
  class Actual365NoLeap : public DayCounter {
  private:
    class Impl : public DayCounter::Impl {
    public:
      std::string name() const { return std::string("Actual/365 (NL)"); }

      // Returns the exact number of days between 2 dates, excluding leap days
      Date::serial_type dayCount(
        const Date& d1,
        const Date& d2) const {

        static const Integer MonthOffset[] = {
          0,  31,  59,  90, 120, 151,  // Jan - Jun
          181, 212, 243, 273, 304, 334   // Jun - Dec
        };

        Date::serial_type s1, s2;

        s1 = d1.dayOfMonth() + MonthOffset[d1.month()-1] + (d1.year() * 365);
        s2 = d2.dayOfMonth() + MonthOffset[d2.month()-1] + (d2.year() * 365);

        if (d1.month() == Feb && d1.dayOfMonth() == 29) {
          --s1;
        }

        if (d2.month() == Feb && d2.dayOfMonth() == 29) {
          --s2;
        }

        return s2 - s1;
      }

      Time yearFraction(
        const Date& d1,
        const Date& d2,
        const Date& d3,
        const Date& d4) const {
        return dayCount(d1, d2)/365.0;
      }
    };
  public:
    Actual365NoLeap()
      : DayCounter(std::shared_ptr<DayCounter::Impl>(
                     new Actual365NoLeap::Impl)) {}
  };

}

#endif /* MATHFIN_ACTUAL_365NL_HPP */
