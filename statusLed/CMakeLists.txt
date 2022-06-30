cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

target_link_libraries(driverInterfaceStatusLeds
   mod::dataTypes
        )
set_target_properties(driverInterfaceStatusLeds PROPERTIES LINKER_LANGUAGE CXX)


target_include_directories(driverInterfaceStatusLeds
        PRIVATE
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        )


target_sources(driverInterfaceStatusLeds
        PRIVATE
        PUBLIC
            include/drivers/statusLeds/StatusLedsDriver.hpp
            include/drivers/statusLeds/PinFlasher.hpp
            include/drivers/statusLeds/StatusLedTypes.hpp
        )

