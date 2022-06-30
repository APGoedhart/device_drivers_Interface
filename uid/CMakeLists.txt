cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

target_link_libraries(driverInterfaceUid
        )
set_target_properties(driverInterfaceUid PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(driverInterfaceUid
        PRIVATE
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC
          ${CMAKE_CURRENT_SOURCE_DIR}/include
        )


target_sources(driverInterfaceUid
        PUBLIC
            include/drivers/uid/Uid.hpp
            include/drivers/uid/ProcessorSerial.hpp
        )

set_target_properties(driverInterfaceUid PROPERTIES LINKER_LANGUAGE CXX)