cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

target_link_libraries(driverInterfaceCan
        mod::dataStructures
        mod::driverInterfaceGpio)

set_target_properties(driverInterfaceCan PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(driverInterfaceCan
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )


target_sources(driverInterfaceCan
        PRIVATE
        PUBLIC
        include/drivers/can/CanDriver.hpp
        include/drivers/can/CanFilter.hpp
        include/drivers/can/CanPacket.hpp
        include/drivers/can/CanTypes.hpp
        )