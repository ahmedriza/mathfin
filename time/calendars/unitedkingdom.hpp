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

#ifndef MATHFIN_UNITED_KINGDOM_CALENDAR_HPP
#define MATHFIN_UNITED_KINGDOM_CALENDAR_HPP

#include <time/calendar.hpp>

namespace MathFin {

  /** United Kingdom calendars
   * Public holidays (data from http://www.dti.gov.uk/er/bankhol.htm):
   * <ul>
   *   <li>Saturdays</li>
   *   <li>Sundays</li>
   *   <li>New Year's Day, January 1st (possibly moved to Monday)</li>
   *   <li>Good Friday</li>
   *   <li>Easter Monday</li>
   *   <li>Early May Bank Holiday, first Monday of May</li>
   *   <li>Spring Bank Holiday, last Monday of May</li>
   *   <li>Summer Bank Holiday, last Monday of August</li>
   *   <li>Christmas Day, December 25th (possibly moved to Monday or
   *    Tuesday)</li>
   *   <li>Boxing Day, December 26th (possibly moved to Monday or
   *    Tuesday)</li>
   * </ul>
   *
   * Holidays for the stock exchange:
   * <ul>
   *   <li>Saturdays</li>
   *   <li>Sundays</li>
   *   <li>New Year's Day, January 1st (possibly moved to Monday)</li>
   *   <li>Good Friday</li>
   *   <li>Easter Monday</li>
   *   <li>Early May Bank Holiday, first Monday of May</li>
   *   <li>Spring Bank Holiday, last Monday of May</li>
   *   <li>Summer Bank Holiday, last Monday of August</li>
   *   <li>Christmas Day, December 25th (possibly moved to Monday or
   *    Tuesday)</li>
   *   <li>Boxing Day, December 26th (possibly moved to Monday or
   *    Tuesday)</li>
   * </ul>

   * Holidays for the metals exchange:
   * <ul>
   *   <li>Saturdays</li>
   *   <li>Sundays</li>
   *   <li>New Year's Day, January 1st (possibly moved to Monday)</li>
   *   <li>Good Friday</li>
   *   <li>Easter Monday</li>
   *   <li>Early May Bank Holiday, first Monday of May</li>
   *   <li>Spring Bank Holiday, last Monday of May</li>
   *   <li>Summer Bank Holiday, last Monday of August</li>
   *   <li>Christmas Day, December 25th (possibly moved to Monday or
   *    Tuesday)</li>
   *   <li>Boxing Day, December 26th (possibly moved to Monday or
   *    Tuesday)</li>
   * </ul>
   *
   * @ingroup calendars
   */
  class UnitedKingdom : public Calendar {
  public:
    UnitedKingdom();
    static UnitedKingdom Settlement();  //!< generic settlement calendar
    static UnitedKingdom Exchange();  //!< London stock-exchange calendar
    static UnitedKingdom Metals();  //|< London metals-exchange calendar

  private:
    UnitedKingdom(const std::shared_ptr<Calendar::Impl>& impl);

    class SettlementImpl : public Calendar::WesternImpl {
    public:
      std::string name() const { return "UK settlement"; }
      bool isBusinessDay(const Date&) const;
    };

    class ExchangeImpl : public Calendar::WesternImpl {
    public:
      std::string name() const { return "London stock exchange"; }
      bool isBusinessDay(const Date&) const;
    };

    class MetalsImpl : public Calendar::WesternImpl {
    public:
      std::string name() const { return "London metals exchange"; }
      bool isBusinessDay(const Date&) const;
    };
  };

}

#endif /* MATHFIN_UNITED_KINGDOM_CALENDAR_HPP */
