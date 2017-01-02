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

  QuantLib is free software: you can redistribute it and/or modify it
  under the terms of the QuantLib license.  You should have received a
  copy of the license along with this program; if not, please email
  <quantlib-dev@lists.sf.net>. The license is also available online at
  <http://quantlib.org/license.shtml>.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <tuple>
#include <time/daycounters/actualactual.hpp>
#include <time/period.hpp>
#include <base/error.hpp>

using boost::posix_time::ptime;

namespace MathFin {

  boost::shared_ptr<DayCounter::Impl>
  ActualActual::implementation(ActualActual::Convention c) {
    switch (c) {
    case Convention::ISMA:
    case Convention::Bond:
      return boost::shared_ptr<DayCounter::Impl>(new ISMA_Impl);
    case Convention::ISDA:
    case Convention::Historical:
    case Convention::Actual365:
      return boost::shared_ptr<DayCounter::Impl>(new ISDA_Impl);
    case Convention::AFB:
    case Convention::Euro:
      return boost::shared_ptr<DayCounter::Impl>(new AFB_Impl);
    default:
      MF_FAIL("unknown act/act convention");
    }
  }

  namespace {
    const std::tuple<Date, Date, Integer> getActualRefPeriodAndEstimatedLength(
      const Date& d1,
      const Date& d2,
      const Date& d3,
      const Date& d4
      ) {
      // when the reference period is not specified, try taking
      // it equal to (d1,d2)
      const Date& provisionalStart = (d3 != Date() ? d3 : d1);
      const Date& provisionalEnd = (d4 != Date() ? d4 : d2);

      MF_REQUIRE(provisionalEnd > provisionalStart && provisionalEnd > d1,
                 "invalid reference period: "
                 << "date 1: " << d1
                 << ", date 2: " << d2
                 << ", reference period start: " << provisionalStart
                 << ", reference period end: " << provisionalEnd);

      // estimate roughly the length in months of a period
      Integer months =
        Integer(0.5 + 12 * Real(provisionalEnd - provisionalStart) / 365);

      // for short periods...
      if (0 == months) {
        // ...take the reference period as 1 year from d1
        Period oneYear = 1 * TimeUnit::Years;
        return std::make_tuple(d1, d1 + oneYear, 12);
      } else {
        return std::make_tuple(provisionalStart, provisionalEnd, months);
      }
    }

    const std::tuple<Date, Date, Time> applyRefPeriodAdjustment(
      const Date& d2,
      const Date& refPeriodEnd,
      const Integer months,
      const Time period,
      Time& sum
      ) {
      Integer i = 0;
      for (;;) {
        Date newRefStart = refPeriodEnd  + (months * i) * TimeUnit::Months;
        Date newRefEnd = refPeriodEnd + (months * (i+1)) * TimeUnit::Months;
        if (d2 < newRefEnd) {
          return std::make_tuple(Date(newRefStart), Date(newRefEnd), sum);
        } else {
          sum += period;
          i++;
        }
      }
    }
  } // end of anonymous namespace

  Time ActualActual::ISMA_Impl::yearFraction(
    const Date& d1,
    const Date& d2,
    const Date& d3,
    const Date& d4) const {

    if (d1 == d2) {
      return 0.0;
    }

    if (d1 > d2) {
      return -yearFraction(d2, d1, d3, d4);
    }

    auto actualRefPeriodAndEstimatedLenght =
      getActualRefPeriodAndEstimatedLength(d1, d2, d3, d4);

    const Date& refPeriodStart = std::get<0>(actualRefPeriodAndEstimatedLenght);
    const Date& refPeriodEnd = std::get<1>(actualRefPeriodAndEstimatedLenght);
    const Integer months = std::get<2>(actualRefPeriodAndEstimatedLenght);

    Time period = Real(months) / 12.0;

    if (d2 <= refPeriodEnd) {
      // here refPeriodEnd is a future (notional?) payment date
      if (d1 >= refPeriodStart) {
        // here refPeriodStart is the last (maybe notional)
        // payment date.
        // refPeriodStart <= d1 <= d2 <= refPeriodEnd
        // [maybe the equality should be enforced, since
        // refPeriodStart < d1 <= d2 < refPeriodEnd
        // could give wrong results] ???
        return period * Real(daysBetween(d1, d2)) /
          daysBetween(refPeriodStart,refPeriodEnd);
      } else {
        // here refPeriodStart is the next (maybe notional)
        // payment date and refPeriodEnd is the second next
        // (maybe notional) payment date.
        // d1 < refPeriodStart < refPeriodEnd
        // AND d2 <= refPeriodEnd
        // this case is long first coupon

        // the last notional payment date
        Date previousRef = refPeriodStart - months * TimeUnit::Months;
        if (d2 > refPeriodStart) {
          return yearFraction(d1, refPeriodStart, previousRef, refPeriodStart)
            +
            yearFraction(refPeriodStart, d2, refPeriodStart, refPeriodEnd);
        } else {
          return yearFraction(d1, d2, previousRef, refPeriodStart);
        }
      }
    } else {
      // here refPeriodEnd is the last (notional?) payment date
      // d1 < refPeriodEnd < d2 AND refPeriodStart < refPeriodEnd
      MF_REQUIRE(refPeriodStart <= d1,
                 "Invalid dates: "
                 "d1 < refPeriodStart < refPeriodEnd < d2");
      // now it is: refPeriodStart <= d1 < refPeriodEnd < d2

      // the part from d1 to refPeriodEnd
      Time sum = yearFraction(d1, refPeriodEnd, refPeriodStart, refPeriodEnd);

      // the part from refPeriodEnd to d2
      // count how many regular periods are in [refPeriodEnd, d2],
      // then add the remaining time
      auto adjustedRefPeriod = applyRefPeriodAdjustment(
        d2, refPeriodEnd, months, period, sum);

      const Date& newRefStart = std::get<0>(adjustedRefPeriod);
      const Date& newRefEnd = std::get<1>(adjustedRefPeriod);
      sum = std::get<2>(adjustedRefPeriod);

      sum += yearFraction(
        newRefStart,
        d2,
        newRefStart,
        newRefEnd
        );

      return sum;
    }
  }

  Time ActualActual::ISDA_Impl::yearFraction(
    const Date& d1,
    const Date& d2,
    const Date&,
    const Date&) const {
    if (d1 == d2) {
      return 0.0;
    }

    if (d1 > d2) {
      return -yearFraction(d2, d1, Date(), Date());
    }

    Integer y1 = d1.year();
    Integer y2 = d2.year();
    Real dib1 = (Date::isLeap(y1) ? 366.0 : 365.0);
    Real dib2 = (Date::isLeap(y2) ? 366.0 : 365.0);

    Time sum = y2 - y1 - 1;
    // FLOATING_POINT_EXCEPTION
    sum += daysBetween(d1, Date(1, Month::January, y1+1)) / dib1;
    sum += daysBetween(Date(1, Month::January, y2), d2) / dib2;
    return sum;
  }

  Time ActualActual::AFB_Impl::yearFraction(
    const Date& d1,
    const Date& d2,
    const Date&,
    const Date&
    ) const {

    if (d1 == d2) {
      return 0.0;
    }

    if (d1 > d2) {
      return -yearFraction(d2, d1, Date(), Date());
    }

    // https://en.wikipedia.org/wiki/Day_count_convention#Actual.2FActual_AFB
    //
    // If the difference between d1 and d2 is more than 1 year,
    // count backwards from d2 to find the number of whole years.
    //
    // When counting backwards for this purpose, if the last day of the relevant
    // period is 28 February, the full year should be counted back to the
    // previous 28 February, unless 29 February exists, in which case 29 February
    // should be used.

    // Note that since Date is immutable, we are using ptime for the manipulations
    // here.

    Time numberOfYears = 0.0;

    const ptime p1 = d1.dateTime();
    const ptime p2 = d2.dateTime();
    ptime prev = p2;
    ptime p22 = p2;
    while (prev > p1) {
      prev = (Date(p22) - 1 * TimeUnit::Years).dateTime();
      Date tmp(prev);
      if (tmp.dayOfMonth() == 28
          && tmp.month() == Month::February
          && Date::isLeap(tmp.year())) {
        prev += boost::gregorian::days(1);
      }
      if (prev >= p1) {
        numberOfYears += 1.0;
        p22 = prev;
      }
    }

    const Date d2prime = Date(p22);
    Real daysInYear = 365.0;

    if (Date::isLeap(d2prime.year())) {
      Date d = Date(29, Month::February, d2prime.year());
      if (d2prime > d && d1 <= d) {
        daysInYear += 1.0;
      }
    } else if (Date::isLeap(d1.year())) {
      Date d = Date(29, Month::February, d1.year());
      if (d2prime > d && d1 <= d) {
        daysInYear += 1.0;
      }
    }

    return numberOfYears + daysBetween(d1, d2prime) / daysInYear;
  }

}
