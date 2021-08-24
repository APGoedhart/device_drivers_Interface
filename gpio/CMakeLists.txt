cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

target_link_libraries(driverInterfaceGpio
      )

target_include_directories(driverInterfaceGpio
        PRIVATE
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        )


target_sources(driverInterfaceGpio
        PRIVATE
        PUBLIC
           include/drivers/gpio/GpioTypes.hpp
        )

