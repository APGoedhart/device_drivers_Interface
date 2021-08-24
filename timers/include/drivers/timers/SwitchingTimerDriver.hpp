#ifndef DRIVERS_INTERFACE_TIMERS_INCLUDE_DRIVERS_TIMERS_SWITCHINGTIMERDRIVER_HPP
#define DRIVERS_INTERFACE_TIMERS_INCLUDE_DRIVERS_TIMERS_SWITCHINGTIMERDRIVER_HPP

#include <cstdint>
#include <cmsis/Processor.hpp>
#include <drivers/timers/SwitchingTimerTypes.hpp>
#include <drivers/timers/Hal_Tim.hpp>


/// Controls the timing and switching of one or more relays in a precise fashion
///  Assumes that the channels are assigned to the timer as
///  ZC Line - ETR
///  Relay 1 - channel 1
///  ZC Line - channel 2
///  Relay 2 - channel 3
///  ZC Load - channel 4
///
/// Currently Assumes we switch within 1 half AC cycle.

namespace Drivers {

  class SwitchingTimerDriver {
    public:
    using  Relay = SwitchingTimerTypes::Relay;
    using  RelayState = SwitchingTimerTypes::RelayState;
    using  RelayDelays = SwitchingTimerTypes::RelayDelays;
    using  SetRelayOutputCb  = SwitchingTimerTypes::SetRelayOutputCb;
    using  HasSwitchedCb  = SwitchingTimerTypes::HasSwitchedCb;

    /// @brief Link the SwitchingTimer driver to use a particular hardware timer.
    SwitchingTimerDriver() = default;
    virtual ~SwitchingTimerDriver()=default;

    SwitchingTimerDriver(const SwitchingTimerDriver &other) = delete;
    SwitchingTimerDriver &operator=(const SwitchingTimerDriver &other) = delete;

    /// @brief Register callbacks for setting relay outputs and being notified that they have switched
    virtual void initialise(const SetRelayOutputCb &setRelayOutputs, const  HasSwitchedCb &hasSwitched)=0;

    /// @brief allow setting of initial delays
    virtual void setDelayEstimates(const RelayDelays &rDelays)=0;

    /// @brief retrieve the current delays for saving to config
    [[nodiscard]] virtual const RelayDelays &getDelays() const =0;

    /// @brief Setup timing and start the counter
    virtual void setupAndStart()=0;

    /// @brief Open/Close the relays in the given order.  If ZC present the relay is switched on the second
    /// zero cross.
    virtual void changeRelay(Relay relay, RelayState newState)=0;

    /// @brief update the given estimated delay to the actual current delay
    virtual void adjustDelayForError(uint16_t &delay, int32_t error) const=0;

  };
}


#endif
