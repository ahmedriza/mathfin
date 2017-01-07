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

/*! \file simpledaycounter.hpp
  \brief Simple day counter for reproducing theoretical calculations
*/

#ifndef MATFHIN_SIMPLE_DAY_COUNTER_HPP
#define MATFHIN_SIMPLE_DAY_COUNTER_HPP

#include <time/daycounter.hpp>

namespace MathFin {

  /**
   * Simple day counter for reproducing theoretical calculations.
   * This day counter tries to ensure that whole-month distances
   * are returned as a simple fraction, i.e., 1 year = 1.0,
   * 6 months = 0.5, 3 months = 0.25 and so forth.
   *
   * @warning this day counter should be used together with
   * NullCalendar, which ensures that dates at whole-month
   * distances share the same day of month. It is <b>not</b>
   * guaranteed to work with any other calendar.
   *
   * @ingroup daycounters
   *
   */
  class SimpleDayCounter : public DayCounter {
  private:
    class Impl : public DayCounter::Impl {
    public:
      std::string name() const { return "Simple"; }
      Date::serial_type dayCount(
        const Date& d1,
        const Date& d2) const;
      Time yearFraction(
        const Date& d1,
        const Date& d2,
        const Date&,
        const Date&) const;
    };
  public:
    SimpleDayCounter()
      : DayCounter(std::shared_ptr<DayCounter::Impl>(
                     new SimpleDayCounter::Impl())) {}
  };

}

#endif /* MATFHIN_SIMPLE_DAY_COUNTER_HPP */
