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

/*! \file actual365fixed.hpp
  \brief Actual/365 (Fixed) day counter
*/

#ifndef MATHFIN_ACTUAL_365_FIXED_HPP
#define MATHFIN_ACTUAL_365_FIXED_HPP

#include <string>
#include <time/daycounter.hpp>

namespace MathFin {

  /**
   * Actual/365 (Fixed) day count convention.
   * "Actual/365 (Fixed)" day count convention, also know as
   * "Act/365 (Fixed)", "A/365 (Fixed)", or "A/365F".
   *
   * @warning According to ISDA, "Actual/365" (without "Fixed") is
   * an alias for "Actual/Actual (ISDA)" (see
   *    ActualActual.)  If Actual/365 is not explicitly
   *    specified as fixed in an instrument specification,
   *    you might want to double-check its meaning.
   *
   * @ingroup daycounters
  */
  class Actual365Fixed : public DayCounter {
  private:
    class Impl : public DayCounter::Impl {
    public:
      std::string name() const { return std::string("Actual/365 (Fixed)"); }
      Time yearFraction(
        const Date& d1,
        const Date& d2,
        const Date&,
        const Date&) const {
        return daysBetween(d1,d2) / 365.0;
      }
    };
  public:
    Actual365Fixed()
      : DayCounter(std::shared_ptr<DayCounter::Impl>(
                     new Actual365Fixed::Impl)) {}
  };

}

#endif /* MATHFIN_ACTUAL_365_FIXED_HPP */
