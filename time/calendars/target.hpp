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

/*! \file target.hpp
  \brief TARGET calendar
*/

#ifndef MATHFIN_TARGET_CALENDAR_HPP
#define MATHFIN_TARGET_CALENDAR_HPP

#include <time/calendar.hpp>

namespace MathFin {

  //! %TARGET calendar
  /*! Holidays (see http://www.ecb.int):
    <ul>
    <li>Saturdays</li>
    <li>Sundays</li>
    <li>New Year's Day, January 1st</li>
    <li>Good Friday (since 2000)</li>
    <li>Easter Monday (since 2000)</li>
    <li>Labour Day, May 1st (since 2000)</li>
    <li>Christmas, December 25th</li>
    <li>Day of Goodwill, December 26th (since 2000)</li>
    <li>December 31st (1998, 1999, and 2001)</li>
    </ul>

    \ingroup calendars

    \test the correctness of the returned results is tested
    against a list of known holidays.
  */
  class TARGET : public Calendar {
  private:
    class Impl : public Calendar::WesternImpl {
    public:
      std::string name() const { return "TARGET"; }
      bool isBusinessDay(const Date&) const;
    };
  public:
    TARGET();
  };

}

#endif /* MATHFIN_TARGET_CALENDAR_HPP */
