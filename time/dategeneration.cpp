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

#include <time/dategeneration.hpp>
#include <base/error.hpp>

namespace MathFin {

  std::ostream& operator<<(std::ostream& out, const DateGeneration& r) {
    switch (r) {
    case DateGeneration::Backward:
      return out << "Backward";
    case DateGeneration::Forward:
      return out << "Forward";
    case DateGeneration::Zero:
      return out << "Zero";
    case DateGeneration::ThirdWednesday:
      return out << "ThirdWednesday";
    case DateGeneration::Twentieth:
      return out << "Twentieth";
    case DateGeneration::TwentiethIMM:
      return out << "TwentiethIMM";
    case DateGeneration::OldCDS:
      return out << "OldCDS";
    case DateGeneration::CDS:
      return out << "CDS";
    default:
      MF_FAIL("Unknown DateGeneration::Rule (" << r << ")");
    }
  }

}
