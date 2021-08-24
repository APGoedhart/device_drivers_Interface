#ifndef DRIVERS_INTERFACE_RTC_INCLUDE_DRIVERS_RTC_CONFIGRAMDRIVER_HPP
#define DRIVERS_INTERFACE_RTC_INCLUDE_DRIVERS_RTC_CONFIGRAMDRIVER_HPP

#include <cstdint>
#include <cstddef>

namespace Drivers  {
  class ConfigRamDriver  {
    public:
       ConfigRamDriver()= default;
       virtual ~ConfigRamDriver() = default;

        /// @brief access to the first N-4 bytes of the backup ram The last 4 stores a CRC32 to verify integrity of
        ///        data
        virtual uint32_t &operator[](size_t index)=0;

        /// @brief Store the data back into the backup ram. Generates the CRC to verify integrity
        virtual void store() =0 ;
        /// @brief Load the data from the backup storage ram and verify the CRC32
        /// @return true if the data was not corrupted, false otherwise
        virtual bool load() =0;

  };
}

#endif