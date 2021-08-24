#ifndef DRIVERS_INTERFACE_CAN_INCLUDE_DRIVERS_CAN_CANDRIVER_HPP
#define DRIVERS_INTERFACE_CAN_INCLUDE_DRIVERS_CAN_CANDRIVER_HPP

#include <drivers/can/CanPacket.hpp>
#include <drivers/can/CanFilter.hpp>
#include <drivers/can/CanTypes.hpp>

namespace Drivers {

/// @brief The Can Driver is packet based. All transmission and reception is done via the
/// CanPacket data type.

  class CanDriver {
    public:

    /// @brief  A filter used to notify device of all packets received. A more discriminant
    /// filter may be put into place to ensure that the device only processes
    /// packets it is interested in. By default installed at filterId =0

    static constexpr auto matchEverything = CanFilter(CanId(0x3FFU), 0x0);

    explicit CanDriver() = default;

    virtual ~CanDriver() = default;

    CanDriver(const CanDriver &) = delete;

    const CanDriver &operator=(const CanDriver &) = delete;


    /// @brief Setup the driver with any interrupts and call backs
    /// @param notify
    virtual void initialise(const Drivers::RxPacketCb &rxPacket, const Drivers::TxPacketSentCb &txPacket) =0;

    /// @brief Adds a packet into the transmit queue if there is space. When the packet gets transmitted is dependant
    /// on the transmit state of the underlying peripheral and the availability of the channel.
    /// @param txPacket the packet to transmit.
    /// @return returns true if the packet was added to the queue
    ///         false if there was no space.
    virtual bool txPacket(CanPacket txPacket)=0;

    /// @brief Return the number of tx mail boxes available. The driver has at least this many available.
    /// This number may increase at any time cannot decrease unless txPacket is made.
    [[nodiscard]] virtual uint32_t getTxSlots() const =0;

    /// @brief Returns true if the CAN is currently in a state in which it can transmit.
    /// @return true if transmission is currently possible. Note the system will always queue packets up to
    [[nodiscard]] virtual bool isCanActive() const =0;

    /// Add a filter for a packet we are interested in. The filter is only applied to the next received packet.
    /// A check is not made to ensure that the filter does not already exist.
    virtual void addMatchingFilter(CanFilter filter)=0;

    /// @brief Sets the current list of filters as active. Clears out the previous filters completely.
    virtual void updateActiveFilters()=0;

    /// @brief Clears out all filters currently active for the CAN This effectively means the
    /// peripheral cannot receive any packets, even if it is active.
    virtual void clearFilters()=0;
  };


}

#endif
