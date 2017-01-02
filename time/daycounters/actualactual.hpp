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

/**
 * @file actualactual.hpp
 * @brief act/act day counters
 */

#ifndef MATHFIN_ACTUALACTUAL_H
#define MATHFIN_ACTUALACTUAL_H

#include <time/daycounter.hpp>

namespace MathFin {

  /**
   * Actual/Actual day count
   * The day count can be calculated according to:
   *
   * - the ISDA convention, also known as "Actual/Actual (Historical)",
   *   "Actual/Actual", "Act/Act", and according to ISDA also "Actual/365",
   *   "Act/365", and "A/365";
   * - the ISMA and US Treasury convention, also known as
   *   "Actual/Actual (Bond)";
   * - the AFB convention, also known as "Actual/Actual (Euro)".
   *
   * @see http://www.isda.org/publications/pdf/Day-Count-Fracation1999.pdf
   *
   * @see https://en.wikipedia.org/wiki/Day_count_convention
   * @ingroup daycounters
   */
  class ActualActual : public DayCounter {

  public:
    enum class Convention { ISMA,
        Bond,
        ISDA,
        Historical,
        Actual365,
        AFB,
        Euro
        };

  public:
    ActualActual(Convention c = Convention::ISDA)
      : DayCounter(implementation(c)) {}

  private:
    class ISMA_Impl : public DayCounter::Impl {
    public:
      std::string name() const {
        return std::string("Actual/Actual (ISMA)");
      }

      Time yearFraction(
        const Date& d1,
        const Date& d2,
        const Date& refPeriodStart,
        const Date& refPeriodEnd) const;
    };

    class ISDA_Impl : public DayCounter::Impl {
    public:
      std::string name() const {
        return std::string("Actual/Actual (ISDA)");
      }

      Time yearFraction(
        const Date& d1,
        const Date& d2,
        const Date& refPeriodStart,
        const Date& refPeriodEnd) const;
    };

    class AFB_Impl : public DayCounter::Impl {
    public:
      std::string name() const {
        return std::string("Actual/Actual (AFB)");
      }

      Time yearFraction(
        const Date& d1,
        const Date& d2,
        const Date& refPeriodStart,
        const Date& refPeriodEnd) const;
    };

    static boost::shared_ptr<DayCounter::Impl> implementation(Convention c);

  };


}

#endif /* MATHFIN_ACTUALACTUAL_H */
