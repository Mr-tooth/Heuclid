cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME Heuclid)
project(${PROJECT_NAME} VERSION 0.1)

set(CMAKE_BUILD_TYPE Release)

message("Build type is ${CMAKE_BUILD_TYPE}")

add_compile_options(-std=c++14)
add_compile_options(/MT /O2)

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


# Build Heuclid static library
add_library(${LIB_NAME} STATIC ${SRC_FILES})


# Set instal configuration
message("Install path is ${CMAKE_INSTALL_PREFIX}")

set(Heuclid_include_dirs ${CMAKE_INSTALL_PREFIX}/include)
set(Heuclid_link_dirs ${CMAKE_INSTALL_PREFIX}/lib)
# set(Heuclid_src)

configure_file(Heuclid.cmake.in ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/HeuclidConfig.cmake @ONLY)
   
install(FILES ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/HeuclidConfig.cmake DESTINATION share/Heuclid/cmake)
install(FILES ${PROJECT_BINARY_DIR}/Heuclid.lib DESTINATION lib)
install(DIRECTORY include/Heuclid DESTINATION include)

