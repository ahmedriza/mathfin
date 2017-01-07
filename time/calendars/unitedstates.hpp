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
  Copyright (C) 2003, 2004, 2005, 2006 StatPro Italia srl
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

/*! \file unitedstates.hpp
  \brief US calendars
*/

#ifndef MATHFIN_UNITED_STATES_CALENDAR_HPP
#define MATHFIN_UNITED_STATES_CALENDAR_HPP

#include <time/calendar.hpp>

namespace MathFin {

  //! United States calendars
  /*! Public holidays (see: http://www.opm.gov/fedhol/):
    <ul>
    <li>Saturdays</li>
    <li>Sundays</li>
    <li>New Year's Day, January 1st (possibly moved to Monday if
    actually on Sunday, or to Friday if on Saturday)</li>
    <li>Martin Luther King's birthday, third Monday in January (since
    1983)</li>
    <li>Presidents' Day (a.k.a. Washington's birthday),
    third Monday in February</li>
    <li>Memorial Day, last Monday in May</li>
    <li>Independence Day, July 4th (moved to Monday if Sunday or
    Friday if Saturday)</li>
    <li>Labor Day, first Monday in September</li>
    <li>Columbus Day, second Monday in October</li>
    <li>Veterans' Day, November 11th (moved to Monday if Sunday or
    Friday if Saturday)</li>
    <li>Thanksgiving Day, fourth Thursday in November</li>
    <li>Christmas, December 25th (moved to Monday if Sunday or Friday
    if Saturday)</li>
    </ul>

    Holidays for the stock exchange (data from http://www.nyse.com):
    <ul>
    <li>Saturdays</li>
    <li>Sundays</li>
    <li>New Year's Day, January 1st (possibly moved to Monday if
    actually on Sunday)</li>
    <li>Martin Luther King's birthday, third Monday in January (since
    1998)</li>
    <li>Presidents' Day (a.k.a. Washington's birthday),
    third Monday in February</li>
    <li>Good Friday</li>
    <li>Memorial Day, last Monday in May</li>
    <li>Independence Day, July 4th (moved to Monday if Sunday or
    Friday if Saturday)</li>
    <li>Labor Day, first Monday in September</li>
    <li>Thanksgiving Day, fourth Thursday in November</li>
    <li>Presidential election day, first Tuesday in November of election
    years (until 1980)</li>
    <li>Christmas, December 25th (moved to Monday if Sunday or Friday
    if Saturday)</li>
    <li>Special historic closings (see
    http://www.nyse.com/pdfs/closings.pdf)</li>
    </ul>

    Holidays for the government bond market (data from
    http://www.bondmarkets.com):
    <ul>
    <li>Saturdays</li>
    <li>Sundays</li>
    <li>New Year's Day, January 1st (possibly moved to Monday if
    actually on Sunday)</li>
    <li>Martin Luther King's birthday, third Monday in January (since
    1983)</li>
    <li>Presidents' Day (a.k.a. Washington's birthday),
    third Monday in February</li>
    <li>Good Friday</li>
    <li>Memorial Day, last Monday in May</li>
    <li>Independence Day, July 4th (moved to Monday if Sunday or
    Friday if Saturday)</li>
    <li>Labor Day, first Monday in September</li>
    <li>Columbus Day, second Monday in October</li>
    <li>Veterans' Day, November 11th (moved to Monday if Sunday or
    Friday if Saturday)</li>
    <li>Thanksgiving Day, fourth Thursday in November</li>
    <li>Christmas, December 25th (moved to Monday if Sunday or Friday
    if Saturday)</li>
    </ul>

    Holidays for the North American Energy Reliability Council
    (data from http://www.nerc.com/~oc/offpeaks.html):
    <ul>
    <li>Saturdays</li>
    <li>Sundays</li>
    <li>New Year's Day, January 1st (possibly moved to Monday if
    actually on Sunday)</li>
    <li>Memorial Day, last Monday in May</li>
    <li>Independence Day, July 4th (moved to Monday if Sunday)</li>
    <li>Labor Day, first Monday in September</li>
    <li>Thanksgiving Day, fourth Thursday in November</li>
    <li>Christmas, December 25th (moved to Monday if Sunday)</li>
    </ul>

    \ingroup calendars

    \test the correctness of the returned results is tested
    against a list of known holidays.
  */
  class UnitedStates : public Calendar {
  public:
    UnitedStates();
    static UnitedStates Settlement();
    static UnitedStates NYSE();
    static UnitedStates GovernmentBond();
    static UnitedStates NERC();

  private:
    UnitedStates(const std::shared_ptr<Calendar::Impl>& impl);

    class SettlementImpl : public Calendar::WesternImpl {
    public:
      std::string name() const { return "US settlement"; }
      bool isBusinessDay(const Date&) const;
    };

    class NyseImpl : public Calendar::WesternImpl {
    public:
      std::string name() const { return "New York stock exchange"; }
      bool isBusinessDay(const Date&) const;
    };

    class GovernmentBondImpl : public Calendar::WesternImpl {
    public:
      std::string name() const { return "US government bond market"; }
      bool isBusinessDay(const Date&) const;
    };

    class NercImpl : public Calendar::WesternImpl {
    public:
      std::string name() const {
        return "North American Energy Reliability Council";
      }
      bool isBusinessDay(const Date&) const;
    };
  };

}

#endif /* MATHFIN_UNITED_STATES_CALENDAR_HPP */
