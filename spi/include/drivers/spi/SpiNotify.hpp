#ifndef DRIVERS_INTERFACE_SPI_INCLUDE_DRIVERS_SPI_SPINOTIFY_HPP
#define DRIVERS_INTERFACE_SPI_INCLUDE_DRIVERS_SPI_SPINOTIFY_HPP

#include <cstdint>
#include <callbacks/Callback.hpp>

namespace Drivers {
   /// @brief The command that was completed
  enum class  SpiCommand:uint8_t {
      Invalid,
      Read,
      Write,
      ReadWrite
  };

  using SpiCommandCompleteCb = Mem::Callback<8, void(SpiCommand)>;

}

#endif
