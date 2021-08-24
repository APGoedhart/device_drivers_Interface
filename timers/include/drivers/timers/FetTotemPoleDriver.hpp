#ifndef DRIVERS_INTERFACE_TIMERS_INCLUDE_DRIVERS_TIMERS_FETTOTEMPOLEDRIVER_HPP
#define DRIVERS_INTERFACE_TIMERS_INCLUDE_DRIVERS_TIMERS_FETTOTEMPOLEDRIVER_HPP

#include <time/Ticks.hpp>
#include <drivers/clocks/ClockTypes.hpp>

namespace Drivers {
  /// @brief Used to define the switch periods
  using NanoSeconds = uint32_t;

  /// @brief  Switch a single totem pole with State and enable to allow for dead time at end of period to clear.
  /// Controls two channels one for determining high and low switch is active and a second channel acting as an
  /// override disable. If false all outputs are off.
  ///
  /// Assumes that both channels are on the same timer. Assumes that the driver has full control over
  /// the timer and can set the timer period as per its own requirements.
  /// Set the time highest resolution and then deals with the periods

  class FetSwitchingTimerDriver {
    public:
      FetSwitchingTimerDriver()=default;

      virtual ~FetSwitchingTimerDriver()=default;

      FetSwitchingTimerDriver(const FetSwitchingTimerDriver &) = delete;

      FetSwitchingTimerDriver &operator=(const FetSwitchingTimerDriver &) = delete;

      /// @brief set the output timing. Setup the channels for PWM and disable the outputs before setting the timing
      /// @details Implements a hi/lo or lo/hi switching cycle with dead time at the end. The pulse train is repetitive
      /// until timing uis changed
      /// @param hiFirst if hiFirst=true then the hi/lo line hi low line starts high at the beginning of the period. otherwise it
      ///          starts low
      /// @param hiTime the period in nanoseconds tha upper fet is active.
      /// @param loTime the period in nanoseconds the lower fet is active.
      /// @param period total period for the high low cycle including the dead time at the end where no fet is active
      virtual void setTiming(bool hiFirst, NanoSeconds period, NanoSeconds hiTime, NanoSeconds loTime )=0;

      /// @brief update the output timing.  Doe not setup the channels or change the output enable
      /// @param hiFirst if hiFirst=true then the hi/lo line hi low line starts high at the beginning of the period. otherwise it
      ///          starts low
      /// @param hiTime the period in nanoseconds tha upper fet is active.
      /// @param loTime the period in nanoseconds the lower fet is active.
      /// @param period total period for the high low cycle including the dead time at the end where no fet is active
      virtual void updateTiming(bool hiFirst, NanoSeconds period, NanoSeconds hiTime, NanoSeconds loTime )=0;

      // @brief enable./disable the channel outputs.
      virtual void enableOutput(bool isEnabled)=0;

    };
}
#endif
