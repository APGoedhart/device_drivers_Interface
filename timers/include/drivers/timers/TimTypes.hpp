#ifndef DRIVERS_TIMERS_INCLUDE_DRIVERS_TIMERS_TIMTYPES_HPP
#define DRIVERS_TIMERS_INCLUDE_DRIVERS_TIMERS_TIMTYPES_HPP

#include <cstdint>
#include <cmsis/Registers.hpp>
#include <callbacks/Callback.hpp>

namespace Drivers {

  /// @brief basic enumeration of timers not all are available on all chips
  enum class Timer : uint8_t {
    Timer1 = 0,
    Timer2 = 1,
    Timer3 = 2,
    Timer4 = 3,
    Timer14 = 4,
    Timer15 = 5,
    Timer16 = 6,
    Timer17 = 7
  };

  /// @brief the Timer capture compare channel
  enum class TimerChannel :uint32_t {
    Channel1 = 0U,
    Channel2 = 1U,
    Channel3 = 2U,
    Channel4 = 3U,
    Invalid = 8u,
  };

  /// @brief the number of pulses to trigger a capture compare on a timer channel
  enum class CapturePulseCount : uint8_t{
      Pulse1 [[maybe_unused]] = 0,
      Pulse2 [[maybe_unused]] = 1,
      Pulse4 [[maybe_unused]] = 2,
      Pulse8 [[maybe_unused]] = 3
  };

  /// #brief the mode flags used with the standard channels
  enum class CompareMode :uint8_t{
    Frozen [[maybe_unused]] = 0,
    ActiveOnMatch [[maybe_unused]] =1,
    InactiveOnMatch [[maybe_unused]] =2,
    Toggle [[maybe_unused]] = 3,
    ForceInactive [[maybe_unused]] = 4,
    ForceActive [[maybe_unused]] = 5,
    PwmModeActive [[maybe_unused]] =6,
    PwmModeInactive [[maybe_unused]] =7
  };


  /// @brief maps timer channel events at a hardware level to a set of flags.
  class TimerEvent : public Mask {
    public:
    using Mask::Mask;

      static constexpr auto counterReset() {
        return TimerEvent(0x0001U);
      }
      static constexpr auto capture1() {
        return TimerEvent(0x0002U);
      }
      static constexpr auto compare1() {
        return TimerEvent(0x0002U);
      }
      static constexpr auto capture2() {
        return TimerEvent(0x0004U);
      }
      static constexpr auto compare2() {
        return TimerEvent(0x0004U);
      }
      static constexpr auto capture3() {
        return TimerEvent(0x0008U);
      }
      static constexpr auto compare3() {
        return TimerEvent(0x0008U);
      }
      static constexpr auto capture4() {
        return TimerEvent(0x0010U);
      }
      static constexpr auto compare4() {
        return TimerEvent(0x0010U);
      }

    [[maybe_unused]] static constexpr auto capture1Overflow() {
        return TimerEvent(0x0200U);
      }

    [[maybe_unused]] static constexpr auto capture2Overflow() {
        return TimerEvent(0x0400U);
      }

    [[maybe_unused]] static constexpr auto capture3Overflow() {
        return TimerEvent(0x0800U);
      }

    [[maybe_unused]] static constexpr auto capture4Overflow() {
        return TimerEvent(0x1000U);
      }
  };

  using TimerPeriodCb = Mem::Callback<8, void ()>;
  using TimerCaptureCompareCb = Mem::Callback<8, void(TimerChannel channel, TimerEvent validEvents)>;

  /// Tracks the state of the timer not held in the registers.
  struct TimerState {
    public:
    uint_fast16_t count;
    uint_fast16_t period;
    TimerPeriodCb notifyPeriod;
    TimerCaptureCompareCb notifyCaptureCompare;
  };

  // ======================================== IMPLEMENTATION ============================================================

}

#endif
