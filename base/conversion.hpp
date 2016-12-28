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

/**
 * @file conversion.hpp
 * @brief Utility methods for type conversions.
 */
namespace MathFin {

  /**
   * @brief
   * Convert a strongly typed enum to its underlying int value.
   *
   * Sometimes, we may need to get the integer value of a strongly typed enum.
   * This utility method helps whilst ensuring type safety.
   *
   * @param value a strongly typed enum
   * @return the int value of the underlying enum
   */
  template <typename Enumeration>
  constexpr auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type  {
    static_assert(std::is_enum<Enumeration>::value, "parameter is not of type enum");
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
  }

}
