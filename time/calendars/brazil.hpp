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

/*! \file brazil.hpp
  \brief Brazilian calendar
*/

#ifndef QUANTLIB_BRAZILIAN_CALENDAR_HPP
#define QUANTLIB_BRAZILIAN_CALENDAR_HPP

#include <time/calendar.hpp>

namespace MathFin {

  //! Brazilian calendar
  /*! Banking holidays:
    <ul>
    <li>Saturdays</li>
    <li>Sundays</li>
    <li>New Year's Day, January 1st</li>
    <li>Tiradentes's Day, April 21th</li>
    <li>Labour Day, May 1st</li>
    <li>Independence Day, September 7th</li>
    <li>Nossa Sra. Aparecida Day, October 12th</li>
    <li>All Souls Day, November 2nd</li>
    <li>Republic Day, November 15th</li>
    <li>Christmas, December 25th</li>
    <li>Passion of Christ</li>
    <li>Carnival</li>
    <li>Corpus Christi</li>
    </ul>

    Holidays for the Bovespa stock exchange
    <ul>
    <li>Saturdays</li>
    <li>Sundays</li>
    <li>New Year's Day, January 1st</li>
    <li>Sao Paulo City Day, January 25th</li>
    <li>Tiradentes's Day, April 21th</li>
    <li>Labour Day, May 1st</li>
    <li>Revolution Day, July 9th</li>
    <li>Independence Day, September 7th</li>
    <li>Nossa Sra. Aparecida Day, October 12th</li>
    <li>All Souls Day, November 2nd</li>
    <li>Republic Day, November 15th</li>
    <li>Black Consciousness Day, November 20th (since 2007)</li>
    <li>Christmas Eve, December 24th</li>
    <li>Christmas, December 25th</li>
    <li>Passion of Christ</li>
    <li>Carnival</li>
    <li>Corpus Christi</li>
    <li>the last business day of the year</li>
    </ul>

    \ingroup calendars

    \test the correctness of the returned results is tested
    against a list of known holidays.
  */
  class Brazil : public Calendar {
  public:
    Brazil();
    static Brazil Settlement();
    static Brazil Exchange();

  private:
    Brazil(const std::shared_ptr<Calendar::Impl>& impl);

    class SettlementImpl : public Calendar::WesternImpl {
    public:
      std::string name() const { return "Brazil"; }
      bool isBusinessDay(const Date&) const;
    };

    class ExchangeImpl : public Calendar::WesternImpl {
    public:
      std::string name() const { return "BOVESPA"; }
      bool isBusinessDay(const Date&) const;
    };
  };

}

#endif /* QUANTLIB_BRAZILIAN_CALENDAR_HPP */
