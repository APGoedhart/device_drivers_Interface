cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

target_link_libraries(driverInterfaceDma
        mod::pointers
        mod::dataStructures)

target_include_directories(driverInterfaceDma
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )


target_sources(driverInterfaceDma
        PRIVATE
        PUBLIC
        include/drivers/dma/DmaChannelDriver.hpp
        include/drivers/dma/DmaTypes.hpp
        )

