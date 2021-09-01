cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

target_link_libraries( driverInterfaceSerial
        mod::dataStructures
        mod::driverInterfaceGpio
        )

target_include_directories(driverInterfaceSerial
        PRIVATE
          include
          ${CMAKE_CURRENT_SOURCE_DIR}/../dma/include
        PUBLIC
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

target_sources(driverInterfaceSerial
        PRIVATE
        PUBLIC
            include/drivers/serial/UsartTypes.hpp
            include/drivers/serial/UsartDriver.hpp
        )

