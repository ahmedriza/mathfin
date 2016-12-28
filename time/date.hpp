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

#ifndef MATHFIN_DATE_HPP
#define MATHFIN_DATE_HPP

#include <time/period.hpp>
#include <time/month.hpp>
#include <time/weekday.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>

namespace MathFin {

  /**
   * Day number
   * @ingroup datetime
   */
  typedef Integer Day;

  /**
   * Year number
   * @ingroup datetime
   */
  typedef Integer Year;

  /**
   * Hour number
   * @ingroup datetime
   */
  typedef boost::posix_time::hours::hour_type Hour;

  /**
   * Minute number
   * @ingroup datetime
   */
  typedef boost::posix_time::minutes::min_type Minute;

  /**
   * Second number
   * @ingroup datetime
   */
  typedef boost::posix_time::minutes::sec_type Second;

  /**
   * Millisecond number
   * @ingroup datetime
   */
  typedef boost::posix_time::time_duration::fractional_seconds_type Millisecond;

  /**
   * Microsecond number
   * @ingroup datetime
   */
  typedef boost::posix_time::time_duration::fractional_seconds_type Microsecond;

  /**
   * Date class.
   *
   * This class provides methods to inspect dates as well as methods and
   * operators which implement a limited date algebra (increasing and
   * decreasing dates, and calculating their difference).
   *
   * The maximal resolution of the methods is either micro or nano seconds
   * depending on the underlying boost installation.
   *
   * @ingroup datetime
   */
  class Date {
  public:
    typedef boost::int_fast32_t serial_type;

    /**
     * @name constructors
     * @{
     */

    /**
     * Default constructor returning a null date.
     */
    Date();

    /**
     * Constructor taking a serial number as given by Excel.
     */
    explicit Date(Date::serial_type serialNumber);

    /**
     * Constructor taking day, month and year.
     */
    Date(Day d, Month m, Year y);

    /**
     * Constructor taking boost posix date time object
     */
    explicit Date(const boost::posix_time::ptime& localTime);

    /**
     * Constructor taking the full range of parameters.
     */
    Date(Day d,
         Month m,
         Year y,
         Hour hours,
         Minute minutes,
         Second seconds,
         Millisecond millisec = 0,
         Microsecond microsec = 0);

    /** @} */ // end of constructors.

    // -------------------------------------------------------------------------

    /**
     * @name inspectors
     * @{
     */

    /**
     * Get week day.
     */
    Weekday weekday() const;

    /**
     * Get day of month.
     */
    Day dayOfMonth() const;

    /**
     * Get day of the year; one-based (Jan 1st = 1)
     */
    Day dayOfYear() const;

    /**
     *  Get month
     */
    Month month() const;

    /**
     * Get year.
     */
    Year year() const;

    /**
     * Get serial number.
     */
    Date::serial_type serialNumber() const;

    /**
     * Get hours.
     */
    Hour hours() const;

    /**
     * Get minutes.
     */
    Minute minutes() const;

    /**
     * Get seconds.
     */
    Second seconds() const;

    /**
     * Get  millseconds.
     */
    Millisecond milliseconds() const;

    /**
     *  Get microseconds.
     */
    Microsecond microseconds() const;

    /**
     * Get fraction of day represent by this Date instance.
     * The maximal resolution of the methods is either micro or nano seconds
     * depending on the underlying boost installation.
     */
    Time fractionOfDay() const;

    /**
     * Get fraction of second represented by this Date instance.
     * The maximal resolution of the methods is either micro or nano seconds
     * depending on the underlying boost installation.
     */
    Time fractionOfSecond() const;

    const boost::posix_time::ptime& dateTime() const { return dateTime_; }

    /** @} */ // end of inspectors.

    // -------------------------------------------------------------------------

    /**
     * @name date algebra
     * @{
     */

    /**
     * returns a new date incremented by the given number of days
     */
    Date operator+(Date::serial_type days) const;

    /**
     * returns a new date incremented by the given period
     */
    Date operator+(const Period&) const;

    /**
     * returns a new date decremented by the given number of days
     */
    Date operator-(Date::serial_type days) const;

    /**
     * returns a new date decremented by the given period
     */
    Date operator-(const Period&) const;

    /** @} */ // end of date algebra methods.

    // -------------------------------------------------------------------------

    /**
     * today's date.
     */
    static Date todaysDate();

    /**
     * earliest allowed date
     */
    static Date minDate();

    /**
     * latest allowed date
     */
    static Date maxDate();

    /**
     * whether the given year is a leap one
     */
    static bool isLeap(Year y);

    /**
     * last day of the month to which the given date belongs
     */
    static Date endOfMonth(const Date& d);

    /**
     * whether a date is the last day of its month
     */
    static bool isEndOfMonth(const Date& d);

    /**
     * next given weekday following or equal to the given date
     * E.g., the Friday following Tuesday, January 15th, 2002
     * was January 18th, 2002.
     * @see http://www.cpearson.com/excel/DateTimeWS.htm
     */
    static Date nextWeekday(const Date& d, Weekday w);

    /**
     * n-th given weekday in the given month and year
     * E.g., the 4th Thursday of March, 1998 was March 26th,
     * 1998.
     * @see http://www.cpearson.com/excel/DateTimeWS.htm
     */
    static Date nthWeekday(Size n, Weekday w, Month m, Year y);

    /**
     * local date time, based on the time zone settings of the computer
     */
    static Date localDateTime();

    /**
     * UTC date time
     */
    static Date universalDateTime();

    /**
     *  underlying resolution of the  posix date time object
     */
    static const Size ticksPerSecond();

  private:
    static Date::serial_type minimumSerialNumber();
    static Date::serial_type maximumSerialNumber();
    static void checkSerialNumber(Date::serial_type serialNumber);

    const boost::posix_time::ptime dateTime_;
  };

  /**
   * Difference in days between dates.
   * @relates Date
   */
  Date::serial_type operator-(const Date&, const Date&);

  /**
   * Difference in days (including fraction of days) between dates
   * @relates Date
   */
  Time daysBetween(const Date&, const Date&);

  // -------------------------------------------------------------------------

  /**
   * Equivalence operator.
   * @relates Date
   */
  bool operator==(const Date&, const Date&);

  /**
   * Not equals operator.
   * @relates Date
   */
  bool operator!=(const Date&, const Date&);

  /**
   * Less than operator.
   * @relates Date
   */
  bool operator<(const Date&, const Date&);

  /**
   * Less than or equals operator.
   * @relates Date
   */
  bool operator<=(const Date&, const Date&);

  /**
   * Greater than operator.
   * @relates Date
   */
  bool operator>(const Date&, const Date&);

  /**
   * Greater than or equals operator.
   * @relates Date
   */
  bool operator>=(const Date&, const Date&);

  /**
   * Output operator.
   * @relates Date
   */
  // TODO
  // std::ostream& operator<<(std::ostream&, const Date&);

}

#endif /* MATHFIN_DATE_HPP */
