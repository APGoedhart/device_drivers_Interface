cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

target_link_libraries(driverInterfaceI2c
           mod::dataStructures)

target_include_directories(driverInterfaceI2c
        PRIVATE
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        )


target_sources(driverInterfaceI2c
        PRIVATE
        PUBLIC
        include/drivers/i2c/I2cTypes.hpp
        include/drivers/i2c/I2cDriver.hpp
        )
