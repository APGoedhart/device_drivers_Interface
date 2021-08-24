#ifndef DRIVERS_CLOCKS_INCLUDE_DRIVERS_CLOCKS_CLOCKTYPES_HPP
#define DRIVERS_CLOCKS_INCLUDE_DRIVERS_CLOCKS_CLOCKTYPES_HPP

#include <cstdint>

namespace Drivers {
  /// @brief The Different clock sources available for the STM32F103/030/334
  enum class ClockSource : uint32_t {
    Hsi = 0,
    Hse = 1,
    Pll = 2,
    Invalid [[maybe_unused]] = 3,
    Lsi [[maybe_unused]] = 5,
    Lse [[maybe_unused]] = 6
  };


  /// @brief Constants that define the different standard clock speeds available.
  enum class ClockSpeed
      : uint32_t {
    Speed32Khz [[maybe_unused]] = 32768,
    Speed50Khz [[maybe_unused]]= 50000,
    Speed100Khz [[maybe_unused]]= 100000,
    Speed4Mhz [[maybe_unused]] = 4000000,
    Speed8Mhz [[maybe_unused]]= 8000000,
    Speed16Mhz [[maybe_unused]]= 16000000,
    Speed24Mhz [[maybe_unused]]= 24000000,
    Speed32Mhz [[maybe_unused]] = 32000000,
    Speed36Mhz [[maybe_unused]] = 36000000,
    Speed48Mhz [[maybe_unused]] = 48000000,
    Speed64Mhz [[maybe_unused]] = 64000000,
    Speed72Mhz [[maybe_unused]] = 72000000,
    Speed96Mhz [[maybe_unused]] = 96000000,
    Speed144Mhz [[maybe_unused]]= 144000000,
    HsiDefault = Speed8Mhz,
    HseDefault = Speed8Mhz,
  };
}

#endif
