#ifndef DRIVERS_INTERFACE_RTC_INCLUDE_DRIVERS_RTC_CONFIGRAMNULLDRIVER_HPP
#define DRIVERS_INTERFACE_RTC_INCLUDE_DRIVERS_RTC_CONFIGRAMNULLDRIVER_HPP

#include <drivers/rtc/ConfigRamDriver.hpp>
#include <cstdint>
#include <cstddef>

namespace Drivers {

  /// @brief For those devices with no backup ram.
  class ConfigRamNullDriver :public ConfigRamDriver {
    public:
    ConfigRamNullDriver() = default;
    ~ConfigRamNullDriver() override = default;

    // return a safe reference
    uint8_t &operator[](size_t) override;

    // we have nowhere to store
    void store() override;

    // we always fail to load
    bool load() override;

    private:
    uint8_t nullData;
  };


uint8_t &ConfigRamNullDriver::operator[](size_t){
  return nullData;
}

void ConfigRamNullDriver::store(){
  /// do nothing;
}

bool ConfigRamNullDriver::load(){
  return false;
}
}

#endif
