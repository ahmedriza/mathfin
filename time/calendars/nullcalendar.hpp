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
  Copyright (C) 2007 StatPro Italia srl

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

/*! \file nullcalendar.hpp
  \brief Calendar for reproducing theoretical calculations
*/

#ifndef MATHFIN_NULL_CALENDAR_HPP
#define MATHFIN_NULL_CALENDAR_HPP

#include <time/calendar.hpp>

namespace MathFin {

  /**
   * Calendar for reproducing theoretical calculations.
   * This calendar has no holidays. It ensures that dates at
   * whole-month distances have the same day of month.
   *
   * @ingroup calendars
  */
  class NullCalendar : public Calendar {
  private:
    class Impl : public Calendar::Impl {
    public:
      std::string name() const { return "Null"; }
      bool isWeekend(Weekday) const { return false; }
      bool isBusinessDay(const Date&) const { return true; }
    };
  public:
    NullCalendar() :
      Calendar(
        std::shared_ptr<Calendar::Impl>(new NullCalendar::Impl)) {}
  };

}

#endif /* MATHFIN_NULL_CALENDAR_HPP */
