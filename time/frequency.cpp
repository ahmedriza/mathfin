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

#include <iostream>
#include <time/frequency.hpp>

namespace MathFin {

  std::ostream& operator<<(std::ostream& out, const Frequency& f) {
    switch (f) {
    case Frequency::NoFrequency:
      return out << "No-Frequency";
    case Frequency::Once:
      return out << "Once";
    case Frequency::Annual:
      return out << "Annual";
    case Frequency::Semiannual:
      return out << "Semiannual";
    case Frequency::EveryFourthMonth:
      return out << "Every-Fourth-Month";
    case Frequency::Quarterly:
      return out << "Quarterly";
    case Frequency::Bimonthly:
      return out << "Bimonthly";
    case Frequency::Monthly:
      return out << "Monthly";
    case Frequency::EveryFourthWeek:
      return out << "Every-fourth-week";
    case Frequency::Biweekly:
      return out << "Biweekly";
    case Frequency::Weekly:
      return out << "Weekly";
    case Frequency::Daily:
      return out << "Daily";
    case Frequency::OtherFrequency:
      return out << "Unknown frequency";
    }
  }

}
