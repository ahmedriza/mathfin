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

/*! \file one.hpp
  \brief 1/1 day counter
*/

#ifndef MATHFIN_ONE_DAY_COUNTER_HPP
#define MATHFIN_ONE_DAY_COUNTER_HPP

#include <time/daycounter.hpp>

namespace MathFin {

  /**
   * 1/1 day count convention
   * @ingroup daycounters
   */
  class OneDayCounter : public DayCounter {
  public:
    OneDayCounter()
      : DayCounter(std::shared_ptr<DayCounter::Impl>(
                     new OneDayCounter::Impl))
      {}

  private:
    class Impl : public DayCounter::Impl {
    public:
      std::string name() const { return std::string("1/1"); }

      Date::serial_type dayCount(const Date& d1, const Date& d2) const {
        // the sign is all we need
        return (d2 >= d1 ? 1 : -1);
      };

      Time yearFraction(
        const Date& d1,
        const Date& d2,
        const Date&,
        const Date&) const {
        return Time(dayCount(d1, d2));
      }
    };
  };

}

#endif /* MATHFIN_ONE_DAY_COUNTER_HPP */
