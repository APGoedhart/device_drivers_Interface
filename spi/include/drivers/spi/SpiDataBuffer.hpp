#ifndef DRIVERS_INTERFACE_SPI_INCLUDE_DRIVERS_SPI_SPIDATABUFFER_HPP
#define DRIVERS_INTERFACE_SPI_INCLUDE_DRIVERS_SPI_SPIDATABUFFER_HPP

#include <cstdint>
#include <drivers/spi/SpiTypes.hpp>
#include <cmsis/PeripheralRegister.hpp>
#include <dataStructures/ByteArray.hpp>
#include <dataStructures/CircularByteBuffer.hpp>

namespace Drivers {

  class SpiDataBuffer {
    public:
      SpiDataBuffer() noexcept:
         txData(),
         rxData(),
         notifyTransferComplete() {
      }

      void registerCallback(const SpiTransferCompleteCb  &callback){
        notifyTransferComplete = callback;
      }

      [[nodiscard]] bool isTransferComplete() const{
        return rxData.bytesLeft() == 0;
      }

      void loadNextTransfer(DataStructures::ByteArray &buffer){
        rxData = buffer.getWriteStream();
        txData = buffer.getReadStream();
      }

      [[nodiscard]] uint32_t dataRemaining() const {
        return rxData.bytesLeft();
      }

      void writeToPortWord(volatile uint16_t &dr){
        dr =  read<uint16_t>(txData);
      }

      /// MISRA - The data register is defined as a 16 bit but it is a fifo and the width of the hardware read/Write
      /// determines whether 16 bits or 8 bits are transmitted. So the access width is very important hence the
      /// cast. The other option is to use a union for register access but that is also prohibited by MISRA.
      void writeToPortByte(volatile uint16_t &dr){
        const auto val =read<uint8_t> (txData);
        *(reinterpret_cast<volatile uint8_t *>(&dr)) = val;
      }


     void readFromPortWord(const volatile uint16_t &dr){
        const uint16_t val = dr;
        rxData.write(val);
      }

      /// MISRA - The data register is defined as a 16 bit but it is a fifo and the width of the hardware read/Write
      /// determines whether 16 bits or 8 bits are transmitted. So the access width is very important hence the
      /// cast. The other option is to use a union for register access but that is also prohibited by MISRA.
      void readFromPortByte(volatile uint16_t &dr){
        const  uint8_t val = *(reinterpret_cast<volatile uint8_t *>(&dr));
        rxData.write(val);
      }
      void notify() const {
        notifyTransferComplete();
      }

    private:
      DataStructures::ByteArray::ReadStream txData;
      DataStructures::ByteArray::WriteStream rxData;
      SpiTransferCompleteCb notifyTransferComplete;
  };
}

#endif
