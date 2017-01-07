/*
  Copyright (C) 2017 Ahmed Riza

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
  Copyright (C) 2004 Jeff Yu
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

#ifndef MATHFIN_CALENDAR_HPP
#define MATHFIN_CALENDAR_HPP

#include <base/error.hpp>
#include <time/date.hpp>
#include <time/businessdayconvention.hpp>

#include <memory>
#include <set>
#include <vector>
#include <string>

namespace MathFin {

  class Period;

  /**
   * calendar class
   * This class provides methods for determining whether a date is a
   * business day or a holiday for a given market, and for
   * incrementing/decrementing a date of a given number of business days.
   *
   * The Bridge pattern is used to provide the base behavior of the
   * calendar, namely, to determine whether a date is a business day.
   *
   * A calendar should be defined for specific exchange holiday schedule
   * or for general country holiday schedule. Legacy city holiday schedule
   * calendars will be moved to the exchange/country convention.
   *
   * @ingroup datetime
   *
   */
  class Calendar {

  protected:
    /**
     * Abstract base class for calendar implementations.  The implementation
     * will be shared by a calendar when a copy of the calendar is created
     * (for example due to adding extra holidays).  Therefore it is important
     * that there is no shared data in the implementations themselves.
     */
    class Impl {
    public:
      virtual ~Impl() {}
      virtual std::string name() const = 0;
      virtual bool isBusinessDay(const Date&) const = 0;
      virtual bool isWeekend(Weekday) const = 0;
    };

    Calendar(const std::shared_ptr<Impl>& impl) : impl_(impl) {}

    const std::shared_ptr<Impl> impl_;

    /**
     * partial calendar implementation
     * This class provides the means of determining the Easter
     * Monday for a given year, as well as specifying Saturdays
     * and Sundays as weekend days.
     */
    class WesternImpl : public Impl {
    public:
      bool isWeekend(Weekday) const;
      /**
       * expressed relative to first day of year
       */
      static Day easterMonday(Year);
    };

    /**
     * partial calendar implementation
     * This class provides the means of determining the Orthodox
     * Easter Monday for a given year, as well as specifying
     * Saturdays and Sundays as weekend days.
     */
    class OrthodoxImpl : public Impl {
    public:
      bool isWeekend(Weekday) const;
      /**
       * expressed relative to first day of year
       */
      static Day easterMonday(Year);
    };


  public:
    /**
     * The default constructor returns a calendar with a null
     * implementation, which is therefore unusable except as a
     * placeholder.
     */
    Calendar() {}

    /**
     * @name Calendar interface
     * @{
     */

    /**
     * Returns whether or not the calendar is initialized
     */
    inline bool empty() const {
      return !impl_;
    }

    /**
     * Returns the name of the calendar.
     * @warning This method is used for output and comparison between
     * calendars. It is <b>not</b> meant to be used for writing
     * switch-on-type code.
     */
    inline std::string name() const {
      MF_REQUIRE(impl_, "no implementation provided");
      return impl_->name();
    }

    /**
     * Returns <tt>true</tt> iff the date is a business day for the
     * given market.
     */
    inline bool isBusinessDay(const Date& d) const {
      MF_REQUIRE(impl_, "no implementation provided");
      if (addedHolidays_.find(d) != addedHolidays_.end()) {
        return false;
      }
      if (removedHolidays_.find(d) != removedHolidays_.end()) {
        return true;
      }
      return impl_->isBusinessDay(d);
    }

    /**
     * Returns <tt>true</tt> iff the date is a business day for the
     * given market.
     */
    inline bool isBusinessDay(const boost::posix_time::ptime& dateTime) const {
      return isBusinessDay(Date(dateTime));
    }

    /**
     * Returns <tt>true</tt> iff the date is a holiday for the given
     * market.
     */
    inline bool isHoliday(const Date& d) const {
      return !isBusinessDay(d);
    }

    /**
     * Returns <tt>true</tt> iff the date is a holiday for the given
     * market.
     */
    inline bool isHoliday(const boost::posix_time::ptime& dateTime) const {
      return !isBusinessDay(Date(dateTime));
    }

    /**
     * Returns <tt>true</tt> iff the weekday is part of the
     * weekend for the given market.
     */
    inline bool isWeekend(Weekday w) const {
      MF_REQUIRE(impl_, "no implementation provided");
      return impl_->isWeekend(w);
    }

    /**
     * Returns <tt>true</tt> iff the date is last business day for the
     * month in given market.
     */
    inline bool isEndOfMonth(const Date& d) const {
      return (d.month() != adjust(d+1).month());
    }

    //! last business day of the month to which the given date belongs
    inline Date endOfMonth(const Date& d) const {
      return adjust(Date::endOfMonth(d), BusinessDayConvention::Preceding);
    }

    /**
     * Adds a date to the set of holidays for the given calendar and
     * return a new modified calendar. The original calendar is not changed
     * and the new calendar returned will share the implementation with
     * the original.
     */
    Calendar addHoliday(const Date&) const;

    /**
     * Removes a date from the set of holidays for the given calendar and
     * return a new modified calendar. The original calendar is not changed
     * and the new calendar returned will share the implementation with
     * the original.
     */
    Calendar removeHoliday(const Date&) const;

    /**
     * Adjusts a non-business day to the appropriate near business day
     * with respect to the given convention.
    */
    Date adjust(
      const Date&,
      BusinessDayConvention convention = BusinessDayConvention::Following) const;

    /**
     * Advances the given date of the given number of business days and
     * returns the result.
     * @note The input date is not modified.
    */
    Date advance(
      const Date&,
      Integer n,
      TimeUnit unit,
      BusinessDayConvention convention = BusinessDayConvention::Following,
      bool endOfMonth = false) const;

    /**
     * Advances the given date as specified by the given period and
     * returns the result.
     * @note The input date is not modified.
    */
    Date advance(
      const Date& date,
      const Period& period,
      BusinessDayConvention convention = BusinessDayConvention::Following,
      bool endOfMonth = false) const;

    /*
     * Calculates the number of business days between two given
     * dates and returns the result.
     */
    Date::serial_type businessDaysBetween(
      const Date& from,
      const Date& to,
      bool includeFirst = true,
      bool includeLast = false) const;

    /**
     * Returns the holidays between two dates
     */
    static std::vector<Date> holidayList(
      const Calendar& calendar,
      const Date& from,
      const Date& to,
      bool includeWeekEnds = false);

    /** @} */

  private:
    const std::set<Date> addedHolidays_;
    const std::set<Date> removedHolidays_;

    Calendar(
      const std::shared_ptr<Impl>& impl,
      const std::set<Date>& addedHolidays,
      const std::set<Date>& removedHolidays
      ) : impl_(impl),
          addedHolidays_(addedHolidays),
          removedHolidays_(removedHolidays)
      {}
  };

  /**
   * Returns <tt>true</tt> iff the two calendars belong to the same
   * derived class.
   * @relates Calendar
  */
  inline bool operator==(const Calendar& c1, const Calendar& c2) {
    return (c1.empty() && c2.empty())
      || (!c1.empty() && !c2.empty() && c1.name() == c2.name());
  }

  /**
   * @relates Calendar
   */
  inline bool operator!=(const Calendar& c1, const Calendar& c2) {
    return !(c1 == c2);
  }

  /**
   * @relates Calendar
   */
  inline std::ostream& operator<<(std::ostream& out, const Calendar &c) {
    return out << c.name();
  }
}

#endif /* MATHFIN_CALENDAR_HPP */
