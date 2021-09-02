#ifndef DRIVERS_INTERFACE_WATCHDOG_INCLUDE_DRIVERS_WATCHDOG_WATCHDOGDRIVER_HPP
#define DRIVERS_INTERFACE_WATCHDOG_INCLUDE_DRIVERS_WATCHDOG_WATCHDOGDRIVER_HPP

namespace Drivers {
  class WatchDogDriver {
    public:
      WatchDogDriver() =default;
      virtual ~WatchDogDriver() = default;

      /// @brief enable the watch dog once, enabled the watchdog cannot be disabled.
      virtual void enable()=0;

      /// @brief kick the watch dog
      virtual void kick()=0;

      /// @brief put the processor to sleep until the next interrupt or the watchdog triggers
      ///        an warning interrupt.
      virtual void waitForInterrupt()=0;

      /// @brief set the watchdog to suspend on debug.
      virtual void disableOnDebug()=0;

  };
}

#endif 