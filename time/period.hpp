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

/*! \file period.hpp
  \brief period and frequency-related classes and enumerations
*/

#ifndef MATHFIN_PERIOD_HPP
#define MATHFIN_PERIOD_HPP

#include <time/frequency.hpp>
#include <time/timeunit.hpp>

namespace MathFin {

  /*! This class provides a Period (length + TimeUnit) class
    and implements a limited algebra.

    \ingroup datetime

    \test self-consistency of algebra is checked.
  */
  class Period {

  public:
    Period() : length_(0), units_(Days) {}
    Period(Integer n, TimeUnit units) : length_(n), units_(units) {}
    explicit Period(Frequency f);
    Integer length() const { return length_; }
    TimeUnit units() const { return units_; }
    Frequency frequency() const;
    Period& operator+=(const Period&);
    Period& operator-=(const Period&);
    Period& operator/=(Integer);
    void normalize();

  private:
    Integer  length_;
    TimeUnit units_;
  };

  /*! \relates Period */
  Real years(const Period&);

  /*! \relates Period */
  Real months(const Period&);

  /*! \relates Period */
  Real weeks(const Period&);

  /*! \relates Period */
  Real days(const Period&);

  /*! \relates Period */
  template <typename T> Period operator*(T n, TimeUnit units);

  /*! \relates Period */
  template <typename T> Period operator*(TimeUnit units, T n);

  /*! \relates Period */
  Period operator-(const Period&);

  /*! \relates Period */
  Period operator*(Integer n, const Period&);

  /*! \relates Period */
  Period operator*(const Period&, Integer n);

  /*! \relates Period */
  Period operator/(const Period&, Integer n);

  /*! \relates Period */
  Period operator+(const Period&, const Period&);

  /*! \relates Period */
  Period operator-(const Period&, const Period&);

  /*! \relates Period */
  bool operator<(const Period&, const Period&);

  /*! \relates Period */
  bool operator==(const Period&, const Period&);

  /*! \relates Period */
  bool operator!=(const Period&, const Period&);

  /*! \relates Period */
  bool operator>(const Period&, const Period&);

  /*! \relates Period */
  bool operator<=(const Period&, const Period&);

  /*! \relates Period */
  bool operator>=(const Period&, const Period&);

  /*! \relates Period */
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

  // inline definitions

  template <typename T>
  inline Period operator*(T n, TimeUnit units) {
    return Period(Integer(n), units);
  }

  template <typename T>
  inline Period operator*(TimeUnit units, T n) {
    return Period(Integer(n),units);
  }

  inline Period operator-(const Period& p) {
    return Period(-p.length(),p.units());
  }

  inline Period operator*(Integer n, const Period& p) {
    return Period(n*p.length(),p.units());
  }

  inline Period operator*(const Period& p, Integer n) {
    return Period(n*p.length(),p.units());
  }

  inline bool operator==(const Period& p1, const Period& p2) {
    return !(p1 < p2 || p2 < p1);
  }

  inline bool operator!=(const Period& p1, const Period& p2) {
    return !(p1 == p2);
  }

  inline bool operator>(const Period& p1, const Period& p2) {
    return p2 < p1;
  }

  inline bool operator<=(const Period& p1, const Period& p2) {
    return !(p1 > p2);
  }

  inline bool operator>=(const Period& p1, const Period& p2) {
    return !(p1 < p2);
  }

}

#endif /* MATHFIN_PERIOD_HPP */