#ifndef DRIVERS_TIMERS_INCLUDE_DRIVERS_TIMERS_SWITCHINGTIMERTYPES_HPP
#define DRIVERS_TIMERS_INCLUDE_DRIVERS_TIMERS_SWITCHINGTIMERTYPES_HPP

#include <time/Ticks.hpp>
#include <drivers/timers/TimTypes.hpp>
#include <dataStructures/EnumIndexedArray.hpp>
#include <callbacks/Callback.hpp>


namespace Drivers::SwitchingTimerTypes {
  // Determine the relay to work with.
  enum class Relay : uint8_t {
    AcRelay [[maybe_unused]] = 0,
    Relay2 [[maybe_unused]] = 0,
    DcRelay [[maybe_unused]] = 1,
    Relay1 [[maybe_unused]] = 1,
    TotalRelays [[maybe_unused]] = 2,
    Invalid = 2
  };

  enum class RelayState : uint8_t {
    Open = 0,
    Closed = 1,
    Invalid = 2
  };

  enum class SwitchingState : uint8_t {
    WaitForZc = 0,
    Switching = 1,
    Switched = 2,
    Notified = 3,
    NoOperation = 4
  };

  enum class ZcState : uint8_t {
    WaitForZc = 0,
    ZcFound = 1,
    ZcCalculated = 2
  };

  // Callbacks
  // =========

  /// @brief The output controlling one of the relay's states needs to be switched.
  /// @details Relay -  the relay whose state has to be switched.
  ///          RelayState - The new required state for the given relay
  using SetRelayOutputCb = Mem::Callback<8, void(Relay, RelayState)>;

  /// @brief Notify the user of the driver that the given relay has changed state and completed switching.
  using HasSwitchedCb = Mem::Callback<8, void(Relay)>;


  // Timing
  // ======
  static constexpr auto ticksPerHalfCycle = static_cast<uint16_t>(Time::ExtendedTicks::defaultTicksPerMillisecond * 10);
  static constexpr auto counterPeriod = ticksPerHalfCycle * 4;
  static constexpr uint16_t ticksPerMs = 50;
  static constexpr uint16_t minPeriod = 9 * ticksPerMs;
  static constexpr uint16_t maxPeriod = 11 * ticksPerMs;
  static constexpr uint16_t defaultDelay = 1 * ticksPerMs;



  /// @brief Track the current delays for both relays and their open and close times`
  using StateDelays = DataStructures::EnumIndexedArray<RelayState, Ticks, 2>;
  using RelayDelays = DataStructures::EnumIndexedArray<Relay,StateDelays, 2>;

}


#endif
