cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

target_link_libraries(driverInterface1Wire
        mod::driverInterfaceTimers
        mod::dataStructures )

target_include_directories(driverInterface1Wire
        PRIVATE
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        )


target_sources(driverInterface1Wire
        PUBLIC
        include/drivers/1Wire/Dallas1WireDriver.hpp
        )

