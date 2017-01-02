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
  Copyright (C) 2004, 2005, 2006, 2007, 2008 Ferdinando Ametrano
  Copyright (C) 2006 Katiuscia Manzoni
  Copyright (C) 2000, 2001, 2002, 2003 RiskMap srl
  Copyright (C) 2003, 2004, 2005, 2006, 2007 StatPro Italia srl

  QuantLib is free software: you can redistribute it and/or modify it
  under the terms of the QuantLib license.  You should have received a
  copy of the license along with this program; if not, please email
  <quantlib-dev@lists.sf.net>. The license is also available online at
  <http://quantlib.org/license.shtml>.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/**
 * \file period.hpp
 * \brief period and frequency-related classes and enumerations
 */

#ifndef MATHFIN_PERIOD_HPP
#define MATHFIN_PERIOD_HPP

#include <base/types.hpp>
#include <time/frequency.hpp>
#include <time/timeunit.hpp>

namespace MathFin {

  /**
   * This class provides a Period (length + TimeUnit) class
   * and implements a limited algebra.
   *
   * A period represents a length and a TimeUnit.  For example,
   * Period(1, TimeUnit::Months) represents a period of 1 month.
   *
   * @ingroup datetime
   */
  class Period {

  public:
    /**
     * Construct a period of 0 length and TimeUnit of days.
     */
    Period() : length_(0), units_(TimeUnit::Days) {}

    /**
     * Construct a period of length n and TimeUnit of units.
     */
    Period(Integer n, TimeUnit units) : length_(n), units_(units) {}

    /**
     * Construct a period using the given Frequence f.
     */
    static const Period of(const Frequency& f);

    /**
     * Get the length of the period.
     */
    Integer length() const { return length_; }

    /**
     * Get the TimeUnit units of the period.
     */
    TimeUnit units() const { return units_; }

    /**
     * Get the frequency that corresponds to this Period instance.
     */
    Frequency frequency() const;

    /**
     * If the unit is TimeUnit::Months and the length is even, then convert
     * unit to TimeUnit::Years and length to the number of years in the period.
     * Otherwise return the period unchanged.
     */
    const Period normalize() const;

  private:
    Period& operator=(const Period&);
    const Integer  length_;
    const TimeUnit units_;
  };

  /**
   * Get the number of years in the period.
   * @relates Period
   */
  Real years(const Period&);

  /**
   * Get the number of months in the period.
   * @relates Period
   */
  Real months(const Period&);

  /**
   * Get the number of weeks in the period.
   * @relates Period
   */
  Real weeks(const Period&);

  /**
   * Get the number of days in the period.
   * @relates Period
   */
  Real days(const Period&);

  /**
   * Subtraction operator
   * @relates Period
   */
  inline Period operator-(const Period& p) {
    return Period(-p.length(), p.units());
  }

  /**
   * Return a period of length n and units.
   */
  template <typename T>
  inline Period operator*(T n, TimeUnit units) {
    return Period(Integer(n), units);
  }

  /**
   * Return a period of units and length n.
   */
  template <typename T>
  inline Period operator*(TimeUnit units, T n) {
    return Period(Integer(n), units);
  }

  /**
   * Return a period of length n * length of the given period and its units.
   * @relates Period
   */
  inline Period operator*(Integer n, const Period& p) {
    return Period(n * p.length(), p.units());
  }

  /**
   * Return a period of length n * length of the given period and its units.
   * @relates Period
   */
  inline Period operator*(const Period& p, Integer n) {
    return Period(n * p.length(), p.units());
  }

  /**
   * Divide the length of the period by n, if possible.
   * @relates Period
   */
  Period operator/(const Period&, Integer n);

  /**
   * Add two periods together.
   * @relates Period
   */
  Period operator+(const Period&, const Period&);

  /**
   * Subtract one period from the other.
   * @relates Period
   */
  Period operator-(const Period&, const Period&);

  /**
   * Less than operator.
   * @relates Period
   */
  bool operator<(const Period&, const Period&);

  /**
   * Equivalence operator.
   * @relates Period
   */
  inline bool operator==(const Period& p1, const Period& p2) {
    return !(p1 < p2 || p2 < p1);
  }

  /**
   * Not equal operator
   * @relates Period
   */
  inline bool operator!=(const Period& p1, const Period& p2) {
    return !(p1 == p2);
  }

  /**
   * Greater than operator
   * @relates Period
   */
  inline bool operator>(const Period& p1, const Period& p2) {
    return p2 < p1;
  }

  /**
   * Less than or equal operator
   * @relates Period
   */
  inline bool operator<=(const Period& p1, const Period& p2) {
    return !(p1 > p2);
  }

  /**
   * Greater than or equal operator
   * @relates Period
   */
  inline bool operator>=(const Period& p1, const Period& p2) {
    return !(p1 < p2);
  }

  /**
   * Output operator
   * @relates Period
   */
  std::ostream& operator<<(std::ostream&, const Period&);

  namespace detail {
    struct long_period_holder {
      long_period_holder(const Period& p) : p(p) {}
      Period p;
    };
    std::ostream& operator<<(std::ostream&, const long_period_holder&);

    struct short_period_holder {
      short_period_holder(Period p) : p(p) {}
      Period p;
    };
    std::ostream& operator<<(std::ostream&, const short_period_holder&);
  }

  namespace io {
    //! output periods in long format (e.g. "2 weeks")
    /*! \ingroup manips */
    detail::long_period_holder long_period(const Period&);

    //! output periods in short format (e.g. "2w")
    /*! \ingroup manips */
    detail::short_period_holder short_period(const Period&);
  }

}

#endif /* MATHFIN_PERIOD_HPP */
