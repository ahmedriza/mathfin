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

// #include <boost/current_function.hpp>

namespace MathFin {
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

#define MULTILINE_MACRO_BEGIN do {

#if defined(BOOST_MSVC) && BOOST_MSVC >= 1500
/* __pragma is available from VC++9 */
#define MULTILINE_MACRO_END                     \
  __pragma(warning(push))                       \
  __pragma(warning(disable:4127))               \
  } while(false)                                \
  __pragma(warning(pop))
#else
#define MULTILINE_MACRO_END } while(false)
#endif


/**
 * \def MF_FAIL
 * \brief throw an error (possibly with file and line information)
 */
#define MF_FAIL(message)                                             \
  MULTILINE_MACRO_BEGIN                                               \
  std::ostringstream _ql_msg_stream;                                  \
  _ql_msg_stream << message;                                          \
  throw MathFin::Error(__FILE__,__LINE__,                             \
                        __func__,_ql_msg_stream.str()); \
  MULTILINE_MACRO_END

/**
 * \def MF_REQUIRE
 * throw an error if the given pre-condition is not verified
 */
#define MF_REQUIRE(condition,message)                                  \
  if (!(condition)) {                                                   \
    std::ostringstream _ql_msg_stream;                                  \
    _ql_msg_stream << message;                                          \
    throw MathFin::Error(__FILE__,__LINE__,                             \
                          __func__,_ql_msg_stream.str()); \
  } else


#endif /* FINMATH_ERROR_HPP */
