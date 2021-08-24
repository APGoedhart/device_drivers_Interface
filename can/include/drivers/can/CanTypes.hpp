#ifndef DRIVERS_INTERFACE_CAN_INCLUDE_DRIVERS_CAN_CANTYPES_HPP
#define DRIVERS_INTERFACE_CAN_INCLUDE_DRIVERS_CAN_CANTYPES_HPP

#include <dataTypes/EnumValue.hpp>
#include <callbacks/Callback.hpp>
#include <projectSetup/HeapConfig.hpp>

namespace Drivers {
  enum class CanPort :uint8_t {
    Can1=0
  };

  class CanId {
    public:
    constexpr explicit CanId(const uint32_t newId)
      :id(static_cast<uint16_t>(newId)){
    }

    explicit constexpr operator uint16_t() const {
      return id;
    }
    explicit constexpr operator uint32_t() const {
      return id;
    }

    private:
      uint16_t id;
  };

  /// @brief the 2 rx mailboxes available in the CAN peripheral
  namespace CanRxFifo {
    class Type : public Utils::EnumValue<uint8_t> {
      public:
      using EnumValue::EnumValue;
      using EnumValue::operator==;
    };

    [[maybe_unused]] constexpr auto fifo0 = Type(0);
    [[maybe_unused]] constexpr auto fifo1 = Type(1);
    [[maybe_unused]] constexpr auto none = Type(2);
  }

  /// @brief the 3 tx mailboxes available in the CAN peripheral
  namespace CanTxMailBox {
    class Type : public Utils::EnumValue<uint8_t> {
      public:
        using EnumValue::EnumValue;
        using EnumValue::operator==;
        using EnumValue::operator!=;

    };

    [[maybe_unused]] constexpr Type mailBox0(0);
    [[maybe_unused]] constexpr Type mailBox1(1);
    [[maybe_unused]] constexpr Type mailBox2(2);
    [[maybe_unused]] constexpr Type none(3);
    constexpr std::array<Type, 3> validMailBox = {mailBox0, mailBox1, mailBox2};
  }


  /// @brief the 3 baud rates currently supported.
  namespace CanBaudRate {
    class Type : public Utils::EnumValue<uint32_t> {
      public:
      using EnumValue::EnumValue;
      using EnumValue::operator==;
    };

    [[maybe_unused]] constexpr Type baudRate250Kb(250000U);
    [[maybe_unused]] constexpr Type baudRate500Kb(500000U);
    [[maybe_unused]] constexpr Type baudRate1000Kb(1000000U);
  }

  class CanPacket;

  using CanInterruptCb = Mem::Callback<8, void() >;
  using TxPacketSentCb = Mem::Callback<8, void()>;
  using RxPacketCb = Mem::Callback<8, void(const CanPacket&)>;

}

#endif //SPS081_BMS_STM32F103_CANTYPES_HPP
