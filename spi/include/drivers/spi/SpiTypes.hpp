#ifndef DRIVERS_INTERFACE_SPI_INCLUDE_DRIVERS_SPI_SPITYPES_HPP
#define DRIVERS_INTERFACE_SPI_INCLUDE_DRIVERS_SPI_SPITYPES_HPP

#include <cstdint>
#include <callbacks/Callback.hpp>


namespace Drivers {

  /// @brief name the SPI peripherals available according to ST naming conventions
  enum class SpiPort :uint32_t {
    Spi1=0U,
    Spi2=1U
  };

  ///  @brief The baud rate for the SPI port. There are only limited clock divisors on the standard ports and clock
  /// configurations
  enum class SpiBaudRate :uint32_t {
    Baud1Mhz [[maybe_unused]],
    Baud1M5Hz [[maybe_unused]],
    Baud3Mhz [[maybe_unused]],
    Baud8Mhz [[maybe_unused]],
    Baud24Mhz [[maybe_unused]],
  };

  /// @brief how the NSS line is pulsed with relation to the current data byte/word transfer. Currently most
  /// implementation use software control
  enum class SpiMode :uint32_t {
    None [[maybe_unused]]  =0,
    MotorolaMode [[maybe_unused]] =0 ,
    TiMode [[maybe_unused]]=1
  };

  using SpiTransferCompleteCb = Mem::Callback<8, void()>;
}
#endif
