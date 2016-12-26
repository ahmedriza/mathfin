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

#ifndef FINMATH_ERROR_HPP
#define FINMATH_ERROR_HPP

#include <exception>
#include <memory>
#include <sstream>
#include <string>
#include <boost/current_function.hpp>

namespace FinMath {
  class Error : public std::exception {
  public:
    Error(const std::string& file,
          long line,
          const std::string& functionName,
          const std::string& message = "");
    ~Error() throw() {}
    const char* what() const throw ();
  private:
    std::shared_ptr<std::string> message_;
  };
}

#endif /* FINMATH_ERROR_HPP */
