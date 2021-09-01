#ifndef DRIVERS_INTERFACE_TIMERS_INCLUDE_DRIVERS_TIMERS_ALARMTIMERDRIVER_HPP
#define DRIVERS_INTERFACE_TIMERS_INCLUDE_DRIVERS_TIMERS_ALARMTIMERDRIVER_HPP

#include <time/Ticks.hpp>
#include <drivers/timers/TimTypes.hpp>
#include <drivers/clocks/ClockTypes.hpp>

namespace Drivers {
  /// @brief Called when one of the alarms associated with one of the channels. fires.
  using AlarmTimerCb = Mem::Callback<8, void(TimerChannel)>;

  /// @brief Setup one of the hardware timers as a pure timer with 1-N alarms corresponding to the
  /// number of capture compare units available on the timer.
  /// @detail The timer is not setup for output or input, only to generate alarms and call the provided
  /// call backs on expiry.
  class AlarmTimerDriver {
    public:
    AlarmTimerDriver() = default;

    AlarmTimerDriver(const AlarmTimerDriver &) = delete;

    virtual ~AlarmTimerDriver() = default;

    /// @brief Initialise the timer with the given counter frequency and period.
    /// @param requiredTickRate THe frequency of the counters ticks (lsb of the counter)
    /// @param periodInTicks The number of ticks for the counter period. the counter will automatically
    ///                      reload at the end of each period.
    virtual void initialise(ClockSpeed requiredTickRate, uint16_t periodInTicks)=0;

    /// @brief Start the counter if it is not already active.
    virtual void startCounter()=0;

    /// @brief Return the current counter value
    [[nodiscard]] virtual Ticks getCounter() const=0;

    /// @brief Return the extended 32bit counter value.
    [[nodiscard]] virtual Time::ExtendedTicks getExtendedCounter() const=0;

    /// @brief  Return the extended 32bit counter value.
    [[maybe_unused]] [[nodiscard]] virtual Time::ExtendedTicks getExtendedCounterFromLock() const=0;

    /// @brief  Set the timeout before the timer expires
    /// @param channel the channel the timeout is applied to
    /// @param timeout the time in ticks before the timer expires
    /// @param callback the interface called on expiry
    virtual void setAlarmTimeout(TimerChannel channel, Ticks timeout, const AlarmTimerCb &callback)=0;

    /// @brief Clear the current alarm timeout.
    virtual void stopAlarmTimeout(TimerChannel channel)=0;

    /// @brief  get timeout in ticks for the current Alarm
    virtual Ticks getAlarmTimeout(TimerChannel channel)=0;

  };

}

#endif
