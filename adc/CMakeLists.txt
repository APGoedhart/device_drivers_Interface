cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

target_link_libraries(driverInterfaceAdc
        mod::dataStructures
        mod::driverInterfaceGpio)

set_target_properties(driverInterfaceAdc PROPERTIES LINKER_LANGUAGE CXX)


target_include_directories(driverInterfaceAdc
        PRIVATE
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        )


target_sources(driverInterfaceAdc
        PRIVATE
        PUBLIC
            include/drivers/adc/AdcDriver.hpp
            include/drivers/adc/AdcTypes.hpp
        )

