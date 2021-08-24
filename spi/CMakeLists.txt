cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

target_link_libraries(driverInterfaceSpi
        mod::dataStructures)

target_include_directories(driverInterfaceSpi
        PRIVATE
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        )


target_sources(driverSpi
        PRIVATE
        PUBLIC
            include/drivers/spi/SpiTypes.hpp
            include/drivers/spi/SpiDriver.hpp
            include/drivers/spi/SpiNotify.hpp
            include/drivers/spi/SpiDataBuffer.hpp
        )

