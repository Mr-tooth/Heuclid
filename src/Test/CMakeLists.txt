#
# Heuclid Tests
#
# NOTE: Heuclid is transitioning to header-only. Until all .cpp implementations
# are moved inline to headers, tests link against the source files directly.
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

# Heuclid source files (until full header-only migration)
set(HEUCLID_SOURCES
  ../Heuclid/euclid/orientation/Orientation2D.cpp
  ../Heuclid/euclid/tools/HeuclidCoreTool.cpp
  ../Heuclid/geometry/ConvexPolygon2D.cpp
  ../Heuclid/geometry/Line2D.cpp
  ../Heuclid/geometry/tools/HeuclidGeometryTools.cpp
  ../Heuclid/geometry/tools/HeuclidPolygonTools.cpp
)

# Test: ConvexHull2D
add_executable(TestConvexHull2D TestConvexHull2D.cpp Foot/FootPolygon.cpp ${HEUCLID_SOURCES})
target_link_libraries(TestConvexHull2D PRIVATE heuclid GTest::gtest_main)
gtest_discover_tests(TestConvexHull2D)

# Test: Bezier curves
add_executable(TestBeizer TestBeizer.cpp ${HEUCLID_SOURCES})
target_link_libraries(TestBeizer PRIVATE heuclid GTest::gtest_main)
gtest_discover_tests(TestBeizer)
