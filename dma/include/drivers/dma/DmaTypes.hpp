#ifndef DRIVERS_DMA_INCLUDE_DRIVERS_DMA_DMATYPES_HPP
#define DRIVERS_DMA_INCLUDE_DRIVERS_DMA_DMATYPES_HPP

#include <cstdint>
#include <dataTypes/EnumValue.hpp>
#include <callbacks/Callback.hpp>
namespace Drivers {

  /// @brief the DMA channel. Not all the channels may be available on all chips.
  enum class DmaChannel :uint16_t {
      Channel1 = 0U,
      Channel2 = 1U,
      Channel3 = 2U,
      Channel4 = 3U,
      Channel5 = 4U,
      Channel6 = 5U,
      Channel7 = 6U,
      Channel8 [[maybe_unused]] = 7U,
      Invalid = 0xFFU,
  };

  /// @brief Priority for the DMA channel
  enum class DmaPriority :uint16_t {
      Low = 0U,
      Medium [[maybe_unused]] =1U,
      High  = 2U,
      VeryHigh [[maybe_unused]] =3U,
  };

  /// @brief the direction the channel runs in
  enum class TransferDirection :uint16_t {
      FromDevice =0,
      FromMemory =1
  };

  /// @brief the width of each transfer on the DMA channel
 enum class DataWidth :uint16_t {
      Bits8 =0,
      Bits16 =1,
      Bits32 [[maybe_unused]] =2
  };

 /// @brief whether the address is incremented after the transfer.
 enum class AddressIncrement :uint16_t{
   Disabled=0,
   PostIncrement=1
  };

 /// @brief is the DMA channel running in circular mode or one shot.
  enum class AutoReload :uint16_t {
    Disabled=0,
    Circular [[maybe_unused]] =1
  };

  enum class InterruptPoint :uint16_t {
    TransferComplete=0,
    HalfTransfer=1,
    TransferError [[maybe_unused]] =2,
  };

  /// @brief Used to notify driver of DMA status change
  using TransferCompleteCb = Mem::Callback<8, void (DmaChannel)>;


}

#endif
