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
  Copyright (C) 2006 Piter Dias
  Copyright (C) 2011 StatPro Italia srl

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

#include <time/daycounters/business252.hpp>
#include <map>

namespace MathFin {

  namespace {
    bool sameYear(const Date& d1, const Date& d2) {
      return d1.year() == d2.year();
    }

    bool sameMonth(const Date& d1, const Date& d2) {
      return d1.year() == d2.year() && d1.month() == d2.month();
    }
  }

  std::string Business252::Impl::name() const {
    std::ostringstream out;
    out << "Business/252(" << calendar_.name() << ")";
    return out.str();
  }

  Date::serial_type Business252::Impl::dayCount(
    const Date& d1,
    const Date& d2) const {
    return calendar_.businessDaysBetween(d1, d2);
  }

  Time Business252::Impl::yearFraction(
    const Date& d1,
    const Date& d2,
    const Date&,
    const Date&) const {
    return dayCount(d1, d2) / 252.0;
  }

}
