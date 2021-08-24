#ifndef DRIVERS_INTERFACE_CAN_INCLUDE_DRIVERS_CAN_CANPACKET_HPP
#define DRIVERS_INTERFACE_CAN_INCLUDE_DRIVERS_CAN_CANPACKET_HPP

#include <cstdint>
#include <dataStructures/ByteArray.hpp>
#include <typeConversion/ConvertTypes.hpp>
#include <drivers/can/CanTypes.hpp>

namespace Drivers {

  /// @brief Models a packet sent via the CAN bus. Used for receive or transmit.
  class CanPacket {
    public:

    ///@brief Create a can packet with a given 11 bit CAN identifier and upto 8 bytes of data.
    ///   @param canId the can identifier for the packet in the range of 0->2047
    ///   @param data upto 8 bytes of data that forms the body of the packet.
    template< size_t LEN >
    [[maybe_unused]] constexpr CanPacket(const CanId canId, const std::array<uint8_t, LEN> &data):
        header(canId), len(static_cast<uint8_t>(data.size() > 8 ? 8 : data.size())), packetData{} {
      memcpy(&packetData[0], &data[0], len);
    }

    /// @brief create a CAN packet from an 11 bit ID and 2 x 32bit words.
    /// @oaram canId the Can Id for the packet
    /// @param dataLo the first 4 bytes of the packet transmitted lsb first
    /// @param dataHi the last 4 bytes of the packet transmitted LSB first. if length <= 4 then this is never
    /// transmitted.
    /// @param length the number of valid data bytes in the CAN packet. j
    constexpr CanPacket(const CanId canId, const uint32_t dataLo, const uint32_t dataHi, const uint8_t length) :
        header(canId), len((length > 8) ? 8 : length), packetData{} {
      toUint8(&packetData[0], dataLo);
      toUint8(&packetData[4], dataHi);
    }

    /// @brief create an invalid packet.
    constexpr CanPacket() : header(0U), len(invalidPacket), packetData{} {
    }

    /// The 11bit can identifier.
    [[nodiscard]] CanId canId() const {
      return CanId(header);
    }

    /// Return the number of valid byte in the data portion of the packet. Invalid packets have 0 bytes
    [[nodiscard]] uint32_t length() const {
      return (len != invalidPacket) ? len : 0;
    }

    /// @brief access the last 4 bytes of the packet converts to 32bit value for loading into CAN mailbox  registers
    ///        data in the buffer is converted so that the LSB is the lowest byte in the buffer.
    [[nodiscard]] uint32_t dataHi() const {
      return toUint32(&packetData[4]);
    }
    /// @brief access the first 4 bytes of the packet converts to 32bit value for loading into CAN mailbox registers
    ///        data in the buffer is converted so that the LSB is the lowest byte in the buffer.
    [[nodiscard]] uint32_t dataLo() const {
      return toUint32(&packetData[0]);
    }

    /// @brief Access to the data portion of the packet as a byte array of the correct length. Modifying the
    /// Bytes array doe snot affect the CAN packet.
    [[nodiscard]] DataStructures::ByteArray data() const {
      auto result = DataStructures::ByteArray(length());
      result.setBytes(0, &packetData[0], length());
      return result;
    }

    /// @brief Return true if the packet is valid. Zero length packets can still be valid if they have a valid CAN ID
    [[nodiscard]] bool isValid() const {
      return len != invalidPacket;
    }

    /// @brief Serialisation method returns the
    [[nodiscard]] constexpr uint32_t streamSize() const {
      return sizeof(header) + sizeof(len) + sizeof(packetData);
    }

    template< typename STREAM >
    bool read(STREAM &stream) {
      if (stream.bytesLeft() >= streamSize()) {
        stream.read(header);
        stream.read(len);
        stream.read(packetData);
      }
      return true;
    }

    template< typename STREAM >
    constexpr void write(STREAM &stream) const {
      stream.write(header);
      stream.write(len);
      stream.write(packetData);
    }

    void invalidate() const  {
      // do nothing as the packet does not dynamically allocate or share memory.
    }

    private:
    /// @brief Mark packet so that the code can distinguish between zero length and invalid packets.
    static constexpr auto invalidPacket = 9;

    /// @brief THe CAN id for the packet
    uint16_t header;
    /// @brief the length of the data portion of the packet. Number of valid bytes in the data portion
    uint8_t len;

    /// @brief storage for upto 8 bytes o data for the variable portion of the packet.
    std::array<uint8_t, 8> packetData;
  };


}

#endif
