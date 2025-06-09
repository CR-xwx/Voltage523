cmake_minimum_required(VERSION 3.14)
project(VoltageSim)

set(CMAKE_CXX_STANDARD 17)


find_package(jsoncpp CONFIG REQUIRED)

include_directories(${CMAKE_SOURCE_DIR})

set(SOURCES
    VoltageDevice.cpp
    TransceiverAPI.cpp
    VoltageCore.cpp
    IOConfig.cpp
)

# 构建 DLL
add_library(VoltageSim SHARED ${SOURCES})
target_compile_definitions(VoltageSim PRIVATE TRANSCEIVER_EXPORTS)
target_link_libraries(VoltageSim PRIVATE ${CMAKE_SOURCE_DIR}/lib/Art_DAQ_64.lib jsoncpp_lib)


# 构建 main 可执行程序
add_executable(main main.cpp)
target_link_libraries(main PRIVATE VoltageSim jsoncpp_lib)
