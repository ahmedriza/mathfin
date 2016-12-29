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
  Copyright (C) 2003, 2004, 2005, 2006 StatPro Italia srl
  Copyright (C) 2004, 2005, 2006 Ferdinando Ametrano
  Copyright (C) 2006 Katiuscia Manzoni
  Copyright (C) 2006 Toyin Akin
  Copyright (C) 2015 Klaus Spanderen

  QuantLib is free software: you can redistribute it and/or modify it
  under the terms of the QuantLib license.  You should have received a
  copy of the license along with this program; if not, please email
  <quantlib-dev@lists.sf.net>. The license is also available online at
  <http://quantlib.org/license.shtml>.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <iostream>
#include <time/month.hpp>
#include <base/error.hpp>

namespace MathFin {

  std::ostream& operator<<(std::ostream& out, const Month& m) {
    switch (m) {
    case Month::January:
      return out << "January";
    case Month::February:
      return out << "February";
    case Month::March:
      return out << "March";
    case Month::April:
      return out << "April";
    case Month::May:
      return out << "May";
    case Month::June:
      return out << "June";
    case Month::July:
      return out << "July";
    case Month::August:
      return out << "August";
    case Month::September:
      return out << "September";
    case Month::October:
      return out << "October";
    case Month::November:
      return out << "November";
    case Month::December:
      return out << "December";
    default:
      MF_FAIL("Unknown month (" << m << ")");
    }
  }


}
