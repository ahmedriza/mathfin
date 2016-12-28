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

#include <time/weekday.hpp>
#include <base/types.hpp>
#include <base/error.hpp>

namespace MathFin {

  std::ostream& operator<<(std::ostream& out, const Weekday& w) {
    return out << io::long_weekday(w);
  }

  namespace detail {

    std::ostream& operator<<(std::ostream& out,
                             const long_weekday_holder& holder) {
      switch (holder.d) {
      case Weekday::Sunday:
        return out << "Sunday";
      case Weekday::Monday:
        return out << "Monday";
      case Weekday::Tuesday:
        return out << "Tuesday";
      case Weekday::Wednesday:
        return out << "Wednesday";
      case Weekday::Thursday:
        return out << "Thursday";
      case Weekday::Friday:
        return out << "Friday";
      case Weekday::Saturday:
        return out << "Saturday";
      default:
        MF_FAIL("unknown weekday");
      }
    }

    std::ostream& operator<<(std::ostream& out,
                             const short_weekday_holder& holder) {
      switch (holder.d) {
      case Weekday::Sunday:
        return out << "Sun";
      case Weekday::Monday:
        return out << "Mon";
      case Weekday::Tuesday:
        return out << "Tue";
      case Weekday::Wednesday:
        return out << "Wed";
      case Weekday::Thursday:
        return out << "Thu";
      case Weekday::Friday:
        return out << "Fri";
      case Weekday::Saturday:
        return out << "Sat";
      default:
        MF_FAIL("unknown weekday");
      }
    }

    std::ostream& operator<<(std::ostream& out,
                             const shortest_weekday_holder& holder) {
      switch (holder.d) {
      case Weekday::Sunday:
        return out << "Su";
      case Weekday::Monday:
        return out << "Mo";
      case Weekday::Tuesday:
        return out << "Tu";
      case Weekday::Wednesday:
        return out << "We";
      case Weekday::Thursday:
        return out << "Th";
      case Weekday::Friday:
        return out << "Fr";
      case Weekday::Saturday:
        return out << "Sa";
      default:
        MF_FAIL("unknown weekday");
      }
    }

  }

  namespace io {

    detail::long_weekday_holder long_weekday(Weekday d) {
      return detail::long_weekday_holder(d);
    }

    detail::short_weekday_holder short_weekday(Weekday d) {
      return detail::short_weekday_holder(d);
    }

    detail::shortest_weekday_holder shortest_weekday(Weekday d) {
      return detail::shortest_weekday_holder(d);
    }

  }
}
