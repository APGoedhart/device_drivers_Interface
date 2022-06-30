#ifndef DRIVERS_INTERFACE_UID_INCLUDE_DRIVERS_UID_PROCESSORSERIAL_HPP
#define DRIVERS_INTERFACE_UID_INCLUDE_DRIVERS_UID_PROCESSORSERIAL_HPP

#include <cstdint>
#include <array>

namespace Drivers {
  class ProcessorSerial {
    public:
      ProcessorSerial():serialNumber{0,0,0}{}
      explicit ProcessorSerial(const volatile uint32_t (& embeddedSerial)[3] ):
      serialNumber{embeddedSerial[0], embeddedSerial[1], embeddedSerial[2]}{}

      ProcessorSerial(const ProcessorSerial &) = default;

      ~ProcessorSerial() = default;

      ProcessorSerial &operator=(const ProcessorSerial &other) = default;

      static constexpr uint32_t streamSize() {
        return 3*sizeof(uint32_t);
      }

      [[nodiscard]] bool isValid() const {
        return serialNumber[0] != 0 && serialNumber[1] != 0 &&serialNumber[2] != 0;
      }

      uint32_t operator[](uint32_t index) const {
        if( index >= serialNumber.size()) {
          return 0;
        }
        return serialNumber[index];
      }


      template<typename STREAM >
      bool read(STREAM &stream) {
        if(stream.bytesLeft() >= streamSize()) {
          for( uint32_t &val :serialNumber ){
            stream.read(val);
          }
        }
        return true;
      }

      template<typename STREAM>
      constexpr void write(STREAM &stream) const {
        for( uint32_t val :serialNumber ){
          stream.write(val);
        }
      }

    private:
      std::array<uint32_t,3> serialNumber;

  };
}


#endif