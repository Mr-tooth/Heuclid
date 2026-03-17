#
# Heuclid Tests
#

# Find GoogleTest
find_package(GTest QUIET)

if(NOT GTest_FOUND)
  message(STATUS "GoogleTest not found - fetching from GitHub")
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG "v1.14.0"
    GIT_SHALLOW TRUE
  )
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  include(GoogleTest)
endif()

# Test: ConvexHull2D
add_executable(TestConvexHull2D TestConvexHull2D.cpp Foot/FootPolygon.cpp)
target_link_libraries(TestConvexHull2D PRIVATE heuclid GTest::gtest_main)
gtest_discover_tests(TestConvexHull2D)

# Test: Bezier curves
add_executable(TestBeizer TestBeizer.cpp)
target_link_libraries(TestBeizer PRIVATE heuclid GTest::gtest_main)
gtest_discover_tests(TestBeizer)

# Test: Polygon predicates (intersect + contained)
add_executable(TestPolygonPredicate TestPolygonPredicate.cpp)
target_link_libraries(TestPolygonPredicate PRIVATE heuclid GTest::gtest_main)
gtest_discover_tests(TestPolygonPredicate)
