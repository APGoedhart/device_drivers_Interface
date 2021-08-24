#ifndef DRIVERS_INTERFACE_RTC_INCLUDE_DRIVERS_RTC_RTCDRIVER_HPP
#define DRIVERS_INTERFACE_RTC_INCLUDE_DRIVERS_RTC_RTCDRIVER_HPP

#include <time/Time.hpp>

namespace Drivers {
  /// @brief implement a basic Real time clock using a unsigned 32 bit second counter since start
  /// Also track the offset of the date time the RTC was started.
  ///
  class RtcDriver {
    public:
    RtcDriver() = default;
    virtual ~RtcDriver() = default;

    RtcDriver(const RtcDriver &)=delete;
    RtcDriver &operator=(const RtcDriver &)=delete;

    /// @brief Configure the RTC for 1 second clock if not enabled already. Start the RTC.
    virtual void enable()=0;

    ///  @brief Return the current fractions of a 1/32K second for the RTC clock or 0 if not supported
    virtual uint16_t getSubSeconds()=0;

    ///  @brief Return the number of seconds since  RTC start.
    virtual Time::Seconds getRawSeconds()=0;

    ///  @brief Return the number of seconds 1/1/2020 0:00 UTC
    ///  @return the number of seconds since 1/1/2020 or 0 if the offset it invalid.
    virtual Time::Seconds getSeconds()=0;

    /// @brief set that Offset for the realtime clock. Can be stored in battery backed up RAM
    /// @param offset - the number of seconds to be added to the realtime clock to convert it to seconds since 1/1/2020 UTC
    virtual void  setOffset(Time::Seconds offset)=0;

    /// @brief return if the offset is set and is valid. If the offset is invalid then call
    virtual bool isOffsetValid()=0;
  };

}

#endif
