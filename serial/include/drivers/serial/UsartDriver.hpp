#ifndef DRIVERS_INTERFACE_SERIAL_INCLUDE_DRIVERS_SERIAL_USARTDRIVER_HPP
#define DRIVERS_INTERFACE_SERIAL_INCLUDE_DRIVERS_SERIAL_USARTDRIVER_HPP

#include <dataStructures/ByteArray.hpp>
#include <dataStructures/CircularByteBuffer.hpp>
#include <callbacks/Callback.hpp>
#include <drivers/gpio/GpioTypes.hpp>
#include "drivers/serial/UsartTypes.hpp"

namespace Drivers {

  /// @brief notify the user of the driver that we have sent the previous tx request.
  using UsartTransmitCompleteCb = Mem::Callback<8, void()>;
  /// @brief notify the user of the driver that new data has been received on the serial port
  ///        @param lineIdle : bool The callback was triggered because the line timeout out waiting for the
  ///                          next character and there was data in the rx buffer.
  using UsartDataReceivedCb = Mem::Callback<8, void(bool)>;


  /// Interface for the USART driver
  template<size_t BUF_SIZE=256U>
  class UsartDriver {
    public:
    static constexpr auto rxBufferSize = BUF_SIZE;
    using CircularBuffer = typename DataStructures::CircularByteBuffer<rxBufferSize>;

    UsartDriver()=default;
    virtual ~UsartDriver() = default;

    /// @brief Initialise the USART
    /// @param baudRate is the speed that the USART port should run at
    /// @param notify is an object that should be called back when data has been received or transmitted
    virtual void initialise(const UsartTransmitCompleteCb  &transmitComplete, const UsartDataReceivedCb &dataReceived) = 0;

    /// @brief Write data to the serial port in an asynchronous manner using the DMA.
    /// @param data is a buffer containing the data to write to the serial port
    virtual void writeBytes(const DataStructures::ByteArray &data) = 0;

    /// @brief Return a read stream that references the underlying circular buffer.
    ///  Does not move the read pointer until updateFromStream is called. does this in a single
    ///  Critical section.
    [[nodiscard]] virtual typename CircularBuffer::ReadStream getRxSnapShot() const = 0;

    /// @brief Updates the underlying circular buffers read pointer with the data read out from the stream.
    /// @param stream a stream given by getRxSnapshot and updated to extract data.
    virtual void updateFromStream(typename CircularBuffer::ReadStream &stream) = 0;

    /// @brief Cannot load a new buffer for transmission whilst the previous one is transmitting.
    [[nodiscard]] virtual bool isTransmitting() const = 0;

  };

}

#endif
