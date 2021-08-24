#ifndef DRIVERS_STATUSLED_INCLUDE_DRIVERS_STATUSLEDS_PINFLASHER_HPP
#define DRIVERS_STATUSLED_INCLUDE_DRIVERS_STATUSLEDS_PINFLASHER_HPP

#include <drivers/statusLeds/StatusLedTypes.hpp>
#include <drivers/gpio/GpioTypes.hpp>

namespace Drivers {

   /// Holds the state of a single LED. Tracks the pin state and performs the flashing.
  class PinFlasher {
    public:
    /// @brief Create an invalid pin that does nto flash
    PinFlasher();

    /// @brief Create a new Pin state that is associated with a particular GPIO pin
    /// @param pin the GPIO pin that the state is tracked for.
    explicit PinFlasher(PortPin assignedPin);

    /// @brief setup the pin for driving the LED (function = output, Drive = push pull)
    void setupPinForOutput() const;

    /// @brief set the new tracked state for the pin.
    void setState(LedState newState);

    /// @brief Should be called every 100mS to toggle the LED pins to produce the desired flash rate.
    /// The PinState tracks the number of elapsed intervals to flash at fast or slow rates.
    void flash();

    /// @brief returns true if this pin has a valid physical GPIO pin associated with it.
    [[nodiscard]] bool isValid() const;

    private:
    /// @brief The physical GPIO pin assigned to this LED
    PortPin pin;

    /// Where we are in the flash period in 1/10th of second from start of period.
    uint8_t flashCount = 0;

    /// The configured state for the LED
    LedState configuredState = LedState::LedOff;

    void setGpioPinHigh(bool isHigh) const;

    ///@brief increment the variable mod a given period.
    static uint8_t incrementModPeriod(uint8_t count, uint8_t period);
  };
}


#endif
