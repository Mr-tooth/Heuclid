#
# Copyright (c) 2026 Junhang Lai (赖俊杭)
#
# SPDX-License-Identifier: Apache-2.0
#

cmake_minimum_required(VERSION 3.22)

# Project setup
set(PROJECT_NAME heuclid)
set(PROJECT_DESCRIPTION
  "A C++ library for Euclidean geometry, convex hull, and geometric computation"
)
set(PROJECT_URL "https://github.com/Mr-tooth/Heuclid")
set(PROJECT_CUSTOM_HEADER_EXTENSION "h")
set(PROJECT_USE_CMAKE_EXPORT TRUE)
set(PROJECT_USE_KEYWORD_LINK_LIBRARIES TRUE)
set(PROJECT_COMPATIBILITY_VERSION AnyNewerVersion)
set(PROJECT_AUTO_RUN_FINALIZE FALSE)

# ---------------------------------------------------------------------------
# --- jrl-cmakemodules: three-tier lookup -------------------------------
# 1) Git submodule under cmake/jrl-cmakemodules/
# 2) System-installed (find_package)
# 3) FetchContent (auto-download)
# ---------------------------------------------------------------------------
set(JRL_CMAKE_MODULES "${CMAKE_CURRENT_LIST_DIR}/cmake/jrl-cmakemodules")
if(EXISTS "${JRL_CMAKE_MODULES}/base.cmake")
  message(STATUS "JRL cmakemodules found in 'cmake/jrl-cmakemodules/' (submodule)")
else()
  find_package(jrl-cmakemodules QUIET CONFIG)
  if(jrl-cmakemodules_FOUND)
    get_property(
      JRL_CMAKE_MODULES
      TARGET jrl-cmakemodules::jrl-cmakemodules
      PROPERTY INTERFACE_INCLUDE_DIRECTORIES
    )
    message(STATUS "JRL cmakemodules found on system at ${JRL_CMAKE_MODULES}")
  else()
    message(STATUS "JRL cmakemodules not found. Fetching from GitHub...")
    include(FetchContent)
    FetchContent_Declare(
      "jrl-cmakemodules"
      GIT_REPOSITORY "https://github.com/jrl-umi3218/jrl-cmakemodules.git"
      GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable("jrl-cmakemodules")
    FetchContent_GetProperties("jrl-cmakemodules" SOURCE_DIR JRL_CMAKE_MODULES)
    message(STATUS "JRL cmakemodules fetched to ${JRL_CMAKE_MODULES}")
  endif()
endif()

# Doxygen settings
set(DOXYGEN_USE_MATHJAX YES)

# ---------------------------------------------------------------------------
# --- Project declaration ---------------------------------------------------
# ---------------------------------------------------------------------------
include("${JRL_CMAKE_MODULES}/base.cmake")
compute_project_args(PROJECT_ARGS LANGUAGES CXX)
project(${PROJECT_NAME} ${PROJECT_ARGS})

include("${JRL_CMAKE_MODULES}/ide.cmake")
include("${JRL_CMAKE_MODULES}/apple.cmake")
# NOTE: Doxygen is handled automatically by base.cmake when BUILD_DOCUMENTATION=ON

apply_default_apple_configuration()

# C++ standard: minimum C++11
check_minimal_cxx_standard(11 ENFORCE)

# ---------------------------------------------------------------------------
# --- Dependencies ----------------------------------------------------------
# ---------------------------------------------------------------------------
# Eigen3: try find_package first, then FetchContent as fallback
find_package(Eigen3 QUIET CONFIG)
if(NOT Eigen3_FOUND)
  message(STATUS "Eigen3 not found locally - fetching from GitHub")
  include(FetchContent)
  FetchContent_Declare(
    Eigen3
    GIT_REPOSITORY "https://gitlab.com/libeigen/eigen.git"
    GIT_TAG "3.4.0"
    GIT_SHALLOW TRUE
  )
  # Eigen is header-only, no build needed
  set(EIGEN_BUILD_DOC OFF CACHE BOOL "" FORCE)
  set(EIGEN_BUILD_TESTING OFF CACHE BOOL "" FORCE)
  set(EIGEN_BUILD_PKGCONFIG OFF CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(Eigen3)
  # Create alias target for compatibility
  if(NOT TARGET Eigen3::Eigen)
    add_library(Eigen3::Eigen ALIAS eigen)
  endif()
  message(STATUS "Eigen3 fetched from GitHub")
else()
  message(STATUS "Eigen3 found: ${Eigen3_VERSION}")
endif()

# ---------------------------------------------------------------------------
# --- Options ---------------------------------------------------------------
# ---------------------------------------------------------------------------
option(BUILD_TESTING "Build unit tests" ON)
option(BUILD_DOCUMENTATION "Build Doxygen documentation" OFF)

# ---------------------------------------------------------------------------
# --- Heuclid library (header-only INTERFACE) -------------------------------
# ---------------------------------------------------------------------------
add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(
  ${PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${PROJECT_NAME} INTERFACE Eigen3::Eigen)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_11)

# Doxygen settings (must be set before base.cmake includes doxygen.cmake)
# Documentation is auto-generated when BUILD_DOCUMENTATION=ON and Doxygen is found.

# ---------------------------------------------------------------------------
# --- Testing ---------------------------------------------------------------
# ---------------------------------------------------------------------------
if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(src/Test)
endif()

# ---------------------------------------------------------------------------
# --- Install ---------------------------------------------------------------
# ---------------------------------------------------------------------------
include(GNUInstallDirs)

# Install headers
install(
  DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING
  PATTERN "*.h"
)

# Install CMake package configuration
install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}-targets
)

install(
  EXPORT ${PROJECT_NAME}-targets
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
