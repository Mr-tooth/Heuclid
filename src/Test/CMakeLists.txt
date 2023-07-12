# cmake_minimum_required(VERSION 3.0)
project(HeuclidTest)

# add_compile_options(/MT /O2)

# find_package(Heuclid REQUIRED)

# # include_directories(${HEUCLID_INCLUDE_DIRS})
# message("include ${HEUCLID_INCLUDE_DIRS}")
# set(BUILD_TEST_LJH 1)

# if(${BUILD_TEST_LJH})
#     message("--[Test] Build Heuclid basic test!")
#     add_executable(test test.cpp)
#     find_package(matplotlib_cpp REQUIRED)
#     target_link_libraries(test ${matplotlib_LIBS} Heuclid.lib)
# endif()


# 20230612 reconstruct heuclid test with googletest frame
set(Heuclid_gtest_list
  TestConvexHull2D
  TestBeizer
  )

foreach(NAME IN LISTS Heuclid_gtest_list)
  if(MSVC)
    find_package(GTest REQUIRED)
    include(GoogleTest)
    add_executable(${NAME} ${NAME}.cpp Foot/FootPolygon.cpp ../Heuclid/geometry/ConvexPolygon2D.cpp ../Heuclid/euclid/tools/HeuclidCoreTool.cpp)
    target_link_libraries(${NAME} GTest::gtest)
    target_compile_options(${NAME} PUBLIC /MT)
    gtest_discover_tests(${NAME})
  endif() 
endforeach()

target_include_directories(TestConvexHull2D PUBLIC ./include)
target_include_directories(TestConvexHull2D PUBLIC ./src/Test/Foot)
