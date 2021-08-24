cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

target_link_libraries(driverInterfaceFlash
        )


target_include_directories(driverInterfaceFlash
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        )


target_sources(driverInterfaceFlash
        PRIVATE
        PUBLIC
            include/drivers/flash/FlashTypes.hpp
        )

