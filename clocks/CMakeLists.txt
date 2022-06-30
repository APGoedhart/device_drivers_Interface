cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

target_link_libraries(driverInterfaceClocks
        )
set_target_properties(driverInterfaceClocks PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(driverInterfaceClocks
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        )


target_sources(driverInterfaceClocks
        PRIVATE
        PUBLIC
            include/drivers/clocks/ClockTypes.hpp
        )

