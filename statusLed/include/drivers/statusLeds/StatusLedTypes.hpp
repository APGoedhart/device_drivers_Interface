#ifndef DRIVERS_STATUSLED_INCLUDE_DRIVERS_STATUSLEDS_STATUSLEDTYPES_HPP
#define DRIVERS_STATUSLED_INCLUDE_DRIVERS_STATUSLEDS_STATUSLEDTYPES_HPP

#include <cstdint>
#include <dataTypes/EnumValue.hpp>

namespace Drivers {
/// @brief The default assignments for the LEDS,
/// The POWER LED is normally operated directly from the power supply.
/// The NETWORK LED may be in some systems be driven directly by the bus claim signal
/// The ACTIVITY LED is used to signal the status of the main activity of the node.
/// The ERROR LED is used to signify that the node has entered an error state.
  enum class LedState : uint8_t {
    LedOff [[maybe_unused]] = 0,
    LedOn [[maybe_unused]] = 1,
    LedSlowFlash [[maybe_unused]] = 2,
    LedFastFlash [[maybe_unused]] = 3
  };

  /// @brief different LEDS defined for the Status Leads
  /// Defined as an enum value to ensure that the system can expand the LEDS
  namespace Leds {
    class Type : public Utils::EnumValue<uint8_t> {
      public:
      using EnumValue::EnumValue;
      using EnumValue::operator==;
    };

    [[maybe_unused]] constexpr auto activity = Type(0);
    [[maybe_unused]] constexpr auto error    = Type(1);
  }



}

#endif
