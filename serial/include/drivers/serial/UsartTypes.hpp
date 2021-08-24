#ifndef DRIVERS_SERIAL_INCLUDE_DRIVERS_SERIAL_USARTTYPES_HPP
#define DRIVERS_SERIAL_INCLUDE_DRIVERS_SERIAL_USARTTYPES_HPP

#include <cstdint>
#include <callbacks/Callback.hpp>
#include <cmsis/Processor.hpp>

namespace Drivers {

  enum class UsartPort :uint32_t {
      Usart1=0,
      Usart2=1,
      Usart3=2,
   };

  enum class WordLength :uint32_t {
      Bits7 [[maybe_unused]] =2U,
      Bits8 =0U,
      Bits9 [[maybe_unused]] =1U
  };

  //lint -strong(JAi, Hal::BaudRate)
  enum class BaudRate :uint32_t {
      Baud9600 [[maybe_unused]] =9600U,
      Baud115200[[maybe_unused]]=115200U,
      Baud200000 [[maybe_unused]] =200000U,
      Baud230400 [[maybe_unused]]=230400U,
      Baud250000 [[maybe_unused]] =250000U,
      Baud460800 [[maybe_unused]] =460800U,
      Baud500000 [[maybe_unused]] =500000U
  };


  //lint -strong(JAi, Hal::StopBits)
  enum class StopBits :uint32_t {
    Bits1   [[maybe_unused]] =0U,
      Bits15 [[maybe_unused]] =3U,
      Bits2 [[maybe_unused]] =2U
  };

  using UsartInterruptHandler = Mem::Callback<8, void(Drivers::IRQn)>;

}



#endif
