#include <base/error.h>

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
