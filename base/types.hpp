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
  Copyright (C) 2003, 2004, 2005 StatPro Italia srl

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

/**
 * \file types.hpp
 * Custom types
 */

#ifndef MATHFIN_TYPES_HPP
#define MATHFIN_TYPES_HPP

namespace MathFin {
  /**
   * integer number
   * \ingroup types
   */
  typedef int Integer;

  /**
   * large integer number
   * \ingroup types
   */
  typedef long BigInteger;

  /**
   * positive number
   * \ingroup types
   */
  typedef unsigned int Natural;

  /**
   * large positive number
   * \ingroup types
   */
  typedef unsigned long BigNatural;

  /**
   * real number
   * \ingroup types
   */
  typedef double Real;

  /**
   * decimal number
   * \ingroup types
   */
  typedef Real Decimal;

  /**
   * size of a container
   * \ingroup types
   */
  typedef std::size_t Size;

  /**
   * continuous quantity with 1-year units
   * \ingroup types
   */
  typedef Real Time;

  /**
   * discount factor between dates
   * \ingroup types
   */
  typedef Real DiscountFactor;

  /**
   * interest rates
   * \ingroup types
   */
  typedef Real Rate;

  /**
   * spreads on interest rates
   * \ingroup types
   */
  typedef Real Spread;

  /**
   * volatility
   * \ingroup types
   */
  typedef Real Volatility;

  /**
   * probability
   * \ingroup types
   */
  typedef Real Probability;
}

#endif /* MATHFIN_TYPES_HPP */
