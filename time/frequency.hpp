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
 Copyright (C) 2004, 2005, 2006, 2007 Ferdinando Ametrano
 Copyright (C) 2006 Katiuscia Manzoni
 Copyright (C) 2000, 2001, 2002, 2003 RiskMap srl
 Copyright (C) 2003, 2004, 2005, 2006 StatPro Italia srl

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

#ifndef MATHFIN_FREQUENCY_HPP
#define MATHFIN_FREQUENCY_HPP

#include <iosfwd>

namespace MathFin {

  //! Frequency of events
  /*! \ingroup datetime */
  enum class Frequency { NoFrequency = -1,     //!< null frequency
      Once = 0,             //!< only once, e.g., a zero-coupon
      Annual = 1,           //!< once a year
      Semiannual = 2,       //!< twice a year
      EveryFourthMonth = 3, //!< every fourth month
      Quarterly = 4,        //!< every third month
      Bimonthly = 6,        //!< every second month
      Monthly = 12,         //!< once a month
      EveryFourthWeek = 13, //!< every fourth week
      Biweekly = 26,        //!< every second week
      Weekly = 52,          //!< once a week
      Daily = 365,          //!< once a day
      OtherFrequency = 999  //!< some other unknown frequency
      };

  /*! \relates Frequency */
  std::ostream& operator<<(std::ostream& out, const Frequency& f);
}


#endif /* FINMATH_FREQUENCY_HPP */
