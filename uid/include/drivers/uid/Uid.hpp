#ifndef DRIVERS_UID_INCLUDE_DRIVERS_UID_UID_HPP
#define DRIVERS_UID_INCLUDE_DRIVERS_UID_UID_HPP

#include <drivers/uid/ProcessorSerial.hpp>

namespace Drivers {
  class UidDriver {
    public:
      UidDriver() = default;
      virtual ~UidDriver()=default;

      [[nodiscard]] virtual ProcessorSerial getSerial() const =0;
  };
}



#endif
