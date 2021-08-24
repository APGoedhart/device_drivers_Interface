#ifndef DRIVERS_INTERFACE_CAN_INCLUDE_DRIVERS_CAN_CANFILTER_HPP
#define DRIVERS_INTERFACE_CAN_INCLUDE_DRIVERS_CAN_CANFILTER_HPP

#include <typeConversion/ConvertTypes.hpp>

namespace Drivers {
  ///  @brief Can filters match incoming packets to decided whether they are of interest to the current device.
  ///  Filters can either match an CAN id exactly or a combination of CAN Id and a mask that determines the bits
  /// in the identifier to match exactly.


  class CanFilter {
    public:
    /// @brief invalid CAN  filter matches nothing
    constexpr CanFilter() : mask(exactMatch), canId(0) {}

    /// @brief do an exact match
    constexpr explicit CanFilter(const CanId id) :
      mask(exactMatch),
      canId(static_cast<uint16_t>(static_cast<uint32_t>(id) << 5)) {}

    /// @brief match to the CAN id on the bit position determined by the mask
    /// @param mask each 1 in the mask is a bit position where the supplied CANId has to match exactly
    /// @param CanId only match this ID exactly at the bit positions where the mask is a 1
    constexpr CanFilter(const CanId id, const uint16_t idMask) :
        mask(static_cast<uint16_t>(idMask << 5)),
        canId(static_cast<uint16_t>( static_cast<uint32_t>(id) << 5)) {
    }

    /// @brief generate a filter from a 32bit register value
    constexpr explicit CanFilter(const uint32_t filterReg) :
        mask(static_cast<uint16_t>(filterReg >> 16U)), canId(static_cast<uint16_t>(filterReg)) {
    }

    /// @brief two filters are equal if their masks and CAN ids are the same.
    bool operator==(const CanFilter &rhs) const {
      return (rhs.mask == mask) && (rhs.canId == canId);
    }

    /// @brtief convert a mask into a value that can be loaded into a 32 bit register.
    [[nodiscard]] constexpr uint32_t registerValue() const {
      return (static_cast<uint32_t>(mask) << 16U) | canId;
    }

    private:
    //
    static constexpr auto exactMatch = static_cast<uint16_t>(0x07FFE << 5);
    /// @brief the mask for the filter to match the CAN ID on. Each bit position with 1 must match exactly
    uint16_t mask;
    /// @brief the CAN ID to match on.
     uint16_t canId;
  };


  ///  @brief A filter bank in the current implementation contains up to two filters that the CAN device can
  ///  use to detect CAN packets with 11 bit identifiers that it is interested in.

  class CanFilterBank {
    public:
    /// @brief only load a single filter
    explicit constexpr CanFilterBank(const CanFilter filter)  :
      filterData {filter.registerValue(),0} {
    }

    /// @brief load two filters into the bank
    constexpr CanFilterBank(const CanFilter filter1, const CanFilter filter2)
        : filterData{filter1.registerValue(), filter2.registerValue()} {
    }

    /// @brief access the DWOrds that make up the filter bank
    const uint32_t &operator[](uint32_t index) const {
      if (index > 1) {
        index = 1;
      }
      return filterData[index];
    }

    /// @brief convert the raw values located at the given index into a filter.
    [[nodiscard]] CanFilter filter(uint32_t index) const {
      if (index > 1) {
        index = 1;
      }
      return CanFilter(filterData[index]);
    }

    /// @brief return true if one of the two filter locations matches the filter we are looking for.
    [[nodiscard]] bool contains(const CanFilter &matchingFilter) const {
      return (filter(0) == matchingFilter) ||
             (filter(1) == matchingFilter);
    }

    private:
    uint32_t filterData[2] = {0,0} ;

  };
}

#endif
