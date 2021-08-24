#ifndef DRIVERS_INTERFACE_TIMERS_INCLUDE_DRIVERS_TIMERS_CLOCKSOURCEDRIVER_HPP
#define DRIVERS_INTERFACE_TIMERS_INCLUDE_DRIVERS_TIMERS_CLOCKSOURCEDRIVER_HPP

#include <drivers/timers/TimTypes.hpp>

namespace Drivers {
  class ClockSourceDriver {
    public:
      /// @brief Setup a timer channel to generate a fixed frequency as an oscillator source for other  hardware
      ClockSourceDriver() = default;
      virtual ~ClockSourceDriver() = default;

      /// @brief enable the driver once the outputs have been setup.
      virtual void enable(bool isEnabled)=0;
  };
}

#endif