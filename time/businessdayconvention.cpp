#include <time/businessdayconvention.h>
#include <base/error.h>
#include <iostream>

namespace FinMath {

  std::ostream& operator<<(std::ostream& out, BusinessDayConvention b) {
    switch (b) {
    case BusinessDayConvention::Following:
      return out << "Following";
    case BusinessDayConvention::ModifiedFollowing:
      return out << "Modified Following";
    case BusinessDayConvention::HalfMonthModifiedFollowing:
      return out << "Half-Month Modified Following";
    case BusinessDayConvention::Preceding:
      return out << "Preceding";
    case BusinessDayConvention::ModifiedPreceding:
      return out << "Modified Preceding";
    case BusinessDayConvention::Unadjusted:
      return out << "Unadjusted";
    case BusinessDayConvention::Nearest:
      return out << "Nearest";
    default:
      std::ostringstream msg;
      msg << "Unknown BusinessDayConvention (" << int(b) << ")";
      std::cerr << msg.str() << std::endl;
      throw FinMath::Error(__FILE__, __LINE__, BOOST_CURRENT_FUNCTION, msg.str());
    }
  }
}
