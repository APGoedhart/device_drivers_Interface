cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

target_link_libraries(driverInterfaceTimers
        mod::time
        )
set_target_properties(driverInterfaceTimers PROPERTIES LINKER_LANGUAGE CXX)


target_include_directories(driverInterfaceTimers
        PRIVATE
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        )


target_sources(driverInterfaceTimers
        PRIVATE
        PUBLIC
        include/drivers/timers/AlarmTimerDriver.hpp
        include/drivers/timers/FetTotemPoleDriver.hpp
        include/drivers/timers/ClockSourceDriver.hpp
        include/drivers/timers/SwitchingTimerDriver.hpp
        include/drivers/timers/SwitchingTimerTypes.hpp
       )

