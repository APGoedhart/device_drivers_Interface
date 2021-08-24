#ifndef DRIVERS_RTC_INCLUDE_DRIVERS_RTC_RTCTYPES_HPP
#define DRIVERS_RTC_INCLUDE_DRIVERS_RTC_RTCTYPES_HPP

#include <callbacks/Callback.hpp>

namespace Drivers {
  using Rtc1SecondCb = Mem::Callback<8, void()>;
}

#endif
