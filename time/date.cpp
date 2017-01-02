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
#include <time/date.hpp>
#include <base/error.hpp>
#include <base/conversion.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

using boost::posix_time::ptime;
using boost::posix_time::time_duration;

namespace MathFin {

  // Helper functions used in other parts of the code.
  namespace {
    const boost::gregorian::date& serialNumberDateReference() {
      static const boost::gregorian::date dateReference(
        1899, boost::gregorian::Dec, 30);
      return dateReference;
    }

#define compatibleEnums \
    (int(boost::date_time::Monday)      +1 == as_integer(Weekday::Monday) \
     && int(boost::date_time::Tuesday)  +1 == as_integer(Weekday::Tuesday) \
     && int(boost::date_time::Wednesday)+1 == as_integer(Weekday::Wednesday) \
     && int(boost::date_time::Thursday) +1 == as_integer(Weekday::Thursday) \
     && int(boost::date_time::Friday)   +1 == as_integer(Weekday::Friday) \
     && int(boost::date_time::Saturday) +1 == as_integer(Weekday::Saturday) \
     && int(boost::date_time::Sunday)   +1 == as_integer(Weekday::Sunday) \
     && int(boost::date_time::Jan) == as_integer(Month::January)        \
     && int(boost::date_time::Feb) == as_integer(Month::February)       \
     && int(boost::date_time::Mar) == as_integer(Month::March)          \
     && int(boost::date_time::Apr) == as_integer(Month::April)          \
     && int(boost::date_time::May) == as_integer(Month::May)            \
     && int(boost::date_time::Jun) == as_integer(Month::June)           \
     && int(boost::date_time::Jul) == as_integer(Month::July)           \
     && int(boost::date_time::Aug) == as_integer(Month::August)         \
     && int(boost::date_time::Sep) == as_integer(Month::September)      \
     && int(boost::date_time::Oct) == as_integer(Month::October)        \
     && int(boost::date_time::Nov) == as_integer(Month::November)       \
     && int(boost::date_time::Dec) == as_integer(Month::December))

    template <bool compatible>
    Weekday mapBoostDateType2MF(boost::gregorian::greg_weekday d) {
      if (compatible) {
        return Weekday(d.as_number() + 1);
      } else {
        switch (d) {
        case boost::date_time::Monday   : return Weekday::Monday;
        case boost::date_time::Tuesday  : return Weekday::Tuesday;
        case boost::date_time::Wednesday: return Weekday::Wednesday;
        case boost::date_time::Thursday : return Weekday::Thursday;
        case boost::date_time::Friday   : return Weekday::Friday;
        case boost::date_time::Saturday : return Weekday::Saturday;
        case boost::date_time::Sunday   : return Weekday::Sunday;
        default:
          MF_FAIL("Unknown boost date_time day of week given");
        }
      }
    }

    template <bool compatible>
    Month mapBoostDateType2MF(boost::gregorian::greg_month m) {
      if (compatible) {
        return Month(m.as_number());
      } else {
        switch (m) {
        case boost::date_time::Jan : return Month::January;
        case boost::date_time::Feb : return Month::February;
        case boost::date_time::Mar : return Month::March;
        case boost::date_time::Apr : return Month::April;
        case boost::date_time::May : return Month::May;
        case boost::date_time::Jun : return Month::June;
        case boost::date_time::Jul : return Month::July;
        case boost::date_time::Aug : return Month::August;
        case boost::date_time::Sep : return Month::September;
        case boost::date_time::Oct : return Month::October;
        case boost::date_time::Nov : return Month::November;
        case boost::date_time::Dec : return Month::December;
        default:
          MF_FAIL("Unknown boost date_time month of week given");
        }
      }
    }

    template <bool compatible>
    boost::gregorian::greg_month mapMFDateType2Boost(Month m) {
      if (compatible) {
        return boost::gregorian::greg_month(as_integer(m));
      } else {
        switch (m) {
        case Month::January  : return boost::date_time::Jan;
        case Month::February : return boost::date_time::Feb;
        case Month::March    : return boost::date_time::Mar;
        case Month::April    : return boost::date_time::Apr;
        case Month::May      : return boost::date_time::May;
        case Month::June     : return boost::date_time::Jun;
        case Month::July     : return boost::date_time::Jul;
        case Month::August   : return boost::date_time::Aug;
        case Month::September: return boost::date_time::Sep;
        case Month::October  : return boost::date_time::Oct;
        case Month::November : return boost::date_time::Nov;
        case Month::December : return boost::date_time::Dec;
        default:
          MF_FAIL("Unknown boost date_time month of week given");
        }
      }
    }

    boost::gregorian::date gregorianDate(Year y, Month m, Day d) {
      MF_REQUIRE(y > 1900 && y < 2200,
                 "year " << y << " out of bound. It must be in [1901,2199]");
      MF_REQUIRE(Integer(m) > 0 && Integer(m) < 13,
                 "month " << Integer(m)
                 << " outside January-December range [1,12]");

      const boost::gregorian::greg_month gregorianMonth =
        mapMFDateType2Boost<compatibleEnums>(m);

      const Day endOfMonthDay =
        boost::gregorian::gregorian_calendar::end_of_month_day(y, gregorianMonth);
      MF_REQUIRE(d <= endOfMonthDay && d > 0,
                 "Day outside month (" << m << ") day-range "
                 << "[1," << endOfMonthDay << "]");

      return boost::gregorian::date(y, gregorianMonth, d);
    }
  }

  // ---------------------------------------------------------------------------


  Date::Date() : dateTime_(serialNumberDateReference()) {}

  Date::Date(Date::serial_type serialNumber)
    : dateTime_(serialNumberDateReference() + boost::gregorian::days(serialNumber)) {
    checkSerialNumber(serialNumber);
  }

  Date::Date(Day d, Month m, Year y) : dateTime_(gregorianDate(y, m, d)) {}

  Date::Date(const ptime& localTime) : dateTime_(localTime) {}

  Date::Date(Day d,
             Month m,
             Year y,
             Hour hours,
             Minute minutes,
             Second seconds,
             Millisecond millisec,
             Microsecond microsec)
    : dateTime_(
      gregorianDate(y, m, d),
      boost::posix_time::time_duration(
        hours, minutes, seconds,
        millisec * (time_duration::ticks_per_second()/1000)
        + microsec*(time_duration::ticks_per_second()/1000000)))
  {}

  // ---------------------------------------------------------------------------

  Weekday Date::weekday() const {
    return mapBoostDateType2MF<compatibleEnums>(dateTime_.date().day_of_week());
  }

  Day Date::dayOfMonth() const {
    return dateTime_.date().day();
  }

  Day Date::dayOfYear() const {
    return dateTime_.date().day_of_year();
  }

  Month Date::month() const {
    return mapBoostDateType2MF<compatibleEnums>(dateTime_.date().month());
  }

  Year Date::year() const {
    return dateTime_.date().year();
  }

  Date::serial_type Date::serialNumber() const {
    const Date::serial_type n = (
      dateTime_.date() - serialNumberDateReference()).days();
    checkSerialNumber(n);
    return n;
  }

  Hour Date::hours() const {
    return dateTime_.time_of_day().hours();
  }

  Minute Date::minutes() const {
    return dateTime_.time_of_day().minutes();
  }

  Second Date::seconds() const {
    return dateTime_.time_of_day().seconds();
  }

  Millisecond Date::milliseconds() const {
    return dateTime_.time_of_day().fractional_seconds()
      / (ticksPerSecond()/1000);
  }

  Microsecond Date::microseconds() const {
    return (dateTime_.time_of_day().fractional_seconds()
            - milliseconds()*(time_duration::ticks_per_second()/1000))
      / (ticksPerSecond()/1000000);
  }

  Time Date::fractionOfDay() const {
    const time_duration t = dateTime_.time_of_day();
    const Time seconds = (t.hours()*60.0 + t.minutes())*60.0 + t.seconds()
      + Real(t.fractional_seconds()) / ticksPerSecond();
    return seconds / 86400.0; // ignore any DST hocus-pocus
  }

  Time Date::fractionOfSecond() const {
    return dateTime_.time_of_day().fractional_seconds()
      / Real(ticksPerSecond());
  }

  // ---------------------------------------------------------------------------
  // static private members.

  Date::serial_type Date::minimumSerialNumber() {
    return 367;       // Jan 1st, 1901
  }

  Date::serial_type Date::maximumSerialNumber() {
    return 109574;    // Dec 31st, 2199
  }

  void Date::checkSerialNumber(Date::serial_type serialNumber) {
    // TODO
    // Need to implement std::ostream& operator<<(std::ostream&, const Date&);
    /*
    MF_REQUIRE(serialNumber >= minimumSerialNumber() &&
               serialNumber <= maximumSerialNumber(),
               "Date's serial number (" << serialNumber << ") outside "
               "allowed range [" << minimumSerialNumber() <<
               "-" << maximumSerialNumber() << "], i.e. [" <<
               minDate() << "-" << maxDate() << "]");
    */

    MF_REQUIRE(serialNumber >= minimumSerialNumber() &&
               serialNumber <= maximumSerialNumber(),
               "Date's serial number (" << serialNumber << ") outside "
               "allowed range [" << minimumSerialNumber() <<
               ", ... ," << maximumSerialNumber() << "]";
      );
  }

  // ---------------------------------------------------------------------------
  // static public methods

  Date Date::todaysDate() {
    boost::gregorian::date current_date(boost::gregorian::day_clock::local_day());
    return Date(
      Day(current_date.day()),
      Month(current_date.month().as_number()),
      Year(current_date.year())
      );
  }

  Date Date::minDate() {
    static const Date minimumDate(minimumSerialNumber());
    return minimumDate;
  }

  Date Date::maxDate() {
    static const Date maximumDate(maximumSerialNumber());
    return maximumDate;
  }

  bool Date::isLeap(Year y) {
    return boost::gregorian::gregorian_calendar::is_leap_year(y);
  }

  Date Date::endOfMonth(const Date& d) {
    const Month m = d.month();
    const Year y = d.year();
    const Day eoM = boost::gregorian::gregorian_calendar::end_of_month_day(
      d.year(), mapMFDateType2Boost<compatibleEnums>(d.month()));
    return Date(eoM, m, y);
  }

  bool Date::isEndOfMonth(const Date& d) {
    return d.dayOfMonth() ==
      boost::gregorian::gregorian_calendar::end_of_month_day(
        d.year(), mapMFDateType2Boost<compatibleEnums>(d.month()));
  }

  Date Date::nextWeekday(const Date& d, Weekday dayOfWeek) {
    Weekday wd = d.weekday();
    return d + ((wd > dayOfWeek ? 7 : 0) - as_integer(wd) + as_integer(dayOfWeek));
  }

  Date Date::nthWeekday(Size nth, Weekday dayOfWeek,
                        Month m, Year y) {
    MF_REQUIRE(nth>0,
               "zeroth day of week in a given (month, year) is undefined");
    MF_REQUIRE(nth<6,
               "no more than 5 weekday in a given (month, year)");
    Weekday first = Date(1, m, y).weekday();
    Size skip = nth - (dayOfWeek >= first ? 1 : 0);
    return Date((1 + as_integer(dayOfWeek) + skip * 7) - as_integer(first), m, y);
  }

  Date Date::localDateTime() {
    return Date(boost::posix_time::microsec_clock::local_time());
  }

  Date Date::universalDateTime() {
    return Date(boost::posix_time::microsec_clock::universal_time());
  }

  const Size Date::ticksPerSecond() {
    return time_duration::ticks_per_second();
  }

  // ---------------------------------------------------------------------------
  // date algebra

  namespace {
    void advance(ptime& dt, Integer n, TimeUnit units) {
      if (units == TimeUnit::Days) {
        dt += boost::gregorian::days(n);
      } else if (units == TimeUnit::Weeks) {
        dt += boost::gregorian::weeks(n);
      } else if (units == TimeUnit::Months || units == TimeUnit::Years) {
        const boost::gregorian::date date = dt.date();
        const Day endOfMonthDay =
          boost::gregorian::gregorian_calendar::end_of_month_day(
            date.year(), date.month());
        if (units == TimeUnit::Months) {
          dt += boost::gregorian::months(n);
        } else {
          dt += boost::gregorian::years(n);
        }
        if (date.day() == endOfMonthDay) {
          // avoid snap-to-end-of-month behavior of boost::date_time
          const Day newEndOfMonthDay
            = boost::gregorian::gregorian_calendar::end_of_month_day(
              dt.date().year(),
              dt.date().month()
              );
          if (newEndOfMonthDay > endOfMonthDay) {
            dt -= boost::gregorian::days(newEndOfMonthDay - endOfMonthDay);
          }
        }
      } else {
        MF_FAIL("Unsupported time units: " << units);
      }
    }
  } // end anonymous namespace

  Date Date::operator+(Date::serial_type days) const {
    return Date(dateTime_ + boost::gregorian::days(days));
  }

  Date Date::operator-(Date::serial_type days) const {
    return Date(dateTime_ - boost::gregorian::days(days));
  }

  Date Date::operator+(const Period& p) const {
    ptime dateTime = dateTime_;
    advance(dateTime, p.length(), p.units());
    return Date(dateTime);
  }

  Date Date::operator-(const Period& p) const {
    ptime dateTime = dateTime_;
    advance(dateTime, -p.length(), p.units());
    return Date(dateTime);
  }

  // ---------------------------------------------------------------------------

  // difference in days between dates
  Date::serial_type operator-(const Date& d1, const Date& d2) {
    return (d1.dateTime().date() - d2.dateTime().date()).days();
  }

  // Difference in days (including fraction of days) between dates
  Time daysBetween(const Date& d1, const Date& d2) {
    const Date::serial_type days = d2 - d1;
    return days + d2.fractionOfDay() - d1.fractionOfDay();
  }

  // Difference in whole years between dates
  // Used in the implementation of Actual/Actual (AFB) DayCounter
  Integer yearsBetween(const Date& d1, const Date& d2) {
    ptime p1 = d1.dateTime();
    ptime p2 = d2.dateTime();
    return 0;
  }

  // ---------------------------------------------------------------------------

  bool operator==(const Date& d1, const Date& d2) {
    return (d1.dateTime() == d2.dateTime());
  }

  bool operator!=(const Date& d1, const Date& d2) {
    return (d1.dateTime() != d2.dateTime());
  }

  bool operator<(const Date& d1, const Date& d2) {
    return (d1.dateTime() < d2.dateTime());
  }

  bool operator<=(const Date& d1, const Date& d2) {
    return (d1.dateTime() <= d2.dateTime());
  }

  bool operator>(const Date& d1, const Date& d2) {
    return (d1.dateTime() > d2.dateTime());
  }

  bool operator>=(const Date& d1, const Date& d2) {
    return (d1.dateTime() >= d2.dateTime());
  }

  // ---------------------------------------------------------------------------

  std::ostream& operator<<(std::ostream& out, const Date& d) {
    out << d.year() << "-"
        << std::setw(2) << std::setfill('0') << as_integer(d.month()) << "-"
        << std::setw(2) << std::setfill('0') << d.dayOfMonth()
        << "T"
        << std::setw(2) << std::setfill('0') << d.hours() << ":"
        << std::setw(2) << std::setfill('0') << d.minutes() << ":"
        << std::setw(2) << std::setfill('0') << d.seconds() << ","
        << std::setw(3) << std::setfill('0') << d.milliseconds()
        << std::setw(3) << std::setfill('0') << d.microseconds();

    return out;
  }

  // ---------------------------------------------------------------------------


}
