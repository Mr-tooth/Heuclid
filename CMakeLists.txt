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

# Doxygen settings (must be before base.cmake)
set(DOXYGEN_USE_MATHJAX YES)
set(DOXYGEN_FILE_PATTERNS "*.h")
set(DOXYGEN_HTML_OUTPUT "doxygen-html")
option(BUILD_DOCUMENTATION "Build Doxygen documentation" ON)
option(INSTALL_DOCUMENTATION "Install Doxygen documentation" OFF)

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
# Eigen3: header-only, INTERFACE target. Use FetchContent with version lock.
find_package(Eigen3 3.3 QUIET CONFIG)
if(NOT TARGET Eigen3::Eigen)
  message(STATUS "Eigen3 not found - fetching 3.4.0 via FetchContent")
  include(FetchContent)
  FetchContent_Declare(
    Eigen3
    GIT_REPOSITORY "https://gitlab.com/libeigen/eigen.git"
    GIT_TAG "3.4.0"
    GIT_SHALLOW TRUE
  )
  # Eigen3 is header-only — just populate, no add_subdirectory.
  # This avoids target name conflicts (e.g. 'uninstall') with jrl-cmakemodules.
  FetchContent_GetProperties(Eigen3)
  if(NOT eigen3_POPULATED)
    FetchContent_Populate(Eigen3)
  endif()
  add_library(Eigen3_Eigen INTERFACE)
  target_include_directories(Eigen3_Eigen INTERFACE "${eigen3_SOURCE_DIR}")
  add_library(Eigen3::Eigen ALIAS Eigen3_Eigen)
  set(Eigen3_FOUND TRUE)
  set(Eigen3_VERSION "3.4.0")
  message(STATUS "Eigen3 fetched: ${eigen3_SOURCE_DIR}")
else()
  message(STATUS "Eigen3 found: ${Eigen3_VERSION}")
endif()

# Register Eigen3 as a dependency for the generated Config.cmake
# (adds find_dependency(Eigen3) to the installed package config)
add_project_dependency(Eigen3 REQUIRED)

# ---------------------------------------------------------------------------
# --- Options ---------------------------------------------------------------
# ---------------------------------------------------------------------------
option(BUILD_TESTING "Build unit tests" ON)
# BUILD_DOCUMENTATION is set before base.cmake include above

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

# ---------------------------------------------------------------------------
# --- Doxygen documentation -------------------------------------------------
# ---------------------------------------------------------------------------
# jrl-cmakemodules (base.cmake) automatically creates {PROJECT_NAME}-doc target
# when BUILD_DOCUMENTATION=ON and Doxygen is found.
# Customize Doxygen output via DOXYGEN_* variables (set before base.cmake include).
# To build: cmake --build build --target heuclid-doc

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
  EXPORT ${PROJECT_NAME}Targets
)

# NOTE: Config.cmake, ConfigVersion.cmake, and export install are handled
# by setup_project_finalize() via jrl-cmakemodules (package-config.cmake).

# ---------------------------------------------------------------------------
# --- Finalize (generates Doxyfile, pkg-config, coverage, etc.) -------------
# ---------------------------------------------------------------------------
setup_project_finalize()
