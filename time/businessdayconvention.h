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
  Copyright (C) 2003, 2004, 2005, 2006, 2007 StatPro Italia srl
  Copyright (C) 2006 Piter Dias
  Copyright (C) 2014 Paolo Mazzocchi

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

#ifndef FINMATH_BUSINESS_DAY_CONVENTION_H
#define FINMATH_BUSINESS_DAY_CONVENTION_H

#include <iosfwd>

namespace FinMath {

  //! Business Day conventions
  /*! These conventions specify the algorithm used to adjust a date in case
    it is not a valid business day.

    \ingroup datetime
  */
  enum class BusinessDayConvention {
    // ISDA
    Following,                   /*!< Choose the first business day after
                                   the given holiday. */
      ModifiedFollowing,           /*!< Choose the first business day after
                                   the given holiday unless it belongs
                                   to a different month, in which case
                                   choose the first business day before
                                   the holiday. */
      Preceding,                   /*!< Choose the first business
                                   day before the given holiday. */
      // NON ISDA
      ModifiedPreceding,           /*!< Choose the first business day before
                                    the given holiday unless it belongs
                                   to a different month, in which case
                                   choose the first business day after
                                   the holiday. */
      Unadjusted,                  /*!< Do not adjust. */
      HalfMonthModifiedFollowing,  /*!< Choose the first business day after
                                   the given holiday unless that day
                                   crosses the mid-month (15th) or the
                                   end of month, in which case choose
                                   the first business day before the
                                   holiday. */
      Nearest,                   /*!< Choose the nearest business day
                                   to the given holiday. If both the
                                   preceding and following business
                                   days are equally far away, default
                                   to following business day. */
      Unknown
  };


  /*! \relates BusinessDayConvention */
  std::ostream& operator<<(std::ostream&, BusinessDayConvention);

}

#endif /* FINMATH_BUSINESS_DAY_CONVENTION_H */
