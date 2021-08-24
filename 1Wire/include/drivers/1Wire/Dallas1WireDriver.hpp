#ifndef DRIVERS_INTERFACE_1WIRE_INCLUDE_DRIVERS_1WIRE_DALLAS1WIREDRIVER_HPP
#define DRIVERS_INTERFACE_1WIRE_INCLUDE_DRIVERS_1WIRE_DALLAS1WIREDRIVER_HPP

#include <cstdint>
#include <cstddef>

#include <dataStructures/ByteArray.hpp>
#include <dataStructures/BitBuffer.hpp>

#include <drivers/gpio/GpioTypes.hpp>
#include <drivers/timers/TimTypes.hpp>
#include <drivers/timers/Hal_Tim.hpp>
#include <callbacks/Callback.hpp>


namespace Drivers {

  /// @brief holds a 1 wire address that is unique for each manufactured 1 wire device.
  using RomCode [[maybe_unused]] = uint64_t;

  /// @brief Callback for when the 1 wire driver has completed the current read or write.
  using Dallas1WireCommandComplateCb = Mem::Callback<8, void()>;

/// @interface for accessing devices on a 1 wire buss. Implements basic protocol allowing  read and write
/// commands across a Dallas Semiconductor. Full device discovery is not implemented by the driver.
///
  class Dallas1WireDriver{
    using ByteArray = DataStructures::ByteArray;
    public:
    Dallas1WireDriver() = default;
    virtual ~Dallas1WireDriver() = default;
    /// @brief Driver managed hardware resources so no copies
    Dallas1WireDriver(const Dallas1WireDriver &other) = delete;

    /// @brief Driver managed hardware resources so no copies
    Dallas1WireDriver &operator=(const Dallas1WireDriver &other) = delete;

    /// @brief register the call back, setup the GPIO pins for the device.
    virtual void initialise(const Dallas1WireCommandComplateCb &callback) =0;

    /// @brief Transmits a reset followed by the write of the command data (typically skip rom + command) and then
    ///reads in the number of bytes found in the rxData buffer.
    /// @param txCmd holds the complete sequence of bytes transmitted to generate the requested response from the
    /// 1 wire device. readonly
    /// @param rxCmd holds the received response from the device The length of the buffer determine the amount of
    ///        data requested from the device. Effectively takes ownership of the buffer until the command completes.
    ///
    virtual void sendReadCommand(const ByteArray &txCmd, const ByteArray &rxData) =0;

    /// @brief Transmits a reset followed by the command and and a sequence of data bytes. Does not expect a response
    virtual void sendWriteCommand(const ByteArray &txData)=0;

    /// Returns true if devices where present on the last bus reset
    [[nodiscard]] virtual bool areDevicesPresent() const=0;

    /// Return the previously read data may be an empty buffer if the previous command was write only.
    [[nodiscard]] virtual ByteArray getRxData() const=0;
   };
}

#endif