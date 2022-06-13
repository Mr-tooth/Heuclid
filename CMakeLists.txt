cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME Heuclid)
project(${PROJECT_NAME} VERSION 0.1)



message("Build type is ${CMAKE_BUILD_TYPE}")

add_compile_options(-std=c++14)
add_compile_options(/MT)

set(ROOT_PATH ..)

include(./cmake/HeuclidConfig.cmake)

include_directories(./include)
include_directories(./include/Heuclid)
include_directories(./include/Heuclid/euclid)
include_directories(./include/Heuclid/geometry)
include_directories(./include/Heuclid/title)

aux_source_directory(./src/Heuclid/euclid SRC_FILES)
aux_source_directory(./src/Heuclid/euclid/orientation SRC_FILES)
aux_source_directory(./src/Heuclid/euclid/tools SRC_FILES)
aux_source_directory(./src/Heuclid/euclid/tuple2D SRC_FILES)
aux_source_directory(./src/Heuclid/euclid/tuple3D SRC_FILES)
aux_source_directory(./src/Heuclid/euclid/tuple4D SRC_FILES)
aux_source_directory(./src/Heuclid/geometry/tools SRC_FILES)
aux_source_directory(./src/Heuclid/geometry SRC_FILES)

set(BUILD_TEST 1)
set(NEED_PLOT 1)
if(BUILD_TEST)
    set(CMAKE_BUILD_TYPE Debug)
    
    
    add_executable(test src/Test/test.cpp ${SRC_FILES})
    if(NEED_PLOT)
        find_package(matplotlib_cpp REQUIRED)
        target_link_libraries(test ${matplotlib_LIBS})
    endif()
else()
    set(CMAKE_BUILD_TYPE Release)
    add_compile_options(/O2)
# Build Heuclid static library
add_library(${LIB_NAME} STATIC ${SRC_FILES})
endif()

# Set instal configuration
message("Install path is ${CMAKE_INSTALL_PREFIX}")

set(Heuclid_include_dirs ${CMAKE_INSTALL_PREFIX}/include)
set(Heuclid_link_dirs ${CMAKE_INSTALL_PREFIX}/lib)
# set(Heuclid_src)

configure_file(Heuclid.cmake.in ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/HeuclidConfig.cmake @ONLY)
   
install(FILES ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/HeuclidConfig.cmake DESTINATION share/Heuclid/cmake)
install(FILES ${PROJECT_BINARY_DIR}/Heuclid.lib DESTINATION lib)
install(DIRECTORY include/Heuclid DESTINATION include)

