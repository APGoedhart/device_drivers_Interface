cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

target_link_libraries(driverInterfaceSpi
        mod::dataStructures)
set_target_properties(driverInterfaceSpi PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(driverInterfaceSpi
        PRIVATE
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        )


target_sources(driverInterfaceSpi
        PRIVATE
        PUBLIC
            include/drivers/spi/SpiTypes.hpp
            include/drivers/spi/SpiDriver.hpp
            include/drivers/spi/SpiNotify.hpp
            include/drivers/spi/SpiDataBuffer.hpp
        )

