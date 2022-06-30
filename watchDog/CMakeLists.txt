cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

target_link_libraries(driverInterfaceWatchDog
        PUBLIC
)
set_target_properties(driverInterfaceWatchDog PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(driverInterfaceWatchDog
        PRIVATE
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        )


target_sources(driverInterfaceWatchDog
        PRIVATE
        PUBLIC
        include/drivers/watchDog/WatchDogDriver.hpp

        )

