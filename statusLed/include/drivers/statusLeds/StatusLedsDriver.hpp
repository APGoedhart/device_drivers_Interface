#ifndef DRIVERS_INTERFACE_STATUSLED_INCLUDE_DRIVERS_STATUSLEDS_STATUSLEDSDRIVER_HPP
#define DRIVERS_INTERFACE_STATUSLED_INCLUDE_DRIVERS_STATUSLEDS_STATUSLEDSDRIVER_HPP

#include <array>
#include <drivers/gpio/Hal_Gpio.hpp>
#include <drivers/statusLeds/StatusLedTypes.hpp>
#include <drivers/statusLeds/PinFlasher.hpp>

namespace Drivers {


  /// @brief Manages the displaying of status to users through a set of LEDS
  class StatusLedsDriver {
    public:
    StatusLedsDriver()=default;
    virtual ~StatusLedsDriver() = default;
    /// Setup the hardware into a known state.
    virtual void initialise() const=0;

    ///@brief set one of the LEDs to the given flash status
    virtual void setStatus(Leds::Type led, LedState state)=0;

    /// Should be called once per 100 ms to flash the LEDS at the required rates.
    virtual void flash() =0;
  };

}

#endif