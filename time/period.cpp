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
  Copyright (C) 2004, 2005, 2006, 2007, 2008, 2014 Ferdinando Ametrano
  Copyright (C) 2006 Katiuscia Manzoni
  Copyright (C) 2000, 2001, 2002, 2003 RiskMap srl
  Copyright (C) 2003, 2004, 2005, 2006, 2008 StatPro Italia srl
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

#include <iostream>
#include <base/conversion.hpp>
#include <base/error.hpp>
#include <time/period.hpp>

namespace MathFin {

  static const Period of(const Frequency& f) {
    switch (f) {
    case Frequency::NoFrequency:
      return Period(0, TimeUnit::Days); // same as Period()
    case Frequency::Once:
      return Period(0, TimeUnit::Years);
    case Frequency::Annual:
      return Period(1, TimeUnit::Years);
    case Frequency::Semiannual:
    case Frequency::EveryFourthMonth:
    case Frequency::Quarterly:
    case Frequency::Bimonthly:
    case Frequency::Monthly:
      return Period(12 / as_integer(f), TimeUnit::Months);
    case Frequency::EveryFourthWeek:
    case Frequency::Biweekly:
    case Frequency::Weekly:
      return Period(52 / as_integer(f), TimeUnit::Weeks);
    case Frequency::Daily:
      return Period(1, TimeUnit::Days);
    case Frequency::OtherFrequency:
      std::ostringstream msg;
      MF_FAIL("Unknown frequency (" << f << ")");
    }
  }

  // ---------------------------------------------------------------------------

  Frequency Period::frequency() const {
    // unsigned version
    Size length = std::abs(length_);

    if (length==0) {
      if (units_ == TimeUnit::Years) return Frequency::Once;
      return Frequency::NoFrequency;
    }

    switch (units_) {
    case TimeUnit::Years:
      if (length == 1)
        return Frequency::Annual;
      else
        return Frequency::OtherFrequency;
    case TimeUnit::Months:
      if (12 % length == 0 && length <= 12)
        return Frequency(12 / length);
      else
        return Frequency::OtherFrequency;
    case TimeUnit::Weeks:
      if (length == 1)
        return Frequency::Weekly;
      else if (length == 2)
        return Frequency::Biweekly;
      else if (length == 4)
        return Frequency::EveryFourthWeek;
      else
        return Frequency::OtherFrequency;
    case TimeUnit::Days:
      if (length == 1)
        return Frequency::Daily;
      else
        return Frequency::OtherFrequency;
    default:
      std::ostringstream msg;
      MF_FAIL("Unsupported time unit (" << units_ << ")");
    }
  }

  const Period Period::normalize() const {
    if (length_ != 0) {
      if (units_ == TimeUnit::Months && length_ % 12 == 0) {
        return Period(length_ / 12, TimeUnit::Years);
      }
    }
    return (*this);
  }

  // ---------------------------------------------------------------------------

  Real years(const Period& p) {
    if (p.length()==0) return 0.0;

    switch (p.units()) {
    case TimeUnit::Days:
      MF_FAIL("cannot convert Days into Years");
    case TimeUnit::Weeks:
      MF_FAIL("cannot convert Weeks into Years");
    case TimeUnit::Months:
      return p.length() / 12.0;
    case TimeUnit::Years:
      return p.length();
    default:
      MF_FAIL("Unsupported time unit (" << p.units() << ")");
    }
  }

  Real months(const Period& p) {
    if (p.length()==0) return 0.0;

    switch (p.units()) {
    case TimeUnit::Days:
      MF_FAIL("cannot convert Days into Months");
    case TimeUnit::Weeks:
      MF_FAIL("cannot convert Weeks into Months");
    case TimeUnit::Months:
      return p.length();
    case TimeUnit::Years:
      return p.length()*12.0;
    default:
      MF_FAIL("Unsupported time unit (" << p.units() << ")");
    }
  }

  Real weeks(const Period& p) {
    if (p.length()==0) return 0.0;

    switch (p.units()) {
    case TimeUnit::Days:
      return p.length()/7.0;
    case TimeUnit::Weeks:
      return p.length();
    case TimeUnit::Months:
      MF_FAIL("cannot convert Months into Weeks");
    case TimeUnit::Years:
      MF_FAIL("cannot convert Years into Weeks");
    default:
      MF_FAIL("Unsupported time unit (" << p.units() << ")");
    }
  }

  Real days(const Period& p) {
    if (p.length()==0) return 0.0;

    switch (p.units()) {
    case TimeUnit::Days:
      return p.length();
    case TimeUnit::Weeks:
      return p.length()*7.0;
    case TimeUnit::Months:
      MF_FAIL("cannot convert Months into Days");
    case TimeUnit::Years:
      MF_FAIL("cannot convert Years into Days");
    default:
      MF_FAIL("Unsupported time unit (" << p.units() << ")");
    }
  }

  // ---------------------------------------------------------------------------

  // Limited algebra

  namespace {
    // Add two periods: p1 in years and p2 in months
    Period addYearsAndMonths(const Period& p1, const Period& p2) {
      if (p1.units() == TimeUnit::Years && p2.units() == TimeUnit::Months) {
        return Period(p1.length() * 12 + p2.length(), TimeUnit::Months);
      } else if (p2.length() == 0) {
        return p1;
      } else {
        MF_FAIL("Impossible addition between " << p1 << " and " << p2);
      }
    }

    // Add two periods: p1 in months and p2 in years
    Period addMonthsAndYears(const Period& p1, const Period& p2) {
      if (p1.units() == TimeUnit::Months && p2.units() == TimeUnit::Years) {
        return Period(p1.length() + p2.length() * 12, TimeUnit::Months);
      } else if (p2.length() == 0) {
        return p1;
      } else {
        MF_FAIL("Impossible addition between " << p1 << " and " << p2);
      }
    }

    // Add two periods: p1 in weeks and p2 in days
    Period addWeeksAndDays(const Period& p1, const Period& p2) {
      if (p1.units() == TimeUnit::Weeks && p2.units() == TimeUnit::Days) {
        return Period(p1.length() * 7 + p2.length(), TimeUnit::Days);
      } else if (p2.length() == 0) {
        return p1;
      } else {
        MF_FAIL("Impossible addition between " << p1 << " and " << p2);
      }
    }

    // Add two periods: p1 in days and p2 in weeks
    Period addDaysAndWeeks(const Period& p1, const Period& p2) {
      if (p1.units() == TimeUnit::Days && p2.units() == TimeUnit::Weeks) {
        return Period(p1.length() + p2.length() * 7, TimeUnit::Days);
      } else if (p2.length() == 0) {
        return p1;
      } else {
        MF_FAIL("Impossible addition between " << p1 << " and " << p2);
      }
    }
  }

  Period operator+(const Period& p1, const Period& p2) {
    if (p1.length() == 0) {
      return Period(p2.length(), p2.units());
    } else if (p1.units() == p2.units()) {
      // no conversion needed
      return Period(p1.length() + p2.length(), p1.units());
    } else {
      switch(p1.units()) {
      case TimeUnit::Years:
        return addYearsAndMonths(p1, p2);
      case TimeUnit::Months:
        return addMonthsAndYears(p1, p2);
      case TimeUnit::Weeks:
        return addWeeksAndDays(p1, p2);
      case TimeUnit::Days:
        return addDaysAndWeeks(p1, p2);
      default:
        MF_FAIL("Unsupported addition between " << p1 << " and " << p2);
      }
    }
  }

  Period operator-(const Period& p1, const Period& p2) {
    return p1 + (-p2);
  }

  Period operator/(const Period& p, Integer n) {
    MF_REQUIRE(n != 0, "cannot divide by zero");
    if (p.length() % n == 0) {
      // keep the original units. If the user created a 24-month period,
      // he'll probably want a 12-month one when he halves it.
      return Period(p.length() / n, p.units());
    } else {
      // try to see if we can do the division and convert to a compatible unit.
      TimeUnit units = p.units();
      Integer length = p.length();
      if (units == TimeUnit::Years) {
        length *= 12;
        units = TimeUnit::Months;
      } else if (units == TimeUnit::Weeks) {
        length *= 7;
        units = TimeUnit::Days;
      }
      // In all cases, we require that length be evenly divisible by n.
      MF_REQUIRE(length % n == 0, p << " cannot be divided by " << n);
      return Period(length / n, units);
    }
  }

  // ---------------------------------------------------------------------------

  namespace {
    /**
     * Helpef function used by operator < to determine the minimum and
     * maximum days in the period.
     */
    std::pair<Integer, Integer> daysMinMax(const Period& p) {
      switch (p.units()) {
      case TimeUnit::Days:
        return std::make_pair(p.length(), p.length());
      case TimeUnit::Weeks:
        return std::make_pair(7 * p.length(), 7 * p.length());
      case TimeUnit::Months:
        return std::make_pair(28 * p.length(), 31 * p.length());
      case TimeUnit::Years:
        return std::make_pair(365 * p.length(), 366 * p.length());
      default:
        MF_FAIL( "Unsupported time unit (" << p.units() << ")");
      }
    }

  }

  bool operator<(const Period& p1, const Period& p2) {
    // special cases
    if (p1.length() == 0)
      return p2.length() > 0;
    if (p2.length() == 0)
      return p1.length() < 0;

    // exact comparisons
    if (p1.units() == p2.units())
      return p1.length() < p2.length();
    if (p1.units() == TimeUnit::Months && p2.units() == TimeUnit::Years)
      return p1.length() < 12*p2.length();
    if (p1.units() == TimeUnit::Years && p2.units() == TimeUnit::Months)
      return 12*p1.length() < p2.length();
    if (p1.units() == TimeUnit::Days && p2.units() == TimeUnit::Weeks)
      return p1.length() < 7*p2.length();
    if (p1.units() == TimeUnit::Weeks && p2.units() == TimeUnit::Days)
      return 7*p1.length() < p2.length();

    // inexact comparisons (handled by converting to days and using limits)
    std::pair<Integer, Integer> p1lim = daysMinMax(p1);
    std::pair<Integer, Integer> p2lim = daysMinMax(p2);

    if (p1lim.second < p2lim.first)
      return true;
    else if (p1lim.first > p2lim.second)
      return false;
    else {
      MF_FAIL("Undecidable comparison between " << p1 << " and " << p2);
    }
  }

  // ---------------------------------------------------------------------------

  // formatting

  std::ostream& operator<<(std::ostream& out, const Period& p) {
    return out << io::short_period(p);
  }

  namespace detail {

    std::ostream& operator<<(std::ostream& out,
                             const long_period_holder& holder) {
      Integer n = holder.p.length();
      Integer m = 0;
      switch (holder.p.units()) {
      case TimeUnit::Microseconds:
        return out << n << (n == 1 ? " microsecond" : " microseconds");
      case TimeUnit::Milliseconds:
        return out << n << (n == 1 ? " miillisecond" : " milliseconds");
      case TimeUnit::Seconds:
        return out << n << (n == 1 ? " second" : " seconds");
      case TimeUnit::Minutes:
        return out << n << (n == 1 ? " minute" : " minutes");
      case TimeUnit::Days:
        if (n>=7) {
          m = n/7;
          out << m << (m == 1 ? " week " : " weeks ");
          n = n%7;
        }
        if (n != 0 || m == 0)
          return out << n << (n == 1 ? " day" : " days");
        else
          return out;
      case TimeUnit::Weeks:
        return out << n << (n == 1 ? " week" : " weeks");
      case TimeUnit::Months:
        if (n>=12) {
          m = n/12;
          out << m << (m == 1 ? " year " : " years ");
          n = n%12;
        }
        if (n != 0 || m == 0)
          return out << n << (n == 1 ? " month" : " months");
        else
          return out;
      case TimeUnit::Years:
        return out << n << (n == 1 ? " year" : " years");
      default:
        MF_FAIL("Unknown time unit (" << holder.p.units() << ")");
      }
    }

    std::ostream& operator<<(std::ostream& out,
                             const short_period_holder& holder) {
      Integer n = holder.p.length();
      Integer m = 0;
      switch (holder.p.units()) {
      case TimeUnit::Microseconds:
        return out << n << "us";
      case TimeUnit::Milliseconds:
        return out << n << "ms";
      case TimeUnit::Seconds:
        return out << n << "s";
      case TimeUnit::Minutes:
        return out << n << "m";
      case TimeUnit::Days:
        if (n >= 7) {
          m = n/7;
          out << m << "W";
          n = n%7;
        }
        if (n != 0 || m == 0)
          return out << n << "D";
        else
          return out;
      case TimeUnit::Weeks:
        return out << n << "W";
      case TimeUnit::Months:
        if (n>=12) {
          m = n/12;
          out << n/12 << "Y";
          n = n%12;
        }
        if (n != 0 || m == 0)
          return out << n << "M";
        else
          return out;
      case TimeUnit::Years:
        return out << n << "Y";
      default:
        MF_FAIL("Unknown time unit (" << holder.p.units() << ")");
      }
    }

  }

  namespace io {

    detail::long_period_holder long_period(const Period& p) {
      return detail::long_period_holder(p);
    }

    detail::short_period_holder short_period(const Period& p) {
      return detail::short_period_holder(p);
    }

  }

}
