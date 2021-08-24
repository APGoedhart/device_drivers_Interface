
#ifndef DRIVERS_FLASH_INCLUDE_DRIVERS_FLASH_FLASHTYPES_HPP
#define DRIVERS_FLASH_INCLUDE_DRIVERS_FLASH_FLASHTYPES_HPP

namespace Drivers {
  /// @brief The number of wait states to insert into read accesses from the flash
  enum class WaitStates:uint32_t{
      Ws0 [[maybe_unused]] =0,
      Ws1 [[maybe_unused]] =1,
      Ws2 [[maybe_unused]] =2,
      Ws3 [[maybe_unused]] =3,
      Ws4 [[maybe_unused]] =4,
      Ws5 [[maybe_unused]] =5
  };

}

#endif
