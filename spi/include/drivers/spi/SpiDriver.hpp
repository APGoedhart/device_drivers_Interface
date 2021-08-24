#ifndef DRIVERS_INTERFACE_SPI_INCLUDE_DRIVERS_SPI_SPIDRIVER_HPP
#define DRIVERS_INTERFACE_SPI_INCLUDE_DRIVERS_SPI_SPIDRIVER_HPP

#include <drivers/spi/SpiNotify.hpp>
#include <drivers/spi/Hal_Spi.hpp>
#include <dataStructures/ByteArray.hpp>

namespace Drivers {

  class SpiDriver {
    public:

    using ByteArray = DataStructures::ByteArray;

    /// @brief setup the peripheral the driver uses
    // The real driver needs to implement this along with configuring the actual GPIO pins used.
    SpiDriver()=default;
    virtual ~SpiDriver() =default;
    SpiDriver(const SpiDriver &rhs) = delete;
    SpiDriver &operator=(const SpiDriver &rhs) = delete;

    /// @brief Initialise the timer driver and enable it.
    /// @param speed The desired speed of the Spi bus. Because Interrupts are used should be
    /// 1.5MHz or less which gives about 1000 cycles between interrupts
    /// @param callback. Used to notify of completion of the asynchronous read or write command.
    virtual void initialise(SpiBaudRate speed, const SpiCommandCompleteCb &callback)=0;

    /// @brief Write out one or more bytes and then read in the result into the corresponding buffer.
    /// On completion the TransferComplete callback will be called.
    /// Uses interrupt routines.
    /// @param result reads the bytes to be written out the SPI port and replaces them with the bytes read back in
    ///              The length of the buffer is used to set the bytes read and written
    virtual void readWriteBytes(ByteArray &rxTxData)=0;

    ///  @brief Return the Currently received data from the last command. Only valid during the callback.
    [[nodiscard]]  virtual ByteArray getRxBuffer() const=0;

    ///  @brief Enable or disable the physical write protect on the external SPI flash.
    virtual void enableWp(bool isEnabled) const=0;
  };
}

#endif