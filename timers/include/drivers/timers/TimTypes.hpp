#ifndef DRIVERS_TIMERS_INCLUDE_DRIVERS_TIMERS_TIMTYPES_HPP
#define DRIVERS_TIMERS_INCLUDE_DRIVERS_TIMERS_TIMTYPES_HPP

#include <cstdint>
#include <callbacks/Callback.hpp>
#include <dataTypes/EnumValue.hpp>
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
  namespace TimerEvent {
    class Type :public Utils::EnumValue<uint16_t>{
      using EnumValue::EnumValue;
      using EnumValue::operator ==;
      using EnumValue::operator !=;
      using EnumValue::operator =;
    };
    constexpr Type counterReset(0x0001);
    constexpr Type capture1(0x0002U);
    constexpr Type compare1(0x0002U);
    constexpr Type capture2(0x0004U);
    constexpr Type compare2(0x0004U);
    constexpr Type capture3(0x0008U);
    constexpr Type compare3(0x0008U);
    constexpr Type capture4(0x0010U);
    constexpr Type compare4(0x0010U);
    constexpr Type capture1Overflow(0x0200U);
    constexpr Type capture2Overflow(0x0400U);
    constexpr Type capture3Overflow(0x0800U);
    constexpr Type capture4Overflow(0x1000U);
  }

  using TimerPeriodCb = Mem::Callback<8, void ()>;
  using TimerCaptureCompareCb = Mem::Callback<8, void(TimerChannel channel, TimerEvent::Type validEvents)>;

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
