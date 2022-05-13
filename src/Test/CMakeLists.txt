cmake_minimum_required(VERSION 3.0)
project(HeuclidTest)

add_compile_options(/MT /O2)

find_package(Heuclid REQUIRED)

link_libraries(Heuclid.lib)
# include_directories(${HEUCLID_INCLUDE_DIRS})
message("include ${HEUCLID_INCLUDE_DIRS}")
set(BUILD_TEST_LJH 1)

if(${BUILD_TEST_LJH})
    message("--[Test] Build Heuclid basic test!")
    add_executable(test test.cpp)
    
endif()