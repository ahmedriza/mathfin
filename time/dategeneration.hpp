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
  Copyright (C) 2007 Ferdinando Ametrano
  Copyright (C) 2008 StatPro Italia srl

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
 * @file dategenerationrule.hpp
 * @brief date generation rule
 */

#ifndef MATHFIN_DATE_GENERATION_HPP
#define MATHFIN_DATE_GENERATION_HPP

#include <iosfwd>

namespace MathFin {

  /**
   * Date-generation rule.
   * These conventions specify the rule used to generate dates in a
   * Schedule.
   *
   * @ingroup datetime
   */
  enum class DateGeneration {
      Backward,       /*!< Backward from termination date to
                      effective date. */
      Forward,        /*!< Forward from effective date to
                        termination date. */
      Zero,           /*!< No intermediate dates between effective date
                        and termination date. */
      ThirdWednesday, /*!< All dates but effective date and termination
                        date are taken to be on the third wednesday
                        of their month (with forward calculation.) */
      Twentieth,      /*!< All dates but the effective date are
                        taken to be the twentieth of their
                        month (used for CDS schedules in
                        emerging markets.)  The termination
                        date is also modified. */
      TwentiethIMM,   /*!< All dates but the effective date are
                        taken to be the twentieth of an IMM
                        month (used for CDS schedules.)  The
                        termination date is also modified. */
      OldCDS,         /*!< Same as TwentiethIMM with unrestricted date
                        ends and log/short stub coupon period (old
                        CDS convention). */
      CDS             /*!< Credit derivatives standard rule since 'Big
                        Bang' changes in 2009.  */
  };

  /**
   * @relates DateGeneration
   */
  std::ostream& operator<<(std::ostream&, const DateGeneration&);
}

#endif
