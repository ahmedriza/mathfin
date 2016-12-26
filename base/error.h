#ifndef FINMATH_ERROR_H
#define FINMATH_ERROR_H

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

#endif /* FINMATH_ERROR_H */
