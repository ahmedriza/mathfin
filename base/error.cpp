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

#include <base/error.hpp>

namespace FinMath {

  std::string format(const std::string& file,
                     long line,
                     const std::string& functionName,
                     const std::string& message) {
    std::ostringstream msg;
    msg << file << ":" << line << ": ";
    if (functionName != "(unknown)") {
      msg << "in function `" << functionName << "': ";
    }
    msg << message;
    return msg.str();
  }

  Error::Error(const std::string& file,
               long line,
               const std::string& functionName,
               const std::string& message) {
    message_ = std::shared_ptr<std::string>
      (new std::string(format(file, line, functionName, message)));
  }

  const char* Error::what() const throw () {
    return message_->c_str();
  }
}
