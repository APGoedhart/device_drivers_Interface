#ifndef DRIVERS_I2C_INCLUDE_DRIVERS_I2C_I2CDRIVER_HPP
#define DRIVERS_I2C_INCLUDE_DRIVERS_I2C_I2CDRIVER_HPP

#include <cstdint>
#include <dataStructures/ByteArray.hpp>
#include <drivers/i2c/I2cTypes.hpp>


namespace Drivers {
  /// @brief Driver controls a single I2C hardware peripheral. Currently designed to interact with a M24C16 type
  /// eeprom on the i2C bus.
  class I2cDriver {
    public:
    using ByteArray = DataStructures::ByteArray;

    I2cDriver(const I2cDriver &) = delete;
    I2cDriver &operator=(const I2cDriver &) = delete;

    I2cDriver() = default;
    virtual ~I2cDriver() = default;

    // I2CDriver
    // ---------
    /// Initialise the timer driver and enable it.
    /// @param speed The desired speed of the i2C bus
    /// @param callback. Used to notify of completion of the asynchronous read or write command.
    virtual void initialise(const NotifyI2cDriverTransferComplete &callback) = 0;

    /// Read a one or more bytes from the slave I2C device.
    /// On completion the TransferComplete callback will be called with the result.
    ///
    /// @param slaveAddress is the 7-bit address of the slave device
    /// @param slaveRegisterAddress is the register address on the slave device to read
    /// @param numberOfBytes is the number of bytes to read
    /// @param result is the resulting bytes that are read
    /// @return true if the read was successful, else false
    virtual void readBytes(uint8_t slaveAddr, uint8_t slaveRegisterAddr, ByteArray &result) = 0;

    /// Write multiple bytes of data to a register on the slave device. Note that the MC24c16 supports only a 16byte page size.
    /// so attempting to write more then 16 bytes in this case will result in wrapping.
    /// On completion the TransferComplete callback will be called with the result.
    ///
    /// @params slaveAddress is the I2C address of the connected slave device
    /// @params slaveRegisterStartAddress is the address of the register to start writing data to slave device
    /// @params data is the data to write to the slave device
    virtual void writeBytes(uint8_t slaveAddr, uint8_t slaveRegisterStartAddr, const ByteArray &txData,
                            uint8_t offset, uint8_t length) = 0;

    /// Return the data just read
    [[nodiscard]] virtual ByteArray getRxBuffer() const = 0;

    /// Enable/disable the write protect line for the I2C EEPROM. WP needs to be low for the period that the write is being performed.
    /// This may be upto 5ms after the data has been written to the EEPROM.
    virtual void setWriteProtect(bool enableWp) const = 0;

  };

}
#endif
