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

#include <time/businessdayconvention.hpp>
#include <base/error.hpp>
#include <iostream>

namespace MathFin {

  std::ostream& operator<<(std::ostream& out, const BusinessDayConvention& b) {
    switch (b) {
    case BusinessDayConvention::Following:
      return out << "Following";
    case BusinessDayConvention::ModifiedFollowing:
      return out << "Modified Following";
    case BusinessDayConvention::HalfMonthModifiedFollowing:
      return out << "Half-Month Modified Following";
    case BusinessDayConvention::Preceding:
      return out << "Preceding";
    case BusinessDayConvention::ModifiedPreceding:
      return out << "Modified Preceding";
    case BusinessDayConvention::Unadjusted:
      return out << "Unadjusted";
    case BusinessDayConvention::Nearest:
      return out << "Nearest";
    default:
      MF_FAIL("Unknown BusinessDayConvention (" << int(b) << ")");
    }
  }
}
