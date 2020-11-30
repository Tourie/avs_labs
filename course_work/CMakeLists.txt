cmake_minimum_required(VERSION 3.14)
project(riscv_sim)

set(CMAKE_CXX_STANDARD 17)


file(GLOB SRC
        "src/*.h"
        "src/*.cpp"
        )

add_executable(riscv_sim Tests/test.cpp Tests/TestClass.h ${SRC})
add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)
include_directories(Tests)
include_directories(src)
target_link_libraries(riscv_sim gtest gtest_main)