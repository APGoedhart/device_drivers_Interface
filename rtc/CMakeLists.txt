cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

target_link_libraries(driverInterfaceRtc
        mod::time)

target_include_directories(driverInterfaceRtc
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )


target_sources(driverInterfaceRtc
        PRIVATE
        PUBLIC
        include/drivers/rtc/RtcDriver.hpp
        include/drivers/rtc/RtcTypes.hpp
        include/drivers/rtc/ConfigRamDriver.hpp
        include/drivers/rtc/ConfigRamNullDriver.hpp
        )

